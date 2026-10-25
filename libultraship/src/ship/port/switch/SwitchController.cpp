#ifdef __SWITCH__
#include "SwitchController.h"
#include <algorithm>
#include <unordered_map>
#include "ship/utils/StringHelper.h"
#include "ship/Context.h"
#include "ship/controller/controldeck/ControlDeck.h"

namespace Ship {

static constexpr uint64_t CONTROLLER_MASK = 1UL;
static std::unordered_map<int32_t, int32_t> sInstanceIdToDeviceSlot;
static std::unordered_map<int32_t, std::string> sInstanceIdToSerial;

void SwitchController::RegisterDevice(int32_t instanceId, int32_t slot, const std::string& serial) {
    sInstanceIdToDeviceSlot[instanceId] = slot;
    sInstanceIdToSerial[instanceId] = serial;
}

void SwitchController::ClearDeviceSlots() {
    sInstanceIdToDeviceSlot.clear();
    sInstanceIdToSerial.clear();
}

int32_t SwitchController::GetDeviceSlot(int32_t instanceId) {
    auto it = sInstanceIdToDeviceSlot.find(instanceId);
    return (it != sInstanceIdToDeviceSlot.end()) ? it->second : -1;
}

std::string SwitchController::GetDeviceSerial(int32_t instanceId) {
    auto it = sInstanceIdToSerial.find(instanceId);
    return (it != sInstanceIdToSerial.end()) ? it->second : "";
}

void SwitchController::Update() {
    // Called every frame.
    // We only poll for controller connection changes every 60 frames.
    static int sFrameCounter = 0;
    if (++sFrameCounter < 60) {
        return;
    }
    sFrameCounter = 0;

    // Check for connection changes
    static bool sLastConnected[4] = {};
    bool changed = false;
    for (uint8_t i = 0; i < 4; i++) {
        bool connected = GetInstance().IsNpadConnected(i);
        if (connected != sLastConnected[i]) {
            sLastConnected[i] = connected;
            changed = true;
        }
    }
    if (changed) {
        auto context = Context::GetRawInstance();
        if (context && context->GetControlDeck()) {
            context->GetControlDeck()->GetConnectedPhysicalDeviceManager()->HandlePhysicalDeviceConnect(0);
        }
    }
}

SwitchController& SwitchController::GetInstance() {
    static SwitchController instance;
    return instance;
}

HidNpadIdType SwitchController::GetNpadId(uint8_t portIndex) const {
    const uint8_t clampedIndex = std::min<uint8_t>(portIndex, 7);
    return static_cast<HidNpadIdType>(HidNpadIdType_No1 + clampedIndex);
}

bool SwitchController::EnsureInitialized(uint8_t portIndex) {
    if (portIndex >= mControllers.size()) {
        return false;
    }

    auto& controller = mControllers[portIndex];
    if (controller.Initialized) {
        return true;
    }

    const auto npadId = GetNpadId(portIndex);
    const uint64_t padMask = (CONTROLLER_MASK << npadId) | (CONTROLLER_MASK << HidNpadIdType_Handheld);

    hidSetSupportedNpadStyleSet(HidNpadStyleTag_NpadFullKey | HidNpadStyleTag_NpadHandheld |
                                 HidNpadStyleTag_NpadJoyDual | HidNpadStyleTag_NpadJoyLeft |
                                 HidNpadStyleTag_NpadJoyRight | HidNpadStyleTag_NpadLucia |
                                 HidNpadStyleTag_NpadLagon | HidNpadStyleTag_NpadLark |
                                 HidNpadStyleTag_NpadLager);

    padInitializeWithMask(&controller.State, padMask);
    padUpdate(&controller.State);

    Result vibInitResult0 = hidInitializeVibrationDevices(controller.Handles[0], 2, HidNpadIdType_Handheld, HidNpadStyleTag_NpadHandheld);
    Result vibInitResult1 = hidInitializeVibrationDevices(controller.Handles[1], 2, npadId, HidNpadStyleTag_NpadJoyDual);
    SPDLOG_INFO("hidInitializeVibrationDevices results: handheld={:#x}, joydual={:#x}", vibInitResult0, vibInitResult1);

    hidGetSixAxisSensorHandles(&controller.Sensors[0], 1, HidNpadIdType_Handheld, HidNpadStyleTag_NpadHandheld);
    hidGetSixAxisSensorHandles(&controller.Sensors[1], 1, npadId, HidNpadStyleTag_NpadFullKey);
    hidGetSixAxisSensorHandles(&controller.Sensors[2], 2, npadId, HidNpadStyleTag_NpadJoyDual);
    hidGetSixAxisSensorHandles(&controller.Sensors[4], 1, npadId, HidNpadStyleTag_NpadJoyLeft);
    hidGetSixAxisSensorHandles(&controller.Sensors[5], 1, npadId, HidNpadStyleTag_NpadJoyRight);
    Result sixAxisLucia = hidGetSixAxisSensorHandles(&controller.Sensors[6], 1, npadId, HidNpadStyleTag_NpadLucia);
    Result sixAxisLagon = hidGetSixAxisSensorHandles(&controller.Sensors[7], 1, npadId, HidNpadStyleTag_NpadLagon);
    Result sixAxisLark = hidGetSixAxisSensorHandles(&controller.Sensors[8], 1, npadId, HidNpadStyleTag_NpadLark);
    Result sixAxisLager = hidGetSixAxisSensorHandles(&controller.Sensors[9], 1, npadId, HidNpadStyleTag_NpadLager);
    SPDLOG_INFO("SENSOR_CALIB thirdparty handles: lucia={:#x} lagon={:#x} lark={:#x} lager={:#x}",
                sixAxisLucia, sixAxisLagon, sixAxisLark, sixAxisLager);

    for (auto& sensor : controller.Sensors) {
        hidStartSixAxisSensor(sensor);
    }

    SPDLOG_INFO("Initialized controller for port {}: npadId={}, padMask={:#x}, styleSet={:#x}, deviceType={:#x}",
                portIndex, static_cast<int>(npadId), padMask, padGetStyleSet(&controller.State),
                hidGetNpadDeviceType(npadId));

    controller.Initialized = true;
    return true;
}

static void ApplyRightJoyConOrientation(HidSixAxisSensorState& state) {
    // RIGHT_GYRO_RAW logging showed left-right rotation registers on the raw
    // z-axis (spiking ~0.6-0.76), not y (stayed under 0.2/noise) -- the right
    // Joy-Con IMU is mounted rotated relative to the left, so this is an axis
    // swap, not a sign flip. ReadGyro reads yaw from angular_velocity.y, so
    // swap y and z here. x (pitch) confirmed correct as-is, left untouched.
    // Sign of the swapped z->y value is a guess pending on-hardware direction
    // check -- flip if left/right ends up backwards.
    const float y = state.angular_velocity.y;
    const float z = state.angular_velocity.z;
    state.angular_velocity.y = z;
    state.angular_velocity.z = y;
}

bool SwitchController::ReadSixAxisState(uint8_t portIndex, HidSixAxisSensorState& state) {
    if (!EnsureInitialized(portIndex)) {
        return false;
    }

    auto& controller = mControllers[portIndex];
    padUpdate(&controller.State);
    const uint64_t styleSet = padGetStyleSet(&controller.State);

    static bool loggedTagValues = false;
    if (!loggedTagValues) {
        SPDLOG_INFO("STYLE_TAG_VALUES Lucia={:#x} Lagon={:#x} Lark={:#x} Lager={:#x} JoyDual={:#x} JoyLeft={:#x} JoyRight={:#x} Handheld={:#x} FullKey={:#x}",
                    (uint64_t)HidNpadStyleTag_NpadLucia, (uint64_t)HidNpadStyleTag_NpadLagon,
                    (uint64_t)HidNpadStyleTag_NpadLark, (uint64_t)HidNpadStyleTag_NpadLager,
                    (uint64_t)HidNpadStyleTag_NpadJoyDual, (uint64_t)HidNpadStyleTag_NpadJoyLeft,
                    (uint64_t)HidNpadStyleTag_NpadJoyRight, (uint64_t)HidNpadStyleTag_NpadHandheld,
                    (uint64_t)HidNpadStyleTag_NpadFullKey);
        loggedTagValues = true;
    }
    static uint64_t lastLoggedStyleSet = 0xFFFFFFFFFFFFFFFFull;
    if (styleSet != lastLoggedStyleSet) {
        SPDLOG_INFO("STYLE_SET_RAW portIndex={} styleSet={:#x}", portIndex, styleSet);
        lastLoggedStyleSet = styleSet;
    }

    if (styleSet & HidNpadStyleTag_NpadJoyDual) {
        const uint64_t attributes = padGetAttributes(&controller.State);
        const bool leftConnected = attributes & HidNpadAttribute_IsLeftConnected;
        const bool rightConnected = attributes & HidNpadAttribute_IsRightConnected;

        if (controller.Gyro == GyroSource::Both && leftConnected && rightConnected) {
            HidSixAxisSensorState leftState = {};
            HidSixAxisSensorState rightState = {};
            hidGetSixAxisSensorStates(controller.Sensors[2], &leftState, 1);
            hidGetSixAxisSensorStates(controller.Sensors[3], &rightState, 1);
            SPDLOG_INFO("GYRO_CALIB raw L(x={:.3f} y={:.3f} z={:.3f}) raw R(x={:.3f} y={:.3f} z={:.3f})",
                        leftState.angular_velocity.x, leftState.angular_velocity.y, leftState.angular_velocity.z,
                        rightState.angular_velocity.x, rightState.angular_velocity.y, rightState.angular_velocity.z);
            ApplyRightJoyConOrientation(rightState);

            state = leftState;
            state.angular_velocity.x = (leftState.angular_velocity.x + rightState.angular_velocity.x) * 0.5f;
            state.angular_velocity.y = (leftState.angular_velocity.y + rightState.angular_velocity.y) * 0.5f;
            state.angular_velocity.z = (leftState.angular_velocity.z + rightState.angular_velocity.z) * 0.5f;
            return leftState.delta_time > 0 || rightState.delta_time > 0;
        }

        if (controller.Gyro == GyroSource::Right && rightConnected) {
            hidGetSixAxisSensorStates(controller.Sensors[3], &state, 1);
            SPDLOG_INFO("RIGHT_GYRO_RAW x={:.3f} y={:.3f} z={:.3f}",
                        state.angular_velocity.x, state.angular_velocity.y, state.angular_velocity.z);
            ApplyRightJoyConOrientation(state);
            return state.delta_time > 0;
        }

        if (leftConnected) {
            hidGetSixAxisSensorStates(controller.Sensors[2], &state, 1);
            return state.delta_time > 0;
        }
        if (rightConnected) {
            hidGetSixAxisSensorStates(controller.Sensors[3], &state, 1);
            ApplyRightJoyConOrientation(state);
            return state.delta_time > 0;
        }
    }

    if (styleSet & HidNpadStyleTag_NpadJoyLeft) {
        hidGetSixAxisSensorStates(controller.Sensors[4], &state, 1);
        return state.delta_time > 0;
    }

    if (styleSet & HidNpadStyleTag_NpadJoyRight) {
        hidGetSixAxisSensorStates(controller.Sensors[5], &state, 1);
        ApplyRightJoyConOrientation(state);
        return state.delta_time > 0;
    }

    if (styleSet & (HidNpadStyleTag_NpadLucia | HidNpadStyleTag_NpadLagon |
                    HidNpadStyleTag_NpadLark | HidNpadStyleTag_NpadLager)) {
        int sensorIdx = -1;
        const char* tagName = "";
        if (styleSet & HidNpadStyleTag_NpadLucia) { sensorIdx = 6; tagName = "Lucia"; }
        else if (styleSet & HidNpadStyleTag_NpadLagon) { sensorIdx = 7; tagName = "Lagon"; }
        else if (styleSet & HidNpadStyleTag_NpadLark) { sensorIdx = 8; tagName = "Lark"; }
        else if (styleSet & HidNpadStyleTag_NpadLager) { sensorIdx = 9; tagName = "Lager"; }

        hidGetSixAxisSensorStates(controller.Sensors[sensorIdx], &state, 1);
        SPDLOG_INFO("THIRDPARTY_GYRO tag={} x={:.3f} y={:.3f} z={:.3f} delta_time={}",
                    tagName, state.angular_velocity.x, state.angular_velocity.y,
                    state.angular_velocity.z, state.delta_time);
        return state.delta_time > 0;
    }

    if (styleSet & HidNpadStyleTag_NpadFullKey) {
        hidGetSixAxisSensorStates(controller.Sensors[1], &state, 1);
        SPDLOG_INFO("FULLKEY_GYRO x={:.3f} y={:.3f} z={:.3f} delta_time={}",
                    state.angular_velocity.x, state.angular_velocity.y,
                    state.angular_velocity.z, state.delta_time);
        return state.delta_time > 0;
    }

    if (styleSet & HidNpadStyleTag_NpadHandheld) {
        hidGetSixAxisSensorStates(controller.Sensors[0], &state, 1);
        return state.delta_time > 0;
    }

    return false;
}

bool SwitchController::ReadGyro(uint8_t portIndex, float& pitch, float& yaw, float& roll) {
    HidSixAxisSensorState sixAxisState = {};
    if (!ReadSixAxisState(portIndex, sixAxisState)) {
        pitch = 0.0f;
        yaw = 0.0f;
        roll = 0.0f;
        return false;
    }

    pitch = sixAxisState.angular_velocity.x * 8.0f;
    yaw = sixAxisState.angular_velocity.y * 8.0f;
    roll = sixAxisState.angular_velocity.z * 8.0f;
    return true;
}

void SwitchController::SetGyroSource(uint8_t portIndex, GyroSource source) {
    if (portIndex >= mControllers.size()) {
        return;
    }
    mControllers[portIndex].Gyro = source;
}

GyroSource SwitchController::GetGyroSourceForPort(uint8_t portIndex) {
    if (portIndex >= mControllers.size()) {
        return GyroSource::Left;
    }
    return mControllers[portIndex].Gyro;
}

bool SwitchController::IsDetachableJoyConPair(uint8_t portIndex) {
    if (portIndex >= mControllers.size() || !EnsureInitialized(portIndex)) {
        return false;
    }
    auto& controller = mControllers[portIndex];
    padUpdate(&controller.State);
    const uint64_t styleSet = padGetStyleSet(&controller.State);
    return (styleSet & HidNpadStyleTag_NpadJoyDual) != 0;
}

void SwitchController::SendRumble(uint8_t portIndex, float lowFrequencyAmplitude, float highFrequencyAmplitude) {
    SPDLOG_INFO("SendRumble called: portIndex={}, low={}, high={}", portIndex, lowFrequencyAmplitude, highFrequencyAmplitude);
    if (!EnsureInitialized(portIndex)) {
        SPDLOG_INFO("SendRumble: EnsureInitialized failed for port {}", portIndex);
        return;
    }

    auto& controller = mControllers[portIndex];
    padUpdate(&controller.State);
    const uint64_t styleSet = padGetStyleSet(&controller.State);

    uint64_t externalStyle = 0;
    if (styleSet & HidNpadStyleTag_NpadFullKey) {
        externalStyle = HidNpadStyleTag_NpadFullKey;
    } else if (styleSet & HidNpadStyleTag_NpadJoyDual) {
        externalStyle = HidNpadStyleTag_NpadJoyDual;
    } else if (styleSet & HidNpadStyleTag_NpadGc) {
        externalStyle = HidNpadStyleTag_NpadGc;
    } else if (styleSet & HidNpadStyleTag_NpadLucia) {
        externalStyle = HidNpadStyleTag_NpadLucia;
    } else if (styleSet & HidNpadStyleTag_NpadLagon) {
        externalStyle = HidNpadStyleTag_NpadLagon;
    } else if (styleSet & HidNpadStyleTag_NpadLark) {
        externalStyle = HidNpadStyleTag_NpadLark;
    } else if (styleSet & HidNpadStyleTag_NpadLager) {
        externalStyle = HidNpadStyleTag_NpadLager;
    }

    if (externalStyle != 0 && controller.LastExternalRumbleStyle != externalStyle) {
        Result reinitResult = hidInitializeVibrationDevices(controller.Handles[1], 2, GetNpadId(portIndex),
                                      static_cast<HidNpadStyleTag>(externalStyle));
        SPDLOG_INFO("RUMBLE_CALIB reinit externalStyle={:#x} reinitResult={:#x} deviceType={:#x}",
                    externalStyle, reinitResult, hidGetNpadDeviceType(GetNpadId(portIndex)));
        controller.LastExternalRumbleStyle = externalStyle;
    }

    HidVibrationValue vibrationValues[2] = {};
    for (auto& value : vibrationValues) {
        value.amp_low = std::clamp(lowFrequencyAmplitude, 0.0f, 1.0f);
        value.amp_high = std::clamp(highFrequencyAmplitude, 0.0f, 1.0f);
        value.freq_low = 160.0f;
        value.freq_high = 320.0f;
    }

    SPDLOG_INFO("SendRumble: styleSet={:#x}, externalStyle={:#x}, isHandheld={}", styleSet, externalStyle, padIsHandheld(&controller.State));
    Result sendResult = 0;
    if (externalStyle != 0) {
        sendResult = hidSendVibrationValues(controller.Handles[1], vibrationValues, 2);
        SPDLOG_INFO("SendRumble: sent via Handles[1] (external), result={:#x}", sendResult);
    } else if (padIsHandheld(&controller.State)) {
        sendResult = hidSendVibrationValues(controller.Handles[0], vibrationValues, 2);
        SPDLOG_INFO("SendRumble: sent via Handles[0] (handheld), result={:#x}", sendResult);
    } else {
        SPDLOG_INFO("SendRumble: NO PATH TAKEN - neither handheld nor externalStyle set");
    }
}

bool SwitchController::IsNpadConnected(uint8_t portIndex) const {
    if (portIndex >= mControllers.size()) {
        return false;
    }
    PadState pad = {};
    const auto npadId = GetNpadId(portIndex);
    if (portIndex == 0) {
        padInitializeWithMask(&pad, (CONTROLLER_MASK << npadId) | (CONTROLLER_MASK << HidNpadIdType_Handheld));
    } else {
        padInitializeWithMask(&pad, CONTROLLER_MASK << npadId);
    }
    padUpdate(&pad);
    return padIsConnected(&pad);
}

std::string SwitchController::GetControllerName(uint8_t portIndex) {
    if (!EnsureInitialized(portIndex)) {
        return "Controller";
    }

    auto& controller = mControllers[portIndex];
    padUpdate(&controller.State);
    const uint32_t styleSet = padGetStyleSet(&controller.State);
    const uint32_t deviceType = hidGetNpadDeviceType(GetNpadId(portIndex));

    if (styleSet & HidNpadStyleTag_NpadHandheld) {
        return "Handheld";
    }
    if (styleSet & HidNpadStyleTag_NpadGc) {
        return "GameCube Controller";
    }

    // Style sets are not precise enough for the other types
    if (deviceType & HidDeviceTypeBits_FullKey) {
        return "Pro Controller";
    }
    if (deviceType & HidDeviceTypeBits_DebugPad) {
        return "DebugPad";
    }
    if (deviceType & HidDeviceTypeBits_Palma) {
        return "Poke Ball Plus";
    }
    if (deviceType & HidDeviceTypeBits_Lucia) {
        return "SNES Controller";
    }
    if (deviceType & HidDeviceTypeBits_Lagon) {
        return "N64 Controller";
    }
    if (deviceType & HidDeviceTypeBits_Lager) {
        return "Genesis Controller";
    }
    if (deviceType & HidDeviceTypeBits_System) {
        return "Generic Controller";
    }
#define DETECT_LR_CONTROLLER(deviceType, name, leftBits, rightBits)      \
    if ((deviceType) & ((leftBits) | (rightBits))) {                     \
        bool l = (deviceType) & (leftBits);                              \
        bool r = (deviceType) & (rightBits);                             \
        return (l && r) ? name " (L+R)" : l ? name " (L)" : name " (R)"; \
    }

    DETECT_LR_CONTROLLER(deviceType, "Joy-Con", HidDeviceTypeBits_JoyLeft, HidDeviceTypeBits_JoyRight)
    DETECT_LR_CONTROLLER(deviceType, "Famicom Controller",
                         HidDeviceTypeBits_LarkHvcLeft | HidDeviceTypeBits_HandheldLarkHvcLeft,
                         HidDeviceTypeBits_LarkHvcRight | HidDeviceTypeBits_HandheldLarkHvcRight)
    DETECT_LR_CONTROLLER(deviceType, "NES Controller",
                         HidDeviceTypeBits_LarkNesLeft | HidDeviceTypeBits_HandheldLarkNesLeft,
                         HidDeviceTypeBits_LarkNesRight | HidDeviceTypeBits_HandheldLarkNesRight)

    return "Unknown Controller";
}

std::string SwitchController::GetControllerSerial(uint8_t npadIndex) {
    if (npadIndex >= mControllers.size()) {
        return StringHelper::Sprintf("NPAD%d", npadIndex);
    }

    if (!EnsureInitialized(npadIndex)) {
        return StringHelper::Sprintf("NPAD%d", npadIndex);
    }

    auto& controller = mControllers[npadIndex];
    padUpdate(&controller.State);

    HidNpadIdType queryIds[2];
    int queryCount;
    if (npadIndex == 0) {
        queryIds[0] = GetNpadId(0);
        queryIds[1] = HidNpadIdType_Handheld;
        queryCount = 2;
    } else {
        queryIds[0] = GetNpadId(npadIndex);
        queryCount = 1;
    }

    for (int q = 0; q < queryCount; q++) {
        HidsysUniquePadId uniquePadIds[2] = {};
        s32 total = 0;
        Result rc = hidsysGetUniquePadsFromNpad(queryIds[q], uniquePadIds, 2, &total);
        if (R_FAILED(rc) || total <= 0) {
            continue;
        }

        HidsysUniquePadSerialNumber serial = {};
        rc = hidsysGetUniquePadSerialNumber(uniquePadIds[0], &serial);
        if (R_SUCCEEDED(rc) && serial.serial_number[0] != '\0') {
            return serial.serial_number;
        }
    }

    return StringHelper::Sprintf("NPAD%d", npadIndex);
}

} // namespace Ship
#endif