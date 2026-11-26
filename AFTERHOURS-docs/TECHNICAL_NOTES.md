# Technical notes and build gates

## Upstream build requirements

The SLOOP build guide documents a JieLi AC79 / pi32v2 toolchain. On macOS it uses Docker Desktop with linux/amd64, the JieLi toolchain, AC79 SDK files and Python with Pillow. The documented outputs include the firmware app, OTA loader and installable .fwsc package.

Read the live upstream guide before building:
https://github.com/isod89/sloop-fm1/blob/main/BUILDING.md

## Development host

The user has an Apple-silicon Mac. Confirm Docker Desktop, Python 3, Node.js and available disk space before setting up the full build. The upstream guide also documents a browser-preview build via Emscripten that does not require the JieLi toolchain or hardware.

## Safety gates

- Do not install an unverified binary.
- Back up user projects, presets and samples before firmware changes.
- Confirm exact FM-1 hardware / flash-chip revision and current firmware.
- Follow the selected firmware's official install and return-to-stock instructions.
- Keep a known-good official firmware recovery path available.
- Never assume a package for one hardware revision is safe for another.

## Tests

The upstream test suite includes host tests and regression checks for DSP rendering, CPU budgets, flash storage, MIDI, project formats, slicer, installer and web UI. Run it before and after every functional change. Intentional sound changes require reviewing the golden-render and CPU-budget update procedure rather than blindly refreshing expected results.
