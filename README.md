# 2 Ship 2 Harkinian – Switch PAL

**English** · [Français](README.fr.md) · [Deutsch](README.de.md) · [Español](README.es.md)

[![switch-build](https://github.com/Desperadas-G/2ship2harkinian-Switch-PAL/actions/workflows/switch.yml/badge.svg)](https://github.com/Desperadas-G/2ship2harkinian-Switch-PAL/actions/workflows/switch.yml)

An unofficial Nintendo Switch port of [2 Ship 2 Harkinian](https://github.com/2ship2harkinian/2ship2harkinian) (2S2H) that also runs the **European (PAL 1.1) version of *The Legend of Zelda: Majora's Mask***, with its four languages: **English, French, German and Spanish**.

It runs as homebrew on a Switch with the [Atmosphère](https://github.com/Atmosphere-NX/Atmosphere) custom firmware.

> This project is not affiliated with Nintendo, HarbourMasters or the 2Ship team. Please don't ask the official 2Ship Discord for support with this fork. Use this repository's [issues](../../issues) instead.

## ⚖️ Legal notice / Mentions légales

- **This repository contains no ROM and no Nintendo assets**, and its releases never will. It only contains source code, which is not a copy of the game: the game's code was decompiled and rewritten as C by the [zeldaret/mm](https://github.com/zeldaret/mm) project.
- **You must own a legitimate copy of *The Legend of Zelda: Majora's Mask*** and dump it **from your own cartridge** (or your own GameCube disc for the US GC version). The game data (`mm.o2r`) is generated on your own computer, from your own dump.
- **Do not ask for ROMs, and never share ROMs or `mm.o2r` files**, here or anywhere else. Issues, pull requests or comments that link to ROMs, or ask for them, will be closed and deleted.
- Downloading a ROM of a game you do not own is piracy and illegal in most countries. We do not condone piracy.
- This is a non-commercial fan project. It is not affiliated with, endorsed or sponsored by Nintendo. *The Legend of Zelda* and *Majora's Mask* are trademarks of Nintendo.
## Based on

| Component | Version |
|---|---|
| 2 Ship 2 Harkinian | **5.0.1 "Battler Bravo"** |
| Switch port | [starshopper612/2ship2harkinian-Switch](https://github.com/starshopper612/2ship2harkinian-Switch) `switch-5.0.1-v3` (gyro and rumble) |
| PAL 1.1 support | [2ship2harkinian#1966](https://github.com/2ship2harkinian/2ship2harkinian/pull/1966) by alexbcz ([alexbcz/2ship2harkinian-PAL](https://github.com/alexbcz/2ship2harkinian-PAL)) |

## Supported ROMs

2Ship contains **no** copyrighted assets. You must dump your own cartridge.

| Version | Supported | Header CRC | SHA-1 (`.z64`) |
|---|---|---|---|
| **PAL 1.1 / Rev A** (Europe, En/Fr/De/Es) | ✅ | `0A5D8F83` | `bb4e4757d10727c7584c59c1f2e5f44196e9c293` |
| NTSC-U 1.0 (USA) | ✅ | `5354631C` | `d6133ace5afaa0882cf214cf88daba39e266c078` |
| NTSC-U GameCube (Collector's Edition) | ✅ | `B443EB08` | `9743aa026e9269b339eb0e3044cd5830a440c1fd` |
| PAL 1.0 (first European release) | ❌ | `E97955C6` | – |
| Japanese versions, PAL GameCube, *Majora's Mask 3D* | ❌ | – | – |

PAL 1.0 and 1.1 cartridges look the same. The header CRC (bytes `0x10`–`0x13` of a `.z64` dump) tells them apart. The Windows generator and `tools/generate-o2r.sh` check it for you. Byte-swapped dumps (`.v64`, `.n64`) are converted automatically.

Patched or translated ROMs (fan translations, hacks) are not supported.

## Installation

### 1. Get the files

**On Windows**, download `2Ship-Switch-PAL-vX.Y.Z-windows.zip` from [Releases](../../releases) and extract it. It contains the Switch files and a ready-to-use `mm.o2r` generator: nothing to install.

On other systems, download `2ship.nro` and `2ship.o2r` from [Releases](../../releases), or [build them yourself](docs/BUILDING_SWITCH.md).

### 2. Generate `mm.o2r` from your ROM

`mm.o2r` holds the game's assets, extracted from your ROM.

**Windows:** drop your ROM (`.z64`, `.n64`, `.v64`, or the `.zip` it came in) onto **`Generate mm.o2r.bat`**. After about a minute, `switch\2s2h\mm.o2r` is created: copy the whole `switch` folder to the root of your SD card and skip to step 4.

**Linux or WSL:**

```bash
git clone <this repository>
cd 2ship2harkinian-Switch-PAL
tools/generate-o2r.sh /path/to/your/rom.z64
```

Install the dependencies first. They are listed in [docs/BUILDING_SWITCH.md](docs/BUILDING_SWITCH.md#1-host-dependencies).

`mm.o2r` must be generated from the **same version** of this repository as the `2ship.nro` you use. Never share your `mm.o2r`: it contains the game's copyrighted data.

### 3. Copy to the SD card

```
sdmc:/switch/2s2h/
├── 2ship.nro
├── 2ship.o2r
└── mm.o2r
```

### 4. Launch

Open the Homebrew Menu by **holding R while launching a game** (title override). Don't launch it from the Album applet: applet mode has too little memory and the game will crash or refuse to start.

### 5. Choose your language (PAL only)

Pick the language in the game's options. The choice is saved.

<img src="docs/screenshots/options-language.jpg" width="640" alt="In-game Options screen of the PAL version, with the four languages: English, Deutsch, Français, Español">

_The PAL Options screen on Switch (French selected)._

## Controls

- **Minus (−)** opens the 2Ship menu (enhancements, cheats, settings).
- **Gyro aiming** and **rumble** work with Joy-Cons, the Pro Controller and compatible third-party controllers. You can choose the gyro source (left, right or both Joy-Cons) in the controller settings.

When you create a save, 2Ship 5.x asks you to pick **Vanilla** or **Randomizer**, then an options preset (*None*, *Curated*, *Defaults*, *Voyage 3*). For the original experience, choose **Vanilla** with **Defaults**.

<img src="docs/screenshots/new-file-mode.jpg" width="640" alt="New File screen: options preset and Vanilla / Randomizer mode">

_The new file screen: options preset and Vanilla / Randomizer mode._

## Known limitations

- PAL support is new and comes from an upstream pull request that has not been merged yet. Some localized text or textures may still be wrong. Please [report them](../../issues/new/choose).
- PAL 1.0 isn't supported yet.
- The desktop builds (Windows/Linux/macOS) have not been tested in this fork.

## Building

See [docs/BUILDING_SWITCH.md](docs/BUILDING_SWITCH.md) for the Switch build, and [docs/BUILDING.md](docs/BUILDING.md) for the upstream desktop instructions.

## Contributing

Bug reports, fixes and improvements are welcome. Read [CONTRIBUTING.md](CONTRIBUTING.md) first.

## Credits

This fork only brings existing work together and adapts it for the Switch. All credit goes to:

- **[2 Ship 2 Harkinian](https://github.com/2ship2harkinian/2ship2harkinian)**: the HarbourMasters / 2Ship team and contributors (the PC port this is built on).
- **[zeldaret/mm](https://github.com/zeldaret/mm)**: the *Majora's Mask* decompilation that made the port possible.
- **[libultraship](https://github.com/Kenix3/libultraship)** (Kenix3 and contributors), **[ZAPDTR](https://github.com/HarbourMasters/ZAPDTR)** and **[OTRExporter](https://github.com/HarbourMasters/OTRExporter)** (HarbourMasters): the engine and asset tools.
- **[YoshiCrystal9/2ship2harkinian-Switch](https://github.com/YoshiCrystal9/2ship2harkinian-Switch)**: the original Switch port, and the Switch icon.
- **[starshopper612/2ship2harkinian-Switch](https://github.com/starshopper612/2ship2harkinian-Switch)** (formerly reflex909): the 5.0.1 forward-port, gyro, rumble and controller fixes, and the Switch forks of libultraship, OTRExporter and ZAPDTR.
- **[timschneeb](https://github.com/timschneeb)**: the Switch gyro and rumble code (from Shipwright-Switch).
- **[alexbcz](https://github.com/alexbcz)**: PAL 1.1 support ([2ship2harkinian#1966](https://github.com/2ship2harkinian/2ship2harkinian/pull/1966), [2ship2harkinian-PAL](https://github.com/alexbcz/2ship2harkinian-PAL)) and the matching libultraship, OTRExporter and ZAPDTR changes.
- **[inspectredc](https://github.com/inspectredc)**: earlier PAL work ([2ship2harkinian#1231](https://github.com/2ship2harkinian/2ship2harkinian/pull/1231), ZAPDTR/OTRExporter MM PAL support).
- **[devkitPro](https://devkitpro.org)**: the Switch toolchain and libnx.

See [docs/SOURCES.md](docs/SOURCES.md) for the exact commits used.

## License

Same licenses as the upstream projects: see [LICENSE](LICENSE), and `libultraship/LICENSE`, `OTRExporter/LICENSE` and `ZAPDTR/LICENSE` for the bundled components.

*The Legend of Zelda: Majora's Mask* is © Nintendo. This repository contains no game assets.

<a href="https://github.com/Kenix3/libultraship/">
  <picture>
    <source media="(prefers-color-scheme: dark)" srcset="./docs/poweredbylus.darkmode.png">
    <img alt="Powered by libultraship" src="./docs/poweredbylus.lightmode.png">
  </picture>
</a>
