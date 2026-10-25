# 2 Ship 2 Harkinian – Switch PAL

[English](README.md) · **Français** · [Deutsch](README.de.md) · [Español](README.es.md)

[![switch-build](https://github.com/Desperadas-G/2ship2harkinian-Switch-PAL/actions/workflows/switch.yml/badge.svg)](https://github.com/Desperadas-G/2ship2harkinian-Switch-PAL/actions/workflows/switch.yml)

Un portage non officiel pour Nintendo Switch de [2 Ship 2 Harkinian](https://github.com/2ship2harkinian/2ship2harkinian) (2S2H), qui fait aussi tourner la **version européenne (PAL 1.1) de *The Legend of Zelda: Majora's Mask*** dans ses quatre langues : **anglais, français, allemand et espagnol**.

Il s'utilise comme homebrew sur une Switch équipée du custom firmware [Atmosphère](https://github.com/Atmosphere-NX/Atmosphere).

> Ce projet n'est affilié ni à Nintendo, ni à HarbourMasters, ni à l'équipe de 2Ship. Merci de ne pas demander d'aide pour ce fork sur le Discord officiel de 2Ship. Utilise plutôt les [issues](../../issues) de ce dépôt.

## ⚖️ Mentions légales

- **Ce dépôt ne contient aucune ROM ni aucune donnée de Nintendo**, et ses releases n'en contiendront jamais. Il ne contient que du code source, qui n'est pas une copie du jeu : le code du jeu a été décompilé et réécrit en C par le projet [zeldaret/mm](https://github.com/zeldaret/mm).
- **Tu dois posséder un exemplaire légitime de *The Legend of Zelda: Majora's Mask*** et en faire le dump **à partir de ta propre cartouche** (ou de ton propre disque GameCube pour la version US GC). Les données du jeu (`mm.o2r`) sont générées sur ton propre ordinateur, à partir de ton dump.
- **Ne demande pas de ROM, et ne partage jamais de ROM ni de fichier `mm.o2r`**, ici ou ailleurs. Les issues, pull requests ou commentaires qui contiennent un lien vers une ROM, ou qui en demandent, seront fermés et supprimés.
- Télécharger la ROM d'un jeu que l'on ne possède pas, c'est du piratage, illégal dans la plupart des pays. Nous ne cautionnons pas le piratage.
- Ce projet amateur est non commercial. Il n'est ni affilié à Nintendo, ni approuvé ou sponsorisé par Nintendo. *The Legend of Zelda* et *Majora's Mask* sont des marques de Nintendo.

## Basé sur

| Composant | Version |
|---|---|
| 2 Ship 2 Harkinian | **5.0.1 « Battler Bravo »** |
| Portage Switch | [starshopper612/2ship2harkinian-Switch](https://github.com/starshopper612/2ship2harkinian-Switch) `switch-5.0.1-v3` (gyroscope et vibrations) |
| Support PAL 1.1 | [2ship2harkinian#1966](https://github.com/2ship2harkinian/2ship2harkinian/pull/1966) par alexbcz ([alexbcz/2ship2harkinian-PAL](https://github.com/alexbcz/2ship2harkinian-PAL)) |

## ROMs compatibles

2Ship ne contient **aucune** donnée protégée par le droit d'auteur. Tu dois faire le dump de ta propre cartouche.

| Version | Compatible | CRC d'en-tête | SHA-1 (`.z64`) |
|---|---|---|---|
| **PAL 1.1 / Rev A** (Europe, En/Fr/De/Es) | ✅ | `0A5D8F83` | `bb4e4757d10727c7584c59c1f2e5f44196e9c293` |
| NTSC-U 1.0 (USA) | ✅ | `5354631C` | `d6133ace5afaa0882cf214cf88daba39e266c078` |
| NTSC-U GameCube (Collector's Edition) | ✅ | `B443EB08` | `9743aa026e9269b339eb0e3044cd5830a440c1fd` |
| PAL 1.0 (première version européenne) | ❌ | `E97955C6` | – |
| Versions japonaises, GameCube PAL, *Majora's Mask 3D* | ❌ | – | – |

Les cartouches PAL 1.0 et 1.1 se ressemblent. C'est le CRC d'en-tête (octets `0x10` à `0x13` d'un dump `.z64`) qui permet de les distinguer, et `tools/generate-o2r.sh` le vérifie pour toi. Les dumps dont les octets sont inversés (`.v64`, `.n64`) sont convertis automatiquement.

Les ROMs modifiées ou traduites (traductions amateurs, hacks) ne sont pas compatibles.

## Installation

### 1. Récupérer les fichiers

Télécharge `2ship.nro` et `2ship.o2r` depuis les [Releases](../../releases), ou [compile-les toi-même](docs/BUILDING_SWITCH.md).

### 2. Générer `mm.o2r` à partir de ta ROM

`mm.o2r` contient les données du jeu, extraites de ta ROM. Génère-le sur un PC sous Linux ou WSL (Windows) :

```bash
git clone <ce dépôt>
cd 2ship2harkinian-Switch-PAL
tools/generate-o2r.sh /chemin/vers/ta/rom.z64
```

Installe d'abord les dépendances. Elles sont listées dans [docs/BUILDING_SWITCH.md](docs/BUILDING_SWITCH.md#1-host-dependencies).

`mm.o2r` doit être généré à partir de la **même version** de ce dépôt que le `2ship.nro` que tu utilises. Ne partage jamais ton `mm.o2r` : il contient les données du jeu, protégées par le droit d'auteur.

### 3. Copier sur la carte SD

```
sdmc:/switch/2s2h/
├── 2ship.nro
├── 2ship.o2r
└── mm.o2r
```

### 4. Lancer le jeu

Ouvre le Homebrew Menu en **maintenant R pendant le lancement d'un jeu** (title override). Ne le lance pas depuis l'Album : en mode applet, il n'y a pas assez de mémoire et le jeu plante ou refuse de démarrer.

### 5. Choisir la langue (PAL uniquement)

Choisis la langue dans les options du jeu. Ton choix est sauvegardé.

## Commandes

- **Moins (−)** ouvre le menu de 2Ship (améliorations, cheats, réglages).
- **La visée au gyroscope** et **les vibrations** fonctionnent avec les Joy-Con, la manette Pro et les manettes tierces compatibles. Tu peux choisir la source du gyroscope (Joy-Con gauche, droit ou les deux) dans les réglages de la manette.

Quand tu crées une sauvegarde, 2Ship 5.x te demande de choisir **Vanilla** ou **Randomizer**, puis un preset d'options (*None*, *Curated*, *Defaults*, *Voyage 3*). Pour retrouver le jeu d'origine, choisis **Vanilla** avec **Defaults**.

## Limitations connues

- Le support PAL est récent et provient d'une pull request upstream qui n'est pas encore fusionnée. Certains textes ou textures traduits peuvent encore être incorrects. Merci de [les signaler](../../issues/new/choose).
- La PAL 1.0 n'est pas encore prise en charge.
- Les versions PC (Windows/Linux/macOS) n'ont pas été testées dans ce fork.

## Compilation

Consulte [docs/BUILDING_SWITCH.md](docs/BUILDING_SWITCH.md) pour la version Switch, et [docs/BUILDING.md](docs/BUILDING.md) pour les instructions upstream des versions PC.

## Contribuer

Les signalements de bugs, correctifs et améliorations sont les bienvenus. Lis d'abord [CONTRIBUTING.md](CONTRIBUTING.md). Les issues peuvent être écrites en français.

## Crédits

Ce fork ne fait que rassembler des travaux existants et les adapter à la Switch. Tout le mérite revient à :

- **[2 Ship 2 Harkinian](https://github.com/2ship2harkinian/2ship2harkinian)** : l'équipe HarbourMasters / 2Ship et ses contributeurs (le portage PC sur lequel tout repose).
- **[zeldaret/mm](https://github.com/zeldaret/mm)** : la décompilation de *Majora's Mask* qui a rendu le portage possible.
- **[libultraship](https://github.com/Kenix3/libultraship)** (Kenix3 et ses contributeurs), **[ZAPDTR](https://github.com/HarbourMasters/ZAPDTR)** et **[OTRExporter](https://github.com/HarbourMasters/OTRExporter)** (HarbourMasters) : le moteur et les outils d'extraction.
- **[YoshiCrystal9/2ship2harkinian-Switch](https://github.com/YoshiCrystal9/2ship2harkinian-Switch)** : le premier portage Switch, et l'icône Switch.
- **[starshopper612/2ship2harkinian-Switch](https://github.com/starshopper612/2ship2harkinian-Switch)** (anciennement reflex909) : le passage à la 5.0.1, le gyroscope, les vibrations et les correctifs de manettes, ainsi que les forks Switch de libultraship, OTRExporter et ZAPDTR.
- **[timschneeb](https://github.com/timschneeb)** : le code gyroscope et vibrations pour Switch (issu de Shipwright-Switch).
- **[alexbcz](https://github.com/alexbcz)** : le support PAL 1.1 ([2ship2harkinian#1966](https://github.com/2ship2harkinian/2ship2harkinian/pull/1966), [2ship2harkinian-PAL](https://github.com/alexbcz/2ship2harkinian-PAL)) et les modifications correspondantes dans libultraship, OTRExporter et ZAPDTR.
- **[inspectredc](https://github.com/inspectredc)** : les premiers travaux sur la PAL ([2ship2harkinian#1231](https://github.com/2ship2harkinian/2ship2harkinian/pull/1231), support MM PAL dans ZAPDTR et OTRExporter).
- **[devkitPro](https://devkitpro.org)** : la toolchain Switch et libnx.

Les commits exacts utilisés sont listés dans [docs/SOURCES.md](docs/SOURCES.md).

## Licence

Mêmes licences que les projets d'origine : voir [LICENSE](LICENSE), ainsi que `libultraship/LICENSE`, `OTRExporter/LICENSE` et `ZAPDTR/LICENSE` pour les composants inclus.

*The Legend of Zelda: Majora's Mask* est © Nintendo. Ce dépôt ne contient aucune donnée du jeu.
