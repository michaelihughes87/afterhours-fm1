# AFTERHOURS — track architecture, drums and mixer

## Decision

Target **six independent tracks**, with two drum/percussion tracks and four melodic / texture tracks. Treat five tracks as a fallback if six cannot meet measured performance and usability targets.

This is a deliberate architectural extension, not a small theme change.

## What the source projects establish

- SLOOP 2.8.5's `firmware/src/core.h` defines `NPART 3` and `NTRK 4`: three synth parts plus a dedicated drum track.
- JIANT's `firmware/src/core.h` defines `NPART 6` and `NTRK NPART`: six parts.
- JIANT's DRUM-X (`firmware/src/eng_drum.c`) is an engine on a part, rather than a globally fixed drum track. Its kit has eight lanes; each lane has its own sound and per-hit behaviour.
- SLOOP's `firmware/src/eng_analog.c` already provides two band-limited oscillators, detune, noise, drive and a trapezoidal state-variable filter.
- JIANT demonstrates sound-reactive engine / kit imagery in `firmware/src/ui_being.c` and related UI files.

Sources:
- https://github.com/isod89/sloop-fm1/blob/main/firmware/src/core.h
- https://github.com/isod89/sloop-fm1/blob/main/firmware/src/eng_analog.c
- https://github.com/abcdaniel/JIANT/blob/main/firmware/src/core.h
- https://github.com/abcdaniel/JIANT/blob/main/firmware/src/eng_drum.c
- https://github.com/abcdaniel/JIANT/blob/main/firmware/src/ui_being.c

## Proposed default layout

| Track | Default engine / role | Key sound |
|---|---|---|
| T1 | DRUM-X / main drums | Kick, snare, hats, clap, toms |
| T2 | DRUM-X / percussion | Breaks, industrial hits, metallic percussion, found sounds |
| T3 | ANALOG / bass | Sub and mono bass |
| T4 | AFTER POLY / main poly | Two-oscillator, Prophet-inspired polysynth |
| T5 | AFTER POLY / second poly | Pads, strings, chord movement |
| T6 | FM6 / SAMPLE / NOISE / lead-texture | Flexible top line and atmosphere |

Where feasible, retain track-engine flexibility so the user can change roles rather than being locked to the default layout.

## Drum design

Two independent DRUM-X parts should each have:
- Their own kit and pattern, with independent level, pan, mute, solo, sends and insert effect.
- At least eight simultaneously useful drum lanes per kit; investigate preserving SLOOP's 16-sound / key mapping if screen and memory budgets allow.
- Per-lane level / velocity response, tune, decay, pan, mute and sound selection as supported by the base engine.
- Common insert families available to either drum track: filter, drive / distortion, bit reduction / crush, modulation, delay and reverb.
- Track-level effects and sends so a kit's whole sound can be processed, while avoiding a costly separate full insert chain on every lane unless benchmarks permit.
- Choke groups for open/closed hats and other mutually exclusive percussion.
- Kick / snare priority in voice stealing; busy hats must not steal the kick.

Factory kit families:
1. Classic electronic: 808, 909, 606, Linn-style, CR-78-inspired.
2. Acoustic / live: dry, roomy, tight, loose, brush / rim / tom variants.
3. Hip-hop / break: dusty breaks, chopped kits, boom-bap.
4. Dance: house, electro, techno, jungle / DnB, UKG.
5. Dub / organic: hand percussion, shakers, congas, rim / wood.
6. Post-punk / industrial: hard room snare, trashy acoustic kit, metal, clangs, impacts, noise bursts, processed objects.

These are tonal categories, not promises to include copyrighted samples or exact drum-machine ROMs. Use properly licensed / original / CC0 sample material, with attribution where required.

## Mixer

The core mixer view should make six strips immediately understandable:
- Track name / colour and compact level meter.
- Level, pan, mute and solo.
- Send levels for delay, reverb and modulation.
- One quick-access tone control / filter.
- Track select and clear indication of the active track.

Secondary pages can expose inserts, routing and detailed parameters. Drum tracks should also expose their kit identity and a quick access to the drum lanes. The web editor can provide a larger mixer for detailed balancing and sound management.

Master page:
- Master level and peak indicator.
- Main EQ / filter.
- Limiter / soft clip only where safe and measurable.
- Shared time-based effects with controllable sends / returns.
- Optional kick-triggered ducking / sidechain-style movement.

## AFTER POLY synthesis

First prototype by extending SLOOP ANALOG rather than duplicating it. Preserve band-limited oscillators and test:
- Two-oscillator blend and fine tuning.
- Pulse width and modulation.
- Oscillator sync if budget permits.
- Optional sub / noise.
- Filter envelope, amp envelope and LFO modulation.
- Unison spread and poly glide.

The FM-1 is a constrained embedded device. Do not promise eight simultaneous voices on all six tracks. Use configurable voice caps, predictable voice stealing and load-aware quality modes. Measure a worst-case song with both drum kits active, two poly tracks playing chords, effects running and the display updating.

## Visual system

The display is an instrument surface, not a dashboard:
- Use a vivid palette (acid lime, cyan, violet, coral, amber and warm cream) with high legibility.
- Each track and sound engine gets a recognisable visual species / signal motif.
- Animate from existing signal metrics and parameter values; avoid expensive full-screen effects.
- Show audio energy, filter movement, oscillator beating and drum hits in ways that help the player understand the sound.
- Allow a low-motion / reduced-animation option and a simpler contrast-focused theme.

## Structural risks and tests

Six tracks touches more than an array size. Audit:
- Track/part arrays, UI navigation and track selection.
- MIDI channel allocation and remote control mapping.
- Song / pattern serialization and project migrations.
- Flash storage, autosave and user presets.
- Mixer / FX routing, dual-core scheduling and audio buffers.
- Tests, emulator/editor state and documentation.

No old project should be silently corrupted. Build a tested import / migration path for existing SLOOP projects before changing storage layouts.

Required tests:
1. Load / save existing SLOOP projects and verify their content.
2. Six tracks active with independent patterns and mixer state.
3. Both drum tracks play simultaneously, including busy hats and kick priority.
4. Two poly tracks playing chords while drums and effects run.
5. MIDI clock, USB audio and external MIDI on all intended tracks.
6. CPU / RAM and audio-dropout tests under worst-case load.
7. Long-session save / load and recovery tests on actual FM-1 hardware.
