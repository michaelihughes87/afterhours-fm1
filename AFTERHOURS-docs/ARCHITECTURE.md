# AFTERHOURS — five-track architecture

## Decision

The agreed product is **five visible tracks**: one dedicated drum-machine track and four independent, flexible synth parts. Six tracks are no longer the target.

| Visible track | Role | Implementation |
|---|---|---|
| T1 | DRUMS | Existing dedicated 16-lane drum machine |
| T2 | PERCUSSION | Ordinary synth part; any engine may be loaded; percussion presets are a curated starting point |
| T3 | BASS | Flexible synth part |
| T4 | AFTER POLY | Flexible synth part; extend the existing ANALOG engine first |
| T5 | TEXTURE / SECOND SYNTH | Flexible synth part for pads, FM, samples, noise, leads and atmosphere |

Roles are defaults, not locks. In particular, T2 must not become a second special drum instrument or a percussion-only engine.

## Baseline source facts

The passing baseline is commit `46e51ce433e9e73c8d6cac0e8eeebfce519feb2c`, based on SLOOP 2.8.5 / Felucca.

- `firmware/src/core.h` currently defines `NPART 3`, `NTRK 4`, and `TRK_DRUM 3`.
- The synth parts occupy `trk[0..2]`; the dedicated drum part occupies `trk[3]`.
- `track_t` combines persistent track parameters and pattern data with substantial runtime state.
- `voice.c` treats `NVOICE 8` as a shared sounding-voice budget across the synth parts.
- `engines.c` allocates one large engine-state arena per synth part in `.pool`.
- `fx.c` sizes synth insert state, render units and dual-core masks around `NPART`; the drum insert has its own four-channel state.
- MIDI settings currently expose three synth channels plus the drum channel.
- `ui_studio.c` draws four track rows at 36 pixels each and reserves the lower display for four knob readouts.
- `gfx.c` has four track colours in both the built-in palette and the saved `theme_t` record.
- `project.c` uses project format 6. Its current project object is 3,816 bytes against a 3,840-byte storage payload limit. Format 5 is exactly 3,840 bytes.
- `storage.c` uses A/B copies in 4 KiB sectors; the 3,840-byte payload limit is intentional, not spare project space.

## Internal indices versus visible order

Keep the four synth parts contiguous internally where that reduces risk to DSP code. A candidate first implementation is `NPART 4`, `NTRK 5`, and `TRK_DRUM 4`, with a single explicit mapping for visible order `[TRK_DRUM, 0, 1, 2, 3]`.

Do not let display row number silently become an internal `trk[]` index. Introduce and test explicit helpers for visible-position-to-track-index and track-index-to-visible-position. Apply the mapping consistently to the track selector, LIVE / TRACKS screen, LEDs, layers, recording indicators, mute / solo, arrangement sections, web editor and any UI labels. Internal synth loops should continue to address the contiguous synth range; all-track loops should include the drum track exactly once.

The selected track may remain an internal track index if that is least disruptive, but every user-facing navigation path must follow the visible order. Document the distinction in code and test it.

## Audio parts, voices and engine state

- Start with the existing global budget of eight simultaneously sounding synth voices shared fairly across all four synth parts. A fourth synth part must not silently multiply the budget to 32 voices.
- Keep engine-specific polyphony limits (for example, the existing lower caps of GRAIN and PHYS) and make percussion presets responsive and controlled. Do not hard-lock T2 to one engine or one fixed voice count.
- Audit voice allocation, voice stealing, held notes, mono / legato / unison, strum, note-off, pending engine changes and preset fades for all four parts.
- Add the fourth `eng_arena` slot only after measuring `sizeof(eng_arena_t)` and reviewing the linker map. The current pool is 333,900 / 344,064 bytes, with an 8,192-byte reserve; its headroom is too small to assume another arena fits.
- `.data + .bss` currently uses 59,340 / 98,304 bytes, leaving 38,964 bytes before other changes. Assess moving long-lived engine arenas from `.pool` to `.bss` or another explicit memory region. Verify the exact map and stack/interrupt constraints; do not move memory by guesswork.
- Preserve dual-core correctness: render-unit masks, part buffers, FM6 operator buses, PHYS random draws, FORMANT constraints, INSERT state and drum rendering must all remain race-free.

## Sequencing, mixer, effects and MIDI

- Every synth part gets its own 64-step note pattern, engine, preset, parameters, voice state, locks and performance controls.
- The drum machine retains its own 64-step / 16-lane pattern and kit data.
- Audit every array and bitmask sized by `NPART` or `NTRK`, including `vis_note`, `note_hits`, `ex_off`, recording masks, solo masks, mute state, panic handling, undo, strum queues, step-entry queues and live recording.
- Expand synth MIDI channel assignment from three to four distinct channels; retain a separate configurable drum channel. Migrate the settings record without changing existing users' channel assignments unexpectedly.
- Check USB MIDI, TRS MIDI, clock, program change, CC, remote control and MIDI learn routing.
- The mixer must show five tracks in visible order. The existing 36-pixel row does not leave room for five rows plus the current knob footer. Prototype a compact row around 28 pixels high, retaining number, name / engine, record / mute / solo, a useful 16-step overview and level meter. Keep detailed sends / inserts on secondary pages.
- Keep the dedicated drum processing path. Do not accidentally allocate the drum INSERT as a synth INSERT or render the drum track as an ordinary synth part.

## Project format and persistent storage

This is a release-blocking design task.

- Project format 6 is 3,816 bytes and is almost at the 3,840-byte object limit. A naive fifth `proj_trk_t` will exceed it.
- Do not enlarge `project_t` and hope `st_save()` accepts it. `storage.c` rejects payloads larger than `ST_PAYLOAD_MAX`.
- Design a new versioned project representation, with checksum and explicit length, and prove that worst-case fully populated patterns, all parameter locks and all five track states fit the chosen storage strategy.
- Evaluate compact / variable-length per-track encoding and a multi-sector A/B object strategy against the actual flash map. Keep power-loss safety: a torn save must leave the previous valid copy recoverable.
- Audit the flash map before reallocating anything. Preserve four project / section slots, working-project autosave, settings, MIDI settings, user presets, FM6 patches, four user-sample slots and factory data. Do not take space from a sample or preset region without proving the layout and migration.
- Import format 6 and older formats by preserving all old content: old synth tracks 1–3 map, in order, to new visible T2–T4; the old dedicated drum track maps to visible T1; new visible T5 starts empty with the appropriate default sound. This preserves user material even though the new role labels differ from old roles.
- Test load, save, power loss during save, autosave, A/B fallback, arrangement sections, drum tuning / decay, user presets and sample data on both supported flash-chip revisions.

## Theme, graphics and editor compatibility

- Current `theme_t` stores four track colours in a 40-byte THM2 record. The web editor writes this record.
- Define a backward-compatible five-colour theme revision (for example, THM3) or a carefully tested derived fifth colour. If changing the record, keep THM1 and THM2 readable and update the web editor's theme protocol in the same release.
- Check fixed four-element arrays and loops throughout `gfx.c`, `ui_draw.c`, `ui_vis.c`, `ui_studio.c`, the theme import/export path and the offline web editor.
- The visual language is an original AFTERHOURS treatment: dark ink-like field, layered / marbled pigment, turquoise / teal, vermilion / orange, amber and emerald. The *In Rainbows* reference is mood only; do not reproduce the artwork.
- The interface remains a 240 × 240 instrument surface. Keep values and editing legible, animations low-cost and optional, and the existing small-canvas / lazy-redraw model unless profiling justifies a change.
- Create engine-specific reactive imagery from existing audio / parameter metrics. Visualisers must not add work to the audio ISR or cause missed audio deadlines.

## Required acceptance tests

1. Four synth parts plus the dedicated drum machine initialise with the correct defaults and visible ordering.
2. Each synth can load every supported engine and change presets independently.
3. The percussion role plays tuned percussion presets but can also load a normal bass, pad, sample or lead sound.
4. Drum sequencing, 16 lanes, kit changes and drum sound editing remain independent of synth sequencing.
5. All five tracks have independent level, pan, mute, solo, recording, patterns and supported effects.
6. Four synth MIDI channels and the separate drum channel route correctly over USB and TRS.
7. Existing SLOOP projects import without losing patterns, sounds, locks, sections or drum data; new projects save and load worst-case content.
8. Autosave, power-loss recovery and A/B storage fallback pass destructive host simulation and device tests.
9. CPU, RAM, pool, stack, dual-core and audio-dropout tests pass under worst-case simultaneous use.
10. The five-track UI is readable and operable on the FM-1 hardware; all five tracks are selectable in the expected order.
11. Visual animation does not interfere with input, display updates or audio continuity.
12. Installation and recovery are rehearsed on the actual FM-1 before release.

## Non-goals for the first architecture milestone

- No second dedicated drum machine; T2 is a flexible synth part.
- No promise of eight voices per synth part; the initial synth voice budget stays shared.
- No new expensive DSP or full-screen framebuffer before profiling.
- No destructive project or settings migration.
- No firmware installation on the pink FM-1 until the new architecture and recovery path pass.
