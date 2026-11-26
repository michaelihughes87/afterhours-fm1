# Development roadmap

## Phase 0 — Establish a reproducible baseline

- [ ] Import upstream SLOOP source, preserving full history and attribution.
- [ ] Record upstream commit, release baseline and firmware identity.
- [ ] Build unmodified upstream on the Mac.
- [ ] Run all upstream host / regression tests.
- [ ] Archive known-good build outputs.
- [ ] Confirm current FM-1 firmware and hardware / flash-chip revision before any install.

**Exit condition:** reproducible build, tests pass, recovery route understood.

## Phase 1 — Product identity and preset experience

- [ ] AFTERHOURS visual identity and colour system.
- [ ] Curated factory preset and kit names / categories.
- [ ] First trip-hop, post-punk and industrial starter projects.
- [ ] Sound design across existing SLOOP engines.
- [ ] Retain SLOOP sequencing / project functions unchanged.

## Phase 2 — Six-track architecture spike

- [ ] Map all SLOOP track and part arrays, serialization, UI, MIDI and FX assumptions.
- [ ] Prototype six independent parts based on the SLOOP architecture.
- [ ] Evaluate selective port/adaptation of JIANT six-part design.
- [ ] Validate two DRUM-X tracks as independent engines with independent kits.
- [ ] Build / test project migration and storage compatibility.
- [ ] Benchmark CPU / RAM and audio dropouts on worst-case content.

**Exit condition:** six tracks pass structural, storage, MIDI and audio stress tests. If not, evaluate a five-track fallback rather than shipping unstable six-track operation.

## Phase 3 — Mixer and sound engines

- [ ] Fast six-strip mixer and per-track effects / sends.
- [ ] Independent drum-track processing and complete kit access.
- [ ] Extend SLOOP ANALOG into AFTER POLY.
- [ ] Preset bank for two-oscillator poly pads, plucks, leads and bass.
- [ ] Add TAPE / DUST / DRIFT / SPACE / DECAY only after DSP budget measurement.

## Phase 4 — Reactive visual instrument

- [ ] Distinct sound-reactive visual for each engine.
- [ ] Drum-kit colony graphic.
- [ ] Oscillator / filter visual for AFTER POLY.
- [ ] Track-colour and graphic theme settings.
- [ ] Reduced-motion and high-contrast alternative.
- [ ] Frame-rate and audio-load tests during animation.

## Phase 5 — Release readiness

- [ ] Save/load migration tests and backup / restore rehearsal.
- [ ] MIDI, USB audio, editor and long-session testing.
- [ ] Actual-device beta testing across supported FM-1 hardware revisions.
- [ ] Licence, asset attribution, source and recovery documentation.
- [ ] Public release only after a verified install and recovery procedure.

## Non-goals for the first build

- A literal Prophet '08 clone.
- Six independent full insert FX chains per drum lane before CPU testing.
- High-cost granular / convolution processing before profiling.
- Cosmetic animations that obscure controls or interrupt audio.
