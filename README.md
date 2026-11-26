# AFTERHOURS

**A colourful, expressive groovebox firmware for the M-VAVE FM-1.**  
Analogue warmth. Digital grime. Imperfect rhythms. Beautiful decay.

AFTERHOURS is a SLOOP-derived firmware project with a distinctly nocturnal, psychedelic and post-punk personality. Its musical territory spans trip-hop, alternative electronic, post-punk, psychedelic synth pop, broken-beat and experimental dance.

## Design target

- **Six tracks preferred**, with **two dedicated, independently mixable drum/percussion tracks** and four melodic / texture tracks.
- A curated collection of classic drum-machine, acoustic, breakbeat and post-punk / industrial kits.
- Kit-wide and track-level effects, per-hit shaping, and a fast hands-on mixer.
- Polyphonic analogue-style synths, including a Prophet '08-inspired two-oscillator voice architecture.
- A colourful, sound-reactive interface with distinct animated imagery for each engine and drum kit.
- Complete groovebox workflow: patterns, song arrangement, presets, sampling, MIDI and dependable project save/recall.

The six-track arrangement is a target, not a claim about the current SLOOP source. SLOOP 2.8.5 has three synth parts plus one dedicated drum track. JIANT demonstrates a six-part architecture in which DRUM-X is an engine selectable on a part. AFTERHOURS will retain SLOOP as its source foundation and selectively port/adapt the relevant six-part and drum-engine architecture, subject to real hardware CPU/RAM measurements.

## Project status

**Design specification / bootstrap stage.** This repository's project scaffold is not flashable firmware. The upstream source baseline must be imported, built and tested before firmware changes begin.

## Foundation

- Upstream: [isod89/sloop-fm1](https://github.com/isod89/sloop-fm1)
- Architecture and interaction reference: [abcdaniel/JIANT](https://github.com/abcdaniel/JIANT)
- Firmware releases and compatibility reference: [The Firmware Hub](https://thefirmwarehub.com/)

SLOOP and JIANT are GPL-3.0 projects. Before distributing a derivative, retain required copyright and licence notices, identify modified files, provide corresponding source as required, and review all asset attributions.

## Principles

1. Preserve SLOOP's sequencing, MIDI, audio, project and recovery foundations.
2. Prioritise a complete, playable instrument over a large collection of half-finished features.
3. Make every kit and engine visually and sonically distinctive.
4. Keep mixing immediate: level, pan, mute, solo, sends and meters close at hand.
5. Treat sound-reactive graphics as instrument feedback, not decoration.
6. Add DSP only after host tests and target CPU/RAM measurements.
7. Never flash an untested build; retain a known-good recovery route.

## Documents

- [Product brief](docs/PRODUCT_BRIEF.md)
- [Track architecture and mixer](docs/ARCHITECTURE.md)
- [Development roadmap](docs/ROADMAP.md)
- [Sound design specification](docs/SOUND_DESIGN.md)
- [Initial preset bank](docs/PRESET_BANK.md)
- [Technical notes](docs/TECHNICAL_NOTES.md)
- [Preset authoring notes](presets/README.md)
- [Bootstrap instructions](BOOTSTRAP.md)
