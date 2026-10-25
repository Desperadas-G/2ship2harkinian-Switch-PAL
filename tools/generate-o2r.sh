#!/usr/bin/env bash
# Generates mm.o2r (from your own ROM dump) and 2ship.o2r for the Switch build.
#
# Usage: tools/generate-o2r.sh /path/to/your/rom.(z64|n64|v64) [output_dir]
#
# Runs on Linux or WSL. Needs the host build dependencies listed in
# docs/BUILDING_SWITCH.md (cmake, ninja, a C++ compiler, python3, libpng,
# libzip, SDL2, ...).
set -euo pipefail

if [ $# -lt 1 ]; then
    echo "Usage: $0 /path/to/rom.(z64|n64|v64) [output_dir]" >&2
    exit 1
fi

ROM_IN="$(realpath "$1")"
REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
OUT_DIR="$(realpath -m "${2:-$REPO_ROOT/out}")"
BUILD_DIR="$REPO_ROOT/build-host"
ROM_OUT="$REPO_ROOT/OTRExporter/baserom.z64"

# Convert to big-endian .z64 if the dump is byte-swapped (.v64) or little-endian (.n64).
python3 - "$ROM_IN" "$ROM_OUT" <<'PY'
import sys
src, dst = sys.argv[1], sys.argv[2]
data = bytearray(open(src, "rb").read())
magic = bytes(data[:4])
if magic == b"\x80\x37\x12\x40":
    pass
elif magic == b"\x37\x80\x40\x12":
    data[0::2], data[1::2] = data[1::2], data[0::2]
elif magic == b"\x40\x12\x37\x80":
    for i in range(0, len(data), 4):
        data[i:i + 4] = data[i:i + 4][::-1]
else:
    sys.exit("Unrecognized ROM format (magic %s)" % magic.hex())
crc = data[0x10:0x14].hex().upper()
names = {"0A5D8F83": "PAL 1.1 (Rev A)", "5354631C": "NTSC-U 1.0", "B443EB08": "NTSC-U GameCube",
         "E97955C6": "PAL 1.0 (NOT SUPPORTED)"}
print("ROM header CRC: %s -> %s" % (crc, names.get(crc, "unknown / unsupported")))
if crc not in ("0A5D8F83", "5354631C", "B443EB08"):
    sys.exit("This ROM version is not supported.")
open(dst, "wb").write(data)
PY

cleanup() { rm -f "$ROM_OUT"; }
trap cleanup EXIT

cmake -S "$REPO_ROOT" -B "$BUILD_DIR" -GNinja -DCMAKE_BUILD_TYPE=Release
cmake --build "$BUILD_DIR" --target ZAPD -j"$(nproc)"
cmake --build "$BUILD_DIR" --target ExtractAssets

mkdir -p "$OUT_DIR"
cp "$REPO_ROOT/mm.o2r" "$REPO_ROOT/2ship.o2r" "$OUT_DIR/"
echo
echo "Done. Copy these files next to 2ship.nro on your SD card (sdmc:/switch/2s2h/):"
ls -la "$OUT_DIR"/mm.o2r "$OUT_DIR"/2ship.o2r
