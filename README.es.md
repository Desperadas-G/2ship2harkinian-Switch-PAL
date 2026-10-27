# 2 Ship 2 Harkinian – Switch PAL

[English](README.md) · [Français](README.fr.md) · [Deutsch](README.de.md) · **Español**

[![switch-build](https://github.com/Desperadas-G/2ship2harkinian-Switch-PAL/actions/workflows/switch.yml/badge.svg)](https://github.com/Desperadas-G/2ship2harkinian-Switch-PAL/actions/workflows/switch.yml)

*Majora's Mask* en Nintendo Switch (Atmosphère) con [2 Ship 2 Harkinian](https://github.com/2ship2harkinian/2ship2harkinian), ahora también con la **versión europea PAL 1.1** (inglés, francés, alemán y español).

## Instalación

1. Descarga **`2Ship-Switch-PAL-vX.Y.Z.zip`** desde la [última release](../../releases/latest) y descomprímelo.
2. Crea los datos del juego a partir de tu ROM: en un PC, arrastra tu ROM (`.z64`, `.n64`, `.v64` o `.zip`) sobre **`Generate mm.o2r.bat`** y espera alrededor de un minuto.
3. Copia la carpeta **`switch`** a la raíz de tu tarjeta SD.
4. Mantén pulsado **R** al iniciar cualquier juego para abrir el Homebrew Menu, y luego abre **2 Ship 2 Harkinian**.

No lo abras desde el Álbum: el modo applet no tiene suficiente memoria.

**Actualizar:** reemplaza `2ship.nro` y `2ship.o2r`. Tu `mm.o2r` y tus partidas se conservan.

`Generate mm.o2r.bat` funciona en Windows. En Linux o macOS, usa `tools/generate-o2r.sh` ([docs/BUILDING_SWITCH.md](docs/BUILDING_SWITCH.md)).

## ROMs compatibles

| Versión | CRC de cabecera |
|---|---|
| PAL 1.1 / Rev A (Europa, En/Fr/De/Es) ✅ | `0A5D8F83` |
| PAL 1.0, versiones japonesas, hacks y traducciones ❌ | – |

El generador comprueba tu ROM y te avisa si no es compatible.

## ⚖️ Aviso legal

- Ni aquí ni en las releases se incluyen ROMs ni datos de Nintendo. Tienes que volcar **tu propio** cartucho.
- Nunca compartas ROMs ni tu `mm.o2r`. Las peticiones y los enlaces se eliminarán.
- Proyecto de fans sin ánimo de lucro, sin relación con Nintendo. *The Legend of Zelda: Majora's Mask* es © Nintendo.

## Créditos

Basado en 2Ship **5.0.1 "Battler Bravo"**. Este fork solo reúne trabajos existentes:

- [2 Ship 2 Harkinian](https://github.com/2ship2harkinian/2ship2harkinian): el equipo de HarbourMasters / 2Ship y sus colaboradores
- [zeldaret/mm](https://github.com/zeldaret/mm): la decompilación de *Majora's Mask*
- [libultraship](https://github.com/Kenix3/libultraship) (Kenix3), [ZAPDTR](https://github.com/HarbourMasters/ZAPDTR) y [OTRExporter](https://github.com/HarbourMasters/OTRExporter) (HarbourMasters)
- [YoshiCrystal9](https://github.com/YoshiCrystal9/2ship2harkinian-Switch): el primer port para Switch y el icono
- [starshopper612](https://github.com/starshopper612/2ship2harkinian-Switch) (antes reflex909): el port 5.0.1 para Switch, giroscopio, vibración y mandos
- [timschneeb](https://github.com/timschneeb): el código de giroscopio y vibración (Shipwright-Switch)
- [alexbcz](https://github.com/alexbcz): el soporte PAL 1.1 ([2ship2harkinian#1966](https://github.com/2ship2harkinian/2ship2harkinian/pull/1966))
- [inspectredc](https://github.com/inspectredc): trabajos PAL anteriores ([2ship2harkinian#1231](https://github.com/2ship2harkinian/2ship2harkinian/pull/1231))
- [devkitPro](https://devkitpro.org): la toolchain de Switch y libnx

Commits exactos: [docs/SOURCES.md](docs/SOURCES.md). Licencia: [LICENSE](LICENSE), además de `libultraship/`, `OTRExporter/` y `ZAPDTR/LICENSE`.

<a href="https://github.com/Kenix3/libultraship/">
  <picture>
    <source media="(prefers-color-scheme: dark)" srcset="./docs/poweredbylus.darkmode.png">
    <img alt="Powered by libultraship" src="./docs/poweredbylus.lightmode.png">
  </picture>
</a>
