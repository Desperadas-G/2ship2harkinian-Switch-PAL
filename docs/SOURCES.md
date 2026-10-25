# Sources

This repository is assembled from the following upstream code. Commit hashes refer to the original repositories.

## Main tree

| Source | Ref | What was taken |
|---|---|---|
| [2ship2harkinian/2ship2harkinian](https://github.com/2ship2harkinian/2ship2harkinian) | tag `5.0.1` (`8a24047fbce8915993804e7819f4df4fa591551f`) | 2S2H 5.0.1 "Battler Bravo", the base of everything below (full history kept) |
| [starshopper612/2ship2harkinian-Switch](https://github.com/starshopper612/2ship2harkinian-Switch) | `main` at `e1b0436d3c580e193d68fe9dbc915522074aff32` (tag `switch-5.0.1-v3` + submodule URL update) | Switch port forward-ported to 5.0.1: gyro, rumble, controller and performance fixes (full history kept) |
| [2ship2harkinian#1966](https://github.com/2ship2harkinian/2ship2harkinian/pull/1966) by alexbcz | `91f3a9fac1f2…` to `b4d0cc5d020b…` | The 15 PAL 1.1 commits, cherry-picked onto 5.0.1 with their original authorship. The 42 `develop` commits the PR branch was based on were **not** taken. |
| [YoshiCrystal9/2ship2harkinian-Switch](https://github.com/YoshiCrystal9/2ship2harkinian-Switch) | `eabe382b63ed2d2accfa64644d629856c1085436` | `mm/switch/2s2hIcon.png`, which the 5.0.1 forward-port had lost because a `.gitignore` rule matches it |

## Bundled components (formerly submodules)

| Directory | Base | Added on top |
|---|---|---|
| `libultraship/` | [starshopper612/libultraship](https://github.com/starshopper612/libultraship) `93893160770a676f59f3dc1dc3e1222fe7a8d4c1` (branch `gyro-rumble-fix`) | `c8e2542a` "feat: add resource path resolver" from [alexbcz/libultraship](https://github.com/alexbcz/libultraship) (same change as Kenix3/libultraship#1301) |
| `OTRExporter/` | [starshopper612/OTRExporter](https://github.com/starshopper612/OTRExporter) `90bf912934d58bcfbfc2ae126da1df471082cbe3` | `8c97155` "feat: add Majora's Mask PAL 1.1 ROM metadata" from [alexbcz/OTRExporter](https://github.com/alexbcz/OTRExporter); `rom_info.py` PAL 1.1 entry renamed to `MM_PAL_11` |
| `ZAPDTR/` | [starshopper612/ZAPDTR](https://github.com/starshopper612/ZAPDTR) `37c7462432d2d329d1cba12574df9477684f6584` | `a7280b0` "feat: add Majora's Mask PAL 1.1 extraction support" and `fbf7265` "Propagate extraction failures from ZAPD" from [alexbcz/ZAPDTR](https://github.com/alexbcz/ZAPDTR) (the second one adapted, because this ZAPDTR has no extraction progress counter) |

## Changes made in this repository

- `mm/2s2h/BenPort.cpp`: the PAL extraction error path calls `Extractor::GetLastError()`, but the extractor isn't compiled on Switch/Wii U, so that call is now guarded.
- `mm/assets/xml/MM_PAL_11/text/message_data_static*.xml`: the PR uses the `SegmentName` form meant for upstream ZAPDTR. These files now use the `CodeFile` + `CodeOffset` form that the bundled ZAPDTR expects, as in the [PAL 1.1 v1.0.0 release](https://github.com/alexbcz/2ship2harkinian-PAL/releases).
- `tools/generate-o2r.sh`, `docs/BUILDING_SWITCH.md` and the Switch CI workflow: build and asset-generation tooling for the Switch.
- PAL 1.1 SHA-1 added to `docs/supportedHashes.json`.
