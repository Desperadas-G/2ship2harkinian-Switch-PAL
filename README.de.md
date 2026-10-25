# 2 Ship 2 Harkinian – Switch PAL

[English](README.md) · [Français](README.fr.md) · **Deutsch** · [Español](README.es.md)

[![switch-build](https://github.com/Desperadas-G/2ship2harkinian-Switch-PAL/actions/workflows/switch.yml/badge.svg)](https://github.com/Desperadas-G/2ship2harkinian-Switch-PAL/actions/workflows/switch.yml)

Eine inoffizielle Nintendo-Switch-Portierung von [2 Ship 2 Harkinian](https://github.com/2ship2harkinian/2ship2harkinian) (2S2H), die auch die **europäische Version (PAL 1.1) von *The Legend of Zelda: Majora's Mask*** unterstützt, mit allen vier Sprachen: **Englisch, Französisch, Deutsch und Spanisch**.

Sie läuft als Homebrew auf einer Switch mit der Custom Firmware [Atmosphère](https://github.com/Atmosphere-NX/Atmosphere).

> Dieses Projekt steht in keiner Verbindung zu Nintendo, HarbourMasters oder dem 2Ship-Team. Bitte frage auf dem offiziellen 2Ship-Discord nicht nach Hilfe zu diesem Fork. Nutze stattdessen die [Issues](../../issues) dieses Repositorys.

## ⚖️ Rechtliche Hinweise

- **Dieses Repository enthält keine ROM und keine Daten von Nintendo**, und seine Releases werden auch nie welche enthalten. Es enthält nur Quellcode, und der ist keine Kopie des Spiels: Der Spielcode wurde vom Projekt [zeldaret/mm](https://github.com/zeldaret/mm) dekompiliert und in C neu geschrieben.
- **Du musst eine legal erworbene Kopie von *The Legend of Zelda: Majora's Mask* besitzen** und sie **von deinem eigenen Modul** auslesen (bzw. von deiner eigenen GameCube-Disc für die US-GC-Version). Die Spieldaten (`mm.o2r`) werden auf deinem eigenen Computer aus deinem Dump erzeugt.
- **Frage nicht nach ROMs, und teile niemals ROMs oder `mm.o2r`-Dateien**, weder hier noch anderswo. Issues, Pull Requests oder Kommentare, die auf ROMs verlinken oder nach ihnen fragen, werden geschlossen und gelöscht.
- Die ROM eines Spiels herunterzuladen, das man nicht besitzt, ist Piraterie und in den meisten Ländern illegal. Wir dulden keine Piraterie.
- Dies ist ein nicht-kommerzielles Fanprojekt. Es ist weder mit Nintendo verbunden noch von Nintendo unterstützt oder gesponsert. *The Legend of Zelda* und *Majora's Mask* sind Marken von Nintendo.

## Grundlage

| Komponente | Version |
|---|---|
| 2 Ship 2 Harkinian | **5.0.1 „Battler Bravo“** |
| Switch-Portierung | [starshopper612/2ship2harkinian-Switch](https://github.com/starshopper612/2ship2harkinian-Switch) `switch-5.0.1-v3` (Gyro und Rumble) |
| PAL-1.1-Unterstützung | [2ship2harkinian#1966](https://github.com/2ship2harkinian/2ship2harkinian/pull/1966) von alexbcz ([alexbcz/2ship2harkinian-PAL](https://github.com/alexbcz/2ship2harkinian-PAL)) |

## Unterstützte ROMs

2Ship enthält **keine** urheberrechtlich geschützten Daten. Du musst dein eigenes Modul auslesen.

| Version | Unterstützt | Header-CRC | SHA-1 (`.z64`) |
|---|---|---|---|
| **PAL 1.1 / Rev A** (Europa, En/Fr/De/Es) | ✅ | `0A5D8F83` | `bb4e4757d10727c7584c59c1f2e5f44196e9c293` |
| NTSC-U 1.0 (USA) | ✅ | `5354631C` | `d6133ace5afaa0882cf214cf88daba39e266c078` |
| NTSC-U GameCube (Collector's Edition) | ✅ | `B443EB08` | `9743aa026e9269b339eb0e3044cd5830a440c1fd` |
| PAL 1.0 (erste europäische Version) | ❌ | `E97955C6` | – |
| Japanische Versionen, GameCube PAL, *Majora's Mask 3D* | ❌ | – | – |

PAL-1.0- und PAL-1.1-Module sehen gleich aus. Unterscheiden lassen sie sich am Header-CRC (Bytes `0x10` bis `0x13` eines `.z64`-Dumps), den `tools/generate-o2r.sh` für dich prüft. Dumps mit vertauschter Bytereihenfolge (`.v64`, `.n64`) werden automatisch umgewandelt.

Veränderte oder übersetzte ROMs (Fan-Übersetzungen, Hacks) werden nicht unterstützt.

## Installation

### 1. Dateien herunterladen

Lade `2ship.nro` und `2ship.o2r` unter [Releases](../../releases) herunter, oder [kompiliere sie selbst](docs/BUILDING_SWITCH.md).

### 2. `mm.o2r` aus deiner ROM erzeugen

`mm.o2r` enthält die Spieldaten, die aus deiner ROM extrahiert werden. Erzeuge die Datei auf einem PC mit Linux oder WSL (Windows):

```bash
git clone <dieses Repository>
cd 2ship2harkinian-Switch-PAL
tools/generate-o2r.sh /pfad/zu/deiner/rom.z64
```

Installiere zuerst die Abhängigkeiten. Sie sind in [docs/BUILDING_SWITCH.md](docs/BUILDING_SWITCH.md#1-host-dependencies) aufgeführt.

`mm.o2r` muss mit **derselben Version** dieses Repositorys erzeugt werden wie die `2ship.nro`, die du verwendest. Teile deine `mm.o2r` niemals: Sie enthält die urheberrechtlich geschützten Daten des Spiels.

### 3. Auf die SD-Karte kopieren

```
sdmc:/switch/2s2h/
├── 2ship.nro
├── 2ship.o2r
└── mm.o2r
```

### 4. Starten

Öffne das Homebrew-Menü, indem du **beim Starten eines Spiels R gedrückt hältst** (Title Override). Starte es nicht über das Album: Im Applet-Modus steht zu wenig Speicher zur Verfügung, und das Spiel stürzt ab oder startet gar nicht.

### 5. Sprache wählen (nur PAL)

Wähle die Sprache in den Spieloptionen. Die Auswahl wird gespeichert.

## Steuerung

- **Minus (−)** öffnet das 2Ship-Menü (Verbesserungen, Cheats, Einstellungen).
- **Gyro-Zielen** und **Rumble** funktionieren mit Joy-Cons, dem Pro Controller und kompatiblen Controllern von Drittanbietern. Die Gyro-Quelle (linker, rechter oder beide Joy-Cons) lässt sich in den Controller-Einstellungen wählen.

Beim Anlegen eines Spielstands fragt 2Ship 5.x nach **Vanilla** oder **Randomizer** und danach nach einem Options-Preset (*None*, *Curated*, *Defaults*, *Voyage 3*). Für das Originalspiel wähle **Vanilla** mit **Defaults**.

## Bekannte Einschränkungen

- Die PAL-Unterstützung ist neu und stammt aus einem Upstream-Pull-Request, der noch nicht übernommen wurde. Manche übersetzten Texte oder Texturen können noch fehlerhaft sein. Bitte [melde sie](../../issues/new/choose).
- PAL 1.0 wird noch nicht unterstützt.
- Die Desktop-Versionen (Windows/Linux/macOS) wurden in diesem Fork nicht getestet.

## Kompilieren

Siehe [docs/BUILDING_SWITCH.md](docs/BUILDING_SWITCH.md) für die Switch-Version und [docs/BUILDING.md](docs/BUILDING.md) für die Upstream-Anleitung der Desktop-Versionen.

## Mitwirken

Fehlerberichte, Korrekturen und Verbesserungen sind willkommen. Lies vorher [CONTRIBUTING.md](CONTRIBUTING.md). Issues dürfen auf Deutsch verfasst werden.

## Credits

Dieser Fork führt nur bestehende Arbeiten zusammen und passt sie an die Switch an. Der Verdienst gebührt:

- **[2 Ship 2 Harkinian](https://github.com/2ship2harkinian/2ship2harkinian)**: dem HarbourMasters- / 2Ship-Team und allen Mitwirkenden (die PC-Portierung, auf der alles aufbaut).
- **[zeldaret/mm](https://github.com/zeldaret/mm)**: der Dekompilierung von *Majora's Mask*, die die Portierung erst möglich gemacht hat.
- **[libultraship](https://github.com/Kenix3/libultraship)** (Kenix3 und Mitwirkende), **[ZAPDTR](https://github.com/HarbourMasters/ZAPDTR)** und **[OTRExporter](https://github.com/HarbourMasters/OTRExporter)** (HarbourMasters): Engine und Extraktionswerkzeuge.
- **[YoshiCrystal9/2ship2harkinian-Switch](https://github.com/YoshiCrystal9/2ship2harkinian-Switch)**: der ursprünglichen Switch-Portierung und dem Switch-Icon.
- **[starshopper612/2ship2harkinian-Switch](https://github.com/starshopper612/2ship2harkinian-Switch)** (vormals reflex909): der Portierung auf 5.0.1, Gyro, Rumble und den Controller-Korrekturen sowie den Switch-Forks von libultraship, OTRExporter und ZAPDTR.
- **[timschneeb](https://github.com/timschneeb)**: dem Gyro- und Rumble-Code für die Switch (aus Shipwright-Switch).
- **[alexbcz](https://github.com/alexbcz)**: der PAL-1.1-Unterstützung ([2ship2harkinian#1966](https://github.com/2ship2harkinian/2ship2harkinian/pull/1966), [2ship2harkinian-PAL](https://github.com/alexbcz/2ship2harkinian-PAL)) und den zugehörigen Änderungen an libultraship, OTRExporter und ZAPDTR.
- **[inspectredc](https://github.com/inspectredc)**: den früheren PAL-Arbeiten ([2ship2harkinian#1231](https://github.com/2ship2harkinian/2ship2harkinian/pull/1231), MM-PAL-Unterstützung in ZAPDTR und OTRExporter).
- **[devkitPro](https://devkitpro.org)**: der Switch-Toolchain und libnx.

Die genauen Commits stehen in [docs/SOURCES.md](docs/SOURCES.md).

## Lizenz

Es gelten die Lizenzen der Originalprojekte: siehe [LICENSE](LICENSE) sowie `libultraship/LICENSE`, `OTRExporter/LICENSE` und `ZAPDTR/LICENSE` für die enthaltenen Komponenten.

*The Legend of Zelda: Majora's Mask* ist © Nintendo. Dieses Repository enthält keine Spieldaten.
