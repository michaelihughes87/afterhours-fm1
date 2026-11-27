# AFTERHOURS — five-track implementation plan

## Starting point

Development branch: `afterhours-five-track`

Known-good baseline: `46e51ce433e9e73c8d6cac0e8eeebfce519feb2c` (SLOOP 2.8.5-derived firmware, original SLOOP palette, successful build and regression suite).

The baseline is a recovery point, not the AFTERHOURS product. Do not install it as the finished instrument.

## Agreed product

Five visible tracks, in this deliberate order:
1. **DRUMS** — one dedicated 16-lane drum machine.
2. **AFTER POLY** — flexible synth part; Prophet warmth + Juno movement.
3. **ORGAN / KEYS** — flexible synth part; soulful organ, warm Rhodes / Wurlitzer-style keys.
4. **MONO BASS** — flexible synth part; Minimoog weight + Pro-One articulation.
5. **TEXTURE / PERC** — flexible synth part; granular / digital / atmospheric sounds and selected tuned / synthetic percussion.

The instrument therefore has four synth parts and one drum part. All four synth parts can load any supported engine and ordinary preset. Roles are defaults and preset-library priorities, not track locks. T5 combines texture and percussion because the agreed instrument has five tracks; percussion is not a separate sixth part or a second drum machine.

## Technical constraints already identified

### Track and audio architecture

- Baseline `core.h`: `NPART=3`, `NTRK=4`, `TRK_DRUM=3`, `NVOICE=8`.
- Synth tracks are currently contiguous in `trk[0..2]`, with the drum track at `trk[3]`.
- Candidate low-disruption internal arrangement: `NPART=4`, `NTRK=5`, `TRK_DRUM=4`, keeping four synth parts contiguous and introducing an explicit visible order `[4,0,1,2,3]` so DRUMS is shown first.
- This mapping must be centralized and tested. Never assume UI row index equals internal track index.
- The global eight-voice synth budget should remain shared across all four synth parts at first. Engine-specific polyphony limits remain in force.
- Audit every `NPART` / `NTRK` array, bitmask, loop and index: synth voices, note hits, visualiser notes, expression, inserts, filters, render masks, recording, undo, strum, step-entry queues, mute / solo, panic, MIDI and UI.

### Engine memory

- `engines.c` allocates `eng_arena[NPART]` in `.pool`.
- Baseline pool usage: 333,900 / 344,064 bytes. Required reserve: 8,192 bytes. Only about 1,972 bytes are available beyond that reserve.
- Baseline `.data + .bss`: 59,340 / 98,304 bytes, leaving 38,964 bytes before other changes.
- Do not add a fourth arena to `.pool` without measuring its exact size and reviewing the linker map.
- Investigate placing engine arenas in `.bss` or a deliberately sized memory region, with tests for stack, ISR, DMA and dual-core safety.
- Measure the actual sizes of GRAIN, FM6 and PHYS state; use worst-case memory, not the average engine.

### Project storage

- Project format 6 is 3,816 bytes; one storage object permits at most 3,840 bytes.
- A fifth track cannot be appended to the existing project struct safely.
- Current persistent layout includes four A/B project objects, a separate A/B working autosave, settings, MIDI settings, user presets, FM6 patches and four user sample slots.
- Design a new versioned, checksummed project representation and prove its worst-case length before changing firmware.
- Compare compact / variable-length track encoding with a multi-sector A/B design and audit the complete flash map.
- Preserve transactional safety: a failed or interrupted save must leave the previous valid project loadable.
- Old formats 1–6 must import without loss: old synth tracks map in order to visible T2–T4; the old drum track maps to visible T1; visible T5 starts empty with its role default.
- Do not silently truncate, erase sample slots or change the data map without verified migration tests.

### MIDI

- Add a fourth synth MIDI channel; keep a separate drum channel.
- Migrate the settings layout while preserving existing channel choices.
- Test USB MIDI, TRS MIDI, clock, program change, CC, remote control and MIDI learn.

### Mixer and display

- The existing 240 × 240 LIVE / TRACKS screen uses four 36-pixel track rows and a knob footer.
- Five 36-pixel rows will collide with the current footer. Prototype five compact rows of roughly 28 pixels, preserving track name / engine, number, pattern overview, level and mute / solo / record status.
- Detailed effect sends and insert controls can stay on secondary pages.
- Keep readable text and values primary; the visuals support the instrument rather than competing with editing.

### Colour theme and editor

- Current theme record `theme_t` contains four track colours and is 40 bytes (THM2).
- The web editor writes this record. A fifth track colour needs a backward-compatible format / protocol plan, including existing theme migration, or a deliberately derived fifth colour.
- Check all fixed four-colour arrays and loops in firmware and web editor before extending.
- Preserve SLOOP palette tests until AFTERHOURS theme tests replace them.

## Implementation order

1. Finish the product and architecture documentation on this branch.
2. Build an exhaustive source audit of all track-index, voice, memory, MIDI, UI and storage assumptions.
3. Generate a linker map; measure arena sizes and determine a memory placement that retains all reserves.
4. Define and host-test the track index / visible order mapping before changing DSP loops.
5. Design project format and flash allocation; test old project imports and worst-case new projects in host tools.
6. Implement four synth parts plus one drum part, including audio, sequencer, mixer, MIDI and dual-core behavior.
7. Implement theme format compatibility and five-row UI.
8. Build and audition the sound library in the agreed order: DRUMS, AFTER POLY, ORGAN / KEYS, MONO BASS, then TEXTURE / PERC; assess Guru-600 P600 as an optional experiment.
9. Implement original, sound-reactive AFTERHOURS graphics.
10. Run full regression, CPU / memory stress and actual-device backup / recovery / install tests.

## Release gates

- No regression in existing golden audio renders unless individually reviewed and approved.
- No new CPU budget failure; target-cost references are static compiler-derived checks, not device performance measurements.
- No audio underruns, crashes, races or memory-reserve violations in worst-case five-track tests.
- Full old-project compatibility and power-loss-safe new save / load.
- All five tracks independently sequence, mix, mute, solo, record and respond to MIDI as specified.
- AFTERHOURS identity is visible in boot, interface, colors, visuals, presets and documentation.
- Actual FM-1 install only after a full device backup and a verified recovery plan.

## Explicitly not part of this first target

- Six tracks.
- Two dedicated drum-machine tracks.
- A percussion-only synth engine or track lock.
- Eight new synth voices per part.
- Flashing the unmodified SLOOP-looking baseline as AFTERHOURS.
