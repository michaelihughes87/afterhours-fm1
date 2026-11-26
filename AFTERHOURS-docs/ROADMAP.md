# AFTERHOURS — development roadmap

## Phase 0 — Reproducible baseline

- [x] Import the SLOOP-derived firmware and preserve its source attribution.
- [x] Add a repeatable GitHub Actions firmware build.
- [x] Repair the editor host-test include and restore the original SLOOP palette baseline.
- [x] Calibrate compiler-derived target-cost references for the verified JieLi toolchain.
- [x] Add a toolchain-version guard.
- [x] Produce a passing baseline build at commit `46e51ce`.
- [x] Keep the baseline on `main` and create the isolated `afterhours-five-track` development branch.

**Exit condition:** reproducible firmware package, host / audio regression suite green, and a recoverable baseline retained. This phase is complete.

## Phase 1 — Lock the five-track product

- [x] Confirm five visible tracks: DRUMS, PERCUSSION synth, BASS, AFTER POLY, TEXTURE / SECOND SYNTH.
- [x] Confirm four flexible synth parts plus one dedicated drum-machine part.
- [x] Confirm PERCUSSION is a role and preset collection, not a restricted engine.
- [ ] Update all product, architecture, sound-design and preset documents consistently.
- [ ] Define the visible track order separately from internal synth-part indices.
- [ ] Define old-project migration behaviour and acceptance criteria.

**Exit condition:** one consistent product and architecture specification with no remaining six-track / two-drum-track assumptions.

## Phase 2 — Architecture and resource investigation

- [ ] Enumerate every `NPART`, `NTRK`, `TRK_DRUM`, track-order, voice, MIDI, UI and storage assumption.
- [ ] Generate and review a linker map; measure engine arena sizes and the exact cost of a fourth synth arena.
- [ ] Decide the memory region for four engine arenas without consuming the required pool reserve or threatening stack / ISR memory.
- [ ] Audit voice allocation, dual-core render units, FX state and all per-track runtime arrays.
- [ ] Design project format 7 or later, including worst-case size and power-loss-safe A/B storage.
- [ ] Audit the complete FM-1 flash map before any storage reallocation.
- [ ] Define four synth MIDI channels plus the separate drum channel and settings migration.
- [ ] Define the five-colour theme compatibility strategy and web editor protocol changes.
- [ ] Prototype the five-row mixer layout within the 240 × 240 screen.

**Exit condition:** a measured implementation design that fits flash, RAM, CPU and screen constraints without data loss.

## Phase 3 — Five-track engine and sequencer

- [ ] Implement four contiguous synth parts plus one dedicated drum part.
- [ ] Introduce and test explicit visible-order / internal-index mapping.
- [ ] Extend voice allocation and engine-state ownership to four synth parts; retain a shared eight-voice budget initially.
- [ ] Extend sequencing, parameter locks, live recording, undo, song sections, mute / solo and panic behaviour.
- [ ] Extend USB / TRS MIDI routing to four synth channels and one drum channel.
- [ ] Extend mixer routing, inserts, sends, meters and dual-core scheduling.
- [ ] Implement the new project format and tested migration from formats 1–6.
- [ ] Add host tests for five-track independence, compatibility, storage and recovery.

**Exit condition:** all five tracks work independently in host tests, all existing projects migrate safely, and the firmware passes audio and resource gates.

## Phase 4 — Musical identity and sound library

- [ ] Extend the existing ANALOG engine into the AFTER POLY sound identity; avoid a duplicate oscillator engine unless necessary.
- [ ] Create percussion-focused presets across several existing engines for T2 while preserving unrestricted engine selection.
- [ ] Create a coherent bass preset bank for T3.
- [ ] Create main poly presets for T4 and textures / secondary synth presets for T5.
- [ ] Curate original / properly licensed drum kits for the dedicated drum machine.
- [ ] Balance default levels, envelopes, tuning and performance ranges across all factory sounds.
- [ ] Create starter projects demonstrating trip-hop, post-punk, dub, broken-beat and experimental workflows.

**Exit condition:** a useful, level-balanced instrument with compelling presets and no default clipping or abrupt level surprises.

## Phase 5 — AFTERHOURS interface and visual identity

- [ ] Replace SLOOP identity with AFTERHOURS naming, boot screen and visual system.
- [ ] Implement the five-track mixer overview and predictable track navigation.
- [ ] Implement five distinguishable track colours with backward-compatible theme storage and editor support.
- [ ] Design original dark-ink / marbled-pigment graphics using teal, vermilion, amber and emerald.
- [ ] Build engine-specific reactive visuals for drums, analogue, FM, physical models, sample, noise and grain.
- [ ] Preserve readable values, fast parameter editing, high contrast and a reduced-motion option.
- [ ] Profile rendering so visual activity never causes audio dropouts.

**Exit condition:** the hardware interface is recognisably AFTERHOURS, five-track operation is clear, and the interface remains responsive while playing.

## Phase 6 — Validation and release

- [ ] Run all existing host tests and add targeted five-track regression tests.
- [ ] Run worst-case CPU, RAM, stack, dual-core and audio-continuity tests.
- [ ] Test project import / export, autosave, A/B recovery and interrupted writes.
- [ ] Test MIDI, USB audio, editor, theme import / export and long sessions.
- [ ] Verify both known FM-1 flash IDs: `0x856014` and `0xB36014`.
- [ ] Make a full hardware backup before the first install.
- [ ] Install only after package identity, flash compatibility and recovery route are verified.
- [ ] Rehearse recovery and document the exact release / rollback procedure.

**Exit condition:** an actual pink FM-1 runs the new firmware reliably, saves and restores projects, and can be recovered using the documented procedure.

## Non-goals for the first release

- No second dedicated drum machine.
- No six-track target.
- No literal Prophet '08 clone.
- No costly DSP or full-screen visual effects without measured headroom.
- No install of the unfinished five-track architecture.
