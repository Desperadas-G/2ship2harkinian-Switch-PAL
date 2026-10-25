# Contributing

Thanks for helping! Bug reports, fixes, translations and improvements are all welcome.

## Ground rules

- **No ROMs, no game data.** Never attach, link or ask for ROMs, `mm.o2r` files, or assets extracted from the game. Issues and pull requests that do will be closed and deleted.
- Be respectful. This is a hobby project built on the work of many people. See [docs/SOURCES.md](docs/SOURCES.md).
- Don't ask the official 2Ship / HarbourMasters Discord about this fork. Problems specific to the Switch or PAL belong here.

## Reporting a bug

Use the **Bug report** template and include:

- the ROM version (PAL 1.1, NTSC-U 1.0 or NTSC-U GC). The header CRC or SHA-1 is enough;
- the release or commit of this repository you used;
- your Switch model, firmware and Atmosphère versions;
- how you launched it (title override with R, or applet mode);
- steps to reproduce, and a photo or screenshot if something looks wrong;
- the language selected (PAL), when the problem is text or texture related.

Before reporting, check whether the bug also happens on the official PC version of 2Ship 5.0.1. If it does, it's an upstream bug, and it's better reported to [2ship2harkinian](https://github.com/2ship2harkinian/2ship2harkinian/issues).

## Pull requests

1. Fork the repository and create a branch from `main`.
2. Keep each pull request focused on one fix or feature.
3. Build the Switch version (see [docs/BUILDING_SWITCH.md](docs/BUILDING_SWITCH.md)) and test on hardware if you can. Say in the PR description what you tested.
4. Format C/C++ changes with `clang-format` (`./run-clang-format.sh`).
5. If your change also makes sense for upstream 2Ship (not specific to the Switch), consider sending it there as well. Please follow their contribution rules, including their policy on disclosing AI-generated content.

## Project layout

| Path | Content |
|---|---|
| `mm/` | The game (decompiled code) and the 2Ship port layer (`mm/2s2h`) |
| `mm/assets/xml/MM_PAL_11/` | Asset definitions for the PAL 1.1 ROM |
| `mm/2s2h/PalAssetLocalization.h` | Mapping between English assets and their PAL language variants |
| `libultraship/` | Engine (rendering, audio, input, resource manager), including the Switch platform code |
| `ZAPDTR/`, `OTRExporter/` | ROM asset extraction tools (run on PC) |
| `tools/generate-o2r.sh` | Generates `mm.o2r` and `2ship.o2r` from a ROM dump |
