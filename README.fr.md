# 2 Ship 2 Harkinian – Switch PAL

[English](README.md) · **Français** · [Deutsch](README.de.md) · [Español](README.es.md)

[![switch-build](https://github.com/Desperadas-G/2ship2harkinian-Switch-PAL/actions/workflows/switch.yml/badge.svg)](https://github.com/Desperadas-G/2ship2harkinian-Switch-PAL/actions/workflows/switch.yml)

*Majora's Mask* sur Nintendo Switch (Atmosphère) avec [2 Ship 2 Harkinian](https://github.com/2ship2harkinian/2ship2harkinian), avec en plus la **version européenne PAL 1.1** (anglais, français, allemand, espagnol).

## Installation

1. Télécharge **`2Ship-Switch-PAL-vX.Y.Z.zip`** depuis la [dernière release](../../releases/latest) et décompresse-le.
2. Crée les données du jeu à partir de ta ROM : sur un PC, glisse ta ROM (`.z64`, `.n64`, `.v64` ou `.zip`) sur **`Generate mm.o2r.bat`** et attends environ une minute.
3. Copie le dossier **`switch`** à la racine de ta carte SD.
4. Maintiens **R** en lançant n'importe quel jeu pour ouvrir le Homebrew Menu, puis lance **2 Ship 2 Harkinian**.

Ne le lance pas depuis l'Album : le mode applet n'a pas assez de mémoire.

**Mise à jour :** remplace `2ship.nro` et `2ship.o2r`. Ton `mm.o2r` et tes sauvegardes restent.

`Generate mm.o2r.bat` fonctionne sous Windows. Sous Linux ou macOS, utilise plutôt `tools/generate-o2r.sh` ([docs/BUILDING_SWITCH.md](docs/BUILDING_SWITCH.md)).

## ROMs compatibles

| Version | CRC d'en-tête |
|---|---|
| PAL 1.1 / Rev A (Europe, En/Fr/De/Es) ✅ | `0A5D8F83` |
| NTSC-U 1.0 (USA) ✅ | `5354631C` |
| NTSC-U GameCube ✅ | `B443EB08` |
| PAL 1.0, versions japonaises, hacks et traductions ❌ | – |

Le générateur vérifie ta ROM et te prévient si elle n'est pas compatible.

## ⚖️ Mentions légales

- Aucune ROM ni aucune donnée Nintendo n'est incluse, ni ici ni dans les releases. Tu dois faire le dump de **ta propre** cartouche.
- Ne partage jamais de ROM ni ton `mm.o2r`. Les demandes et les liens seront supprimés.
- Projet de fan non commercial, sans lien avec Nintendo. *The Legend of Zelda: Majora's Mask* est © Nintendo.

## Crédits

Basé sur 2Ship **5.0.1 « Battler Bravo »**. Ce fork ne fait que rassembler des travaux existants :

- [2 Ship 2 Harkinian](https://github.com/2ship2harkinian/2ship2harkinian) : l'équipe HarbourMasters / 2Ship et ses contributeurs
- [zeldaret/mm](https://github.com/zeldaret/mm) : la décompilation de *Majora's Mask*
- [libultraship](https://github.com/Kenix3/libultraship) (Kenix3), [ZAPDTR](https://github.com/HarbourMasters/ZAPDTR) et [OTRExporter](https://github.com/HarbourMasters/OTRExporter) (HarbourMasters)
- [YoshiCrystal9](https://github.com/YoshiCrystal9/2ship2harkinian-Switch) : le premier portage Switch et l'icône
- [starshopper612](https://github.com/starshopper612/2ship2harkinian-Switch) (ex-reflex909) : le portage Switch 5.0.1, le gyroscope, les vibrations, les manettes
- [timschneeb](https://github.com/timschneeb) : le code gyroscope et vibrations (Shipwright-Switch)
- [alexbcz](https://github.com/alexbcz) : le support PAL 1.1 ([2ship2harkinian#1966](https://github.com/2ship2harkinian/2ship2harkinian/pull/1966))
- [inspectredc](https://github.com/inspectredc) : les premiers travaux PAL ([2ship2harkinian#1231](https://github.com/2ship2harkinian/2ship2harkinian/pull/1231))
- [devkitPro](https://devkitpro.org) : la toolchain Switch et libnx

Commits exacts : [docs/SOURCES.md](docs/SOURCES.md). Licence : [LICENSE](LICENSE), plus `libultraship/`, `OTRExporter/` et `ZAPDTR/LICENSE`.

<a href="https://github.com/Kenix3/libultraship/">
  <picture>
    <source media="(prefers-color-scheme: dark)" srcset="./docs/poweredbylus.darkmode.png">
    <img alt="Powered by libultraship" src="./docs/poweredbylus.lightmode.png">
  </picture>
</a>
