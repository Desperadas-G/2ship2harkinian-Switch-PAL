# 2 Ship 2 Harkinian – Switch PAL

**English** · [Français](README.fr.md) · [Deutsch](README.de.md) · [Español](README.es.md)

[![switch-build](https://github.com/Desperadas-G/2ship2harkinian-Switch-PAL/actions/workflows/switch.yml/badge.svg)](https://github.com/Desperadas-G/2ship2harkinian-Switch-PAL/actions/workflows/switch.yml)

*Majora's Mask* on Nintendo Switch (Atmosphère) with [2 Ship 2 Harkinian](https://github.com/2ship2harkinian/2ship2harkinian), now with the **European PAL 1.1 version** (English, French, German, Spanish).

## Installation

1. Download **`2Ship-Switch-PAL-vX.Y.Z.zip`** from the [latest release](../../releases/latest) and extract it.
2. Create the game data from your ROM: on a PC, drop your ROM (`.z64`, `.n64`, `.v64` or `.zip`) onto **`Generate mm.o2r.bat`** and wait about a minute.
3. Copy the **`switch`** folder to the root of your SD card.
4. Hold **R** while launching any game to open the Homebrew Menu, then start **2 Ship 2 Harkinian**.

Don't launch it from the Album: applet mode doesn't have enough memory.

**Updating:** replace `2ship.nro` and `2ship.o2r`. Your `mm.o2r` and your saves stay.

`Generate mm.o2r.bat` runs on Windows. On Linux or macOS, use `tools/generate-o2r.sh` instead ([docs/BUILDING_SWITCH.md](docs/BUILDING_SWITCH.md)).

## Supported ROMs

| Version | Header CRC |
|---|---|
| PAL 1.1 / Rev A (Europe, En/Fr/De/Es) ✅ | `0A5D8F83` |
| PAL 1.0, Japanese versions, hacks and translations ❌ | – |

The generator checks your ROM and tells you if it isn't supported.

## ⚖️ Legal

- No ROM and no Nintendo assets are included, here or in the releases. You must dump **your own** cartridge.
- Never share ROMs or your `mm.o2r`. Requests and links will be deleted.
- A non-commercial fan project, not affiliated with Nintendo. *The Legend of Zelda: Majora's Mask* is © Nintendo.

## Credits

Based on 2Ship **5.0.1 "Battler Bravo"**. This fork only brings existing work together:

- [2 Ship 2 Harkinian](https://github.com/2ship2harkinian/2ship2harkinian): HarbourMasters / 2Ship team and contributors
- [zeldaret/mm](https://github.com/zeldaret/mm): the *Majora's Mask* decompilation
- [libultraship](https://github.com/Kenix3/libultraship) (Kenix3), [ZAPDTR](https://github.com/HarbourMasters/ZAPDTR) and [OTRExporter](https://github.com/HarbourMasters/OTRExporter) (HarbourMasters)
- [YoshiCrystal9](https://github.com/YoshiCrystal9/2ship2harkinian-Switch): original Switch port and icon
- [starshopper612](https://github.com/starshopper612/2ship2harkinian-Switch) (ex-reflex909): 5.0.1 Switch port, gyro, rumble, controllers
- [timschneeb](https://github.com/timschneeb): gyro and rumble code (Shipwright-Switch)
- [alexbcz](https://github.com/alexbcz): PAL 1.1 support ([2ship2harkinian#1966](https://github.com/2ship2harkinian/2ship2harkinian/pull/1966))
- [inspectredc](https://github.com/inspectredc): earlier PAL work ([2ship2harkinian#1231](https://github.com/2ship2harkinian/2ship2harkinian/pull/1231))
- [devkitPro](https://devkitpro.org): Switch toolchain and libnx

Exact commits: [docs/SOURCES.md](docs/SOURCES.md). License: [LICENSE](LICENSE), plus `libultraship/`, `OTRExporter/` and `ZAPDTR/LICENSE`.

<a href="https://github.com/Kenix3/libultraship/">
  <picture>
    <source media="(prefers-color-scheme: dark)" srcset="./docs/poweredbylus.darkmode.png">
    <img alt="Powered by libultraship" src="./docs/poweredbylus.lightmode.png">
  </picture>
</a>
