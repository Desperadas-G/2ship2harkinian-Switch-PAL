# 2 Ship 2 Harkinian – Switch PAL

[English](README.md) · [Français](README.fr.md) · **Deutsch** · [Español](README.es.md)

[![switch-build](https://github.com/Desperadas-G/2ship2harkinian-Switch-PAL/actions/workflows/switch.yml/badge.svg)](https://github.com/Desperadas-G/2ship2harkinian-Switch-PAL/actions/workflows/switch.yml)

*Majora's Mask* auf der Nintendo Switch (Atmosphère) mit [2 Ship 2 Harkinian](https://github.com/2ship2harkinian/2ship2harkinian), jetzt auch mit der **europäischen PAL-1.1-Version** (Englisch, Französisch, Deutsch, Spanisch).

## Installation

1. Lade **`2Ship-Switch-PAL-vX.Y.Z.zip`** aus dem [neuesten Release](../../releases/latest) herunter und entpacke es.
2. Erzeuge die Spieldaten aus deiner ROM: Ziehe sie am PC (`.z64`, `.n64`, `.v64` oder `.zip`) auf **`Generate mm.o2r.bat`** und warte etwa eine Minute.
3. Kopiere den Ordner **`switch`** in das Hauptverzeichnis deiner SD-Karte.
4. Halte **R** gedrückt, während du ein beliebiges Spiel startest, um das Homebrew-Menü zu öffnen, und starte **2 Ship 2 Harkinian**.

Starte es nicht über das Album: Im Applet-Modus reicht der Speicher nicht.

**Update:** Ersetze `2ship.nro` und `2ship.o2r`. Deine `mm.o2r` und deine Spielstände bleiben erhalten.

`Generate mm.o2r.bat` läuft unter Windows. Unter Linux oder macOS nimmst du stattdessen `tools/generate-o2r.sh` ([docs/BUILDING_SWITCH.md](docs/BUILDING_SWITCH.md)).

## Unterstützte ROMs

| Version | Header-CRC |
|---|---|
| PAL 1.1 / Rev A (Europa, En/Fr/De/Es) ✅ | `0A5D8F83` |
| PAL 1.0, japanische Versionen, Hacks und Übersetzungen ❌ | – |

Der Generator prüft deine ROM und sagt dir, wenn sie nicht unterstützt wird.

## ⚖️ Rechtliches

- Hier und in den Releases sind keine ROMs und keine Nintendo-Daten enthalten. Du musst **dein eigenes** Modul dumpen.
- Teile niemals ROMs oder deine `mm.o2r`. Anfragen und Links werden gelöscht.
- Ein nicht-kommerzielles Fanprojekt ohne Verbindung zu Nintendo. *The Legend of Zelda: Majora's Mask* ist © Nintendo.

## Credits

Basiert auf 2Ship **5.0.1 „Battler Bravo“**. Dieser Fork führt nur bestehende Arbeiten zusammen:

- [2 Ship 2 Harkinian](https://github.com/2ship2harkinian/2ship2harkinian): das HarbourMasters- / 2Ship-Team und alle Mitwirkenden
- [zeldaret/mm](https://github.com/zeldaret/mm): die Dekompilierung von *Majora's Mask*
- [libultraship](https://github.com/Kenix3/libultraship) (Kenix3), [ZAPDTR](https://github.com/HarbourMasters/ZAPDTR) und [OTRExporter](https://github.com/HarbourMasters/OTRExporter) (HarbourMasters)
- [YoshiCrystal9](https://github.com/YoshiCrystal9/2ship2harkinian-Switch): die erste Switch-Portierung und das Icon
- [starshopper612](https://github.com/starshopper612/2ship2harkinian-Switch) (ehemals reflex909): die 5.0.1-Switch-Portierung, Gyro, Rumble, Controller
- [timschneeb](https://github.com/timschneeb): der Gyro- und Rumble-Code (Shipwright-Switch)
- [alexbcz](https://github.com/alexbcz): die PAL-1.1-Unterstützung ([2ship2harkinian#1966](https://github.com/2ship2harkinian/2ship2harkinian/pull/1966))
- [inspectredc](https://github.com/inspectredc): frühere PAL-Arbeiten ([2ship2harkinian#1231](https://github.com/2ship2harkinian/2ship2harkinian/pull/1231))
- [devkitPro](https://devkitpro.org): die Switch-Toolchain und libnx

Genaue Commits: [docs/SOURCES.md](docs/SOURCES.md). Lizenz: [LICENSE](LICENSE), dazu `libultraship/`, `OTRExporter/` und `ZAPDTR/LICENSE`.

<a href="https://github.com/Kenix3/libultraship/">
  <picture>
    <source media="(prefers-color-scheme: dark)" srcset="./docs/poweredbylus.darkmode.png">
    <img alt="Powered by libultraship" src="./docs/poweredbylus.lightmode.png">
  </picture>
</a>
