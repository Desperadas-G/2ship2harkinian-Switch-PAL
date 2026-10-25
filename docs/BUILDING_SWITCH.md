# Building for Nintendo Switch

The Switch build has two parts:

1. **Host tools (Linux/WSL)**: build `ZAPD` for your PC and use it to generate `mm.o2r` (from your ROM) and `2ship.o2r` (the port's own assets).
2. **Switch executable**: cross-compile `2ship.nro` with devkitPro (devkitA64 + libnx + Switch portlibs).

Everything below was tested on Ubuntu 24.04 (also under WSL2 on Windows 10).

## 1. Host dependencies

```bash
sudo apt-get update
sudo apt-get install -y build-essential cmake ninja-build git python3 pkg-config lsb-release \
  libusb-dev libusb-1.0-0-dev libsdl2-dev libsdl2-net-dev libpng-dev libglew-dev nlohmann-json3-dev \
  libtinyxml2-dev libspdlog-dev libogg-dev libopus-dev opus-tools libopusfile-dev libvorbis-dev \
  libzip-dev zipcmp zipmerge ziptool libbz2-dev zlib1g-dev
```

## 2. Generate `mm.o2r` and `2ship.o2r`

```bash
tools/generate-o2r.sh /path/to/your/rom.z64
```

The script accepts `.z64`, `.v64` and `.n64` dumps, checks the ROM version, builds `ZAPD` in `build-host/` and writes both archives to `out/`.

To build only `2ship.o2r` (no ROM needed):

```bash
cmake -S . -B build-host -GNinja -DCMAKE_BUILD_TYPE=Release
cmake --build build-host --target Generate2ShipOtr
```

## 3. Build `2ship.nro`

### Option A: Docker (recommended)

The official `devkitpro/devkita64` image already contains devkitA64, libnx and the Switch portlibs.

```bash
docker run --rm -v "$PWD":/src -w /src devkitpro/devkita64:latest bash -c '
  git config --global --add safe.directory "*"
  /opt/devkitpro/portlibs/switch/bin/aarch64-none-elf-cmake -S . -B build-switch -GNinja -DCMAKE_BUILD_TYPE=Release
  cmake --build build-switch -j$(nproc)
'
```

The result is `build-switch/mm/2ship.nro`.

### Option B: native devkitPro

Install devkitPro pacman by following the [devkitPro instructions](https://devkitpro.org/wiki/Getting_Started), then:

```bash
sudo dkp-pacman -S switch-dev switch-portlibs switch-cmake
source /etc/profile.d/devkit-env.sh
/opt/devkitpro/portlibs/switch/bin/aarch64-none-elf-cmake -S . -B build-switch -GNinja -DCMAKE_BUILD_TYPE=Release
cmake --build build-switch -j$(nproc)
```

## 4. Install on the SD card

```
sdmc:/switch/2s2h/
├── 2ship.nro
├── 2ship.o2r
└── mm.o2r
```

`mm.o2r` and `2ship.o2r` must come from the **same source tree** as `2ship.nro`. The game refuses archives made by a different 2Ship version.

## PC builds

The desktop builds (Windows, Linux, macOS) still use the upstream instructions in [BUILDING.md](BUILDING.md). They have not been tested in this fork.
