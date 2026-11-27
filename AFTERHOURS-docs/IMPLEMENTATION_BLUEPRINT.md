# AFTERHOURS — Five-Track Implementation Blueprint

**Document status:** Design / implementation plan; not a firmware patch.  
**Repository:** `michaelihughes87/afterhours-fm1`  
**Development branch:** `afterhours-five-track`  
**Design baseline:** `d18c85ba9482c5606bbeb2aa4b6ece8d15eade51`  
**Scope:** Resolve the product order, project and memory strategy, MIDI, mixer / theme, engine integration and validation sequence before five-track firmware implementation.  
**Safety:** Do not flash this development branch to the pink FM-1. The current branch still contains the original three-synth-plus-drum firmware architecture.

---

## 1. Executive decision

AFTERHOURS is a five-visible-track instrument:

| Visible order | Track | Default musical role | Internal track index |
|---:|---|---|---:|
| 1 | **DRUMS** | Dedicated 16-lane drum machine | 4 |
| 2 | **AFTER POLY** | Prophet warmth + Juno movement | 0 |
| 3 | **ORGAN / KEYS** | Soulful organ, Rhodes / Wurlitzer-style keys | 1 |
| 4 | **MONO BASS** | Minimoog weight + Pro-One articulation | 2 |
| 5 | **TEXTURE / PERC** | Granular / digital / atmospheric sounds and selected percussion | 3 |

This is one dedicated drum part and four flexible synth parts. The track names describe default sound-library roles, not restrictions. Any supported synth engine and ordinary preset must be loadable on any of the four synth parts.

There is **no sixth percussion track**. Texture and percussion share visible track 5.

### Proposed internal constants

```c
#define NPART 4
#define NTRK 5
#define TRK_DRUM 4
#define NVOICE 8
```

The internal synth parts remain contiguous in `trk[0..3]`. The drum part is `trk[4]`. The first implementation should retain the existing global budget of eight simultaneously sounding synth voices across all four synth parts.

### Visible/internal mapping

```c
static const uint8_t VISIBLE_TO_INTERNAL[5] = {4, 0, 1, 2, 3};
```

A corresponding inverse mapping is required:

```c
static const uint8_t INTERNAL_TO_VISIBLE[5] = {1, 2, 3, 4, 0};
```

The exact helper names are implementation choices. The mapping must be centralised, range-checked and unit-tested. Do not spread literal index translations throughout the UI.

**Selection-state decision:** `song.sel`, recording masks, solo masks, sequencer queues and DSP arrays should continue to use internal track indices unless a specific interface contract requires otherwise. Convert only at user-facing boundaries. This minimises changes to audio and sequencing code.

---

## 2. Verified baseline constraints

These measurements and structures describe the existing firmware, not a five-track build.

### 2.1 Target memory report

The successful diagnostic build of the original firmware reported:

| Region | Current use | Capacity | Remaining |
|---|---:|---:|---:|
| Main `.data + .bss` | 59,340 B | 98,304 B | 38,964 B |
| `.pool` | 333,900 B | 344,064 B | 10,164 B |
| `.pool` headroom above required reserve | — | 8,192 B reserve | 1,972 B |
| `.lowram` | 22,772 B | 29,384 B | 6,612 B |
| `.noinit` | 15,472 B | 15,696 B | 224 B |

The current engine arena array is allocated in `.pool`, one arena per synth part. The `.pool` has only 1,972 bytes beyond its required reserve. Do not add another full engine arena to that pool.

The `.bss` headroom makes it a plausible location for the fourth synth part's engine arena, but this is **a candidate, not an approved allocation**. The new `track_t`, per-part runtime arrays, inserts, MIDI state, and any other added objects must be included in the target link map. The `.lowram` region is already used for second-core / audio-related work and has only 6,612 bytes reported free; do not assume it is spare general-purpose RAM.

The diagnostic build should continue to emit the symbol and section reports after every memory-affecting step. Host CPU tests and compiler-derived target loop-cost checks are regression tools; neither substitutes for measuring real-time behaviour on the FM-1.

### 2.2 Project and NOINIT constraint

Current source facts:

- Project format 6 is 3,816 bytes.
- `storage.c` permits a maximum payload of 3,840 bytes per flash object.
- Four project slots are cached in `.noinit`.
- Four format-6 project slots occupy `4 × 3,816 = 15,264` bytes.
- The full measured `.noinit` usage is 15,472 / 15,696 bytes, leaving just 224 bytes.
- A straightforward five-track project object is estimated at about 4,750 bytes. Four expanded copies would require about 19,000 bytes before other `.noinit` objects, so this cannot fit.

Do not change `NTRK` and allow the existing `project_t proj_slot[4]` to grow. That would overrun the region.

### 2.3 Flash storage map

The current `storage.c` map documents:

| Purpose | Existing address range / sectors |
|---|---|
| Project A/B objects | `0x97000..0x9EFFF` |
| Working autosave A/B | `0x9F000` and `0xFE000` |
| Four user-sample slots | `0xA0000..0xDBFFF` |
| User preset banks | `0xDC000..0xDFFFF` |
| FM6 patch bank | `0xE5000` and `0xE6000` |
| Settings A/B | `0xFC000` and `0xFD000` |

Each persistent object uses A/B sectors. `st_save()` writes the alternate copy and writes the validity header last; the previous valid copy remains available if a write is interrupted.

**Do not borrow sectors from the four sample slots, user presets, project slots or update staging without a complete flash-map review and migration plan.**

Guru-600's P600 patch-store addresses must not be copied into AFTERHOURS: its current `0xD9000 / 0xDA000` allocation conflicts with the FM-1 user-sample address region used by this firmware family.

---

## 3. Project format strategy

### 3.1 Format 7 is a compact-storage candidate, not yet approved

The existing source audit contains a calculated compact format-7 proposal of **3,813 bytes**:

| Component | Calculation | Bytes |
|---|---:|---:|
| Four synth tracks | `4 × (73 metadata + 512 synth steps + 64 nudge/fill + 72 locks)` | 2,884 |
| One drum track | `73 metadata + 640 drum steps + 64 nudge/fill + 72 locks` | 849 |
| Header, globals, selection, reserved bytes and checksum | Fixed | 80 |
| **Calculated total** | | **3,813** |
| Existing payload maximum | | 3,840 |
| **Calculated margin** | | **27** |

This is a useful route because `4 × 3,813 = 15,252` bytes for four cached section records. With the currently measured 208 bytes of other NOINIT objects, the calculated total would be 15,460 bytes, leaving 236 bytes in the existing region.

However, the format is **not implemented, range-tested or proven**. Its safety depends on several assumptions:
- Synth steps can be encoded in exactly eight bytes without losing note, timing, flags, velocity, level or ratchet information.
- Drum steps remain ten bytes and retain all 16 lane states, levels and ratchets.
- All 24 locks per track can be stored in three bytes each.
- Every packed parameter and lock value fits its proposed signed-byte representation.
- Engine and preset identity remains stable and is not renumbered.
- Header, reserved bytes, checksum and migration information are included in the exact serialized size.

The 27-byte margin is very small. Format 7 must be a fixed, versioned byte representation with compile-time / host-test size assertions. Do not rely on compiler struct padding or append fields casually.

### 3.2 P600 decision must precede format freeze

Guru-600's P600 engine has more controls than the current generic eight engine-specific parameter slots (`P_E0..P_E7`). The existing compact format-7 parameter block budgets eight engine values.

Therefore:
1. Finish the P600 parameter-map investigation first.
2. Decide whether P600 is a first-release engine, a later optional engine or only a sound-design reference.
3. If P600 is included, design how its full parameter set and patch identity are saved in projects and user presets.
4. Recalculate and re-test the complete format before freezing it.

Do not squeeze extra P600 values into reserved bytes without a formally versioned layout and worst-case size test. A separate patch-bank reference is one possible design, but its flash location and migration must be safe.

### 3.3 Recommended storage architecture

Use a compact, versioned five-track record for the four section caches and the working autosave. Keep the existing A/B sector model.

The active `trk[]` array is already the runtime representation. Project capture should serialise from the live tracks into a compact record; project apply should validate and decode the compact record directly into the live tracks. Avoid introducing four expanded five-track runtime project objects in `.noinit`.

Keep the legacy format 1–6 structures as explicit, fixed-size read-only types. They must retain their original four-track layout even after `NTRK` becomes 5. In particular, do not let legacy definitions use the new `NTRK` macro for their array lengths.

### 3.4 Old-project migration

The old project order is three synth tracks followed by the drum track. The new internal order is four synth parts followed by the drum track.

For old formats 2–6:

| Old project track | New internal track | New visible track |
|---|---|---|
| Old synth 1 | `trk[0]` | T2 AFTER POLY |
| Old synth 2 | `trk[1]` | T3 ORGAN / KEYS |
| Old synth 3 | `trk[2]` | T4 MONO BASS |
| Old drum track 4 | `trk[4]` | T1 DRUMS |
| New synth part | `trk[3]` | T5 TEXTURE / PERC; start empty with its role default |

If the old selected-track index was 3 (the drum track), migrate it to internal index 4. Old synth selections 0–2 remain unchanged.

For format 1, retain the existing behaviour: its single instrument loads into the first synth part (new internal `trk[0]`, visible T2); other tracks start with defaults and empty patterns.

Every legacy format must be imported by explicit version-specific structures and converters. Preserve patterns, parameter locks, microtiming, fills, drum data, drum tuning / decay, globals and all valid sound identity fields. Test the conversion rather than assuming old binary layouts remain compatible.

### 3.5 Project acceptance tests

- Format 7 exact byte length is at most 3,840, with every field and reserved byte documented.
- Four packed section records fit the `.noinit` memory map.
- Worst-case five-track projects fit: 64 steps per track, 24 locks per track, full parameter ranges, all globals and full drum data.
- Pack / unpack round trips preserve every field.
- Invalid parameter ranges, locks, engine IDs, presets, checksums and lengths are rejected safely.
- Formats 1–6 import without loss using their original fixed-size layouts.
- A/B save is interrupted at each meaningful erase / program / commit stage; the prior valid project must still load.
- Working autosave, section saves, erase, power-cycle recovery and user-preset / sample data remain intact.
- Backup / restore and web-editor project paths use the same versioned data rules.

---

## 4. Track, sequencing and audio architecture

### 4.1 Keep synth parts contiguous internally

The least disruptive first design is:

- `NPART = 4`
- `NTRK = 5`
- `TRK_DRUM = 4`
- `trk[0..3]` are the four synth parts.
- `trk[4]` is the dedicated drum part.

Keep `TDRUM` as the dedicated drum pointer. Keep synth loops bounded by `NPART` and all-track loops bounded by `NTRK`. Review all array sizes, masks and hard-coded indices; changing three macros alone is not a five-track implementation.

### 4.2 Visible order and selection

Use the mapping `[4, 0, 1, 2, 3]` only where the user sees or selects a track.

Key UI boundaries:
- Track navigation and selection.
- LIVE / TRACKS display rows and row numbers.
- Track colours and meters.
- Mute / solo / record indicators.
- Confirmation messages and “track cleared” labels.
- Drum-page entry and key-layer behaviour.
- Web editor track selectors and messages.
- Program-change / editor-facing track IDs, where protocol semantics are user-visible.

`TSEL` and the audio / sequencer core can continue to use internal indices. Central helpers must convert between visible positions and internal track indices.

### 4.3 Shared voice budget

The current code stores `NVOICE` voice slots in each track's runtime state, but `voice.c::voices_busy()` counts sounding voices across all synth parts and enforces a shared budget of eight.

For AFTERHOURS:
- Keep the initial total sounding synth voice budget at eight.
- Do not accidentally change the system to eight voices per synth part.
- Preserve engine-specific polyphony caps (FM6, GRAIN, PHYS and others).
- Extend voice stealing / allocation fairly across four synth parts.
- Test mono, legato, unison, glide, note-off, held notes, arpeggiators, sequencer notes, MIDI notes and fades.
- Keep the drum track's voice path separate from the shared synth budget.

### 4.4 Engine memory placement

The current `eng_arena[NPART]` is in `.pool`. The `.pool` reserve makes a fourth arena there unsafe.

Recommended investigation:
1. Measure `sizeof(track_t)`, `sizeof(eng_arena_t)`, `sizeof(gr_part_t)`, `PHYS_ARENA`, per-part INSERT / filter state and every new track-sized array with the target compiler.
2. Measure stack high-water marks and the actual linker map.
3. Prototype keeping the current three arenas in `.pool` and placing the fourth arena in ordinary RAM (`.bss`) or another explicitly sized, proven region.
4. Refactor all accesses through one arena accessor. `phys_render_draws()` currently derives an arena pointer directly and must use the same mapping.
5. Check `.bss`, `.pool`, `.lowram`, NOINIT, both stacks, DMA and second-core memory after the change.
6. Keep the required 8 KiB pool reserve and all measured stack guards.

This is a candidate allocation strategy, not permission to move an arena before the target map is understood.

### 4.5 Dual-core rendering and effects

Audit all `NPART` / `NTRK` assumptions in:
- `engines.c`, `voice.c`, `fx.c`, `drums.c`, `seq.c`.
- Part buffers, engine ownership, PHYS random-draw constraints and FORMANT restrictions.
- INSERT state, filter state, `U_ALL`, `U_DRUMS`, render masks and core split logic.
- Recording, note hits, note-offs, panic, mute / solo, strum, undo, live recording, sequencer queues and arranger snapshots.

`fx.c::units_split()` currently places the final synth part and the drum renderer on one core by default. With four synth parts, that becomes synth part 4 plus drums. Benchmark that combination and the worst-case alternate split; do not assume the current core distribution remains balanced.

---

## 5. MIDI and settings compatibility

### Existing source constraint

The current MIDI channel implementation uses `G_CH1`, `G_CH2`, `G_CH3`, one drum channel and OTHER routing. `seq.c` calculates a synth channel using `song.g[G_CH1 + i]`. With four synth parts, `i == 3` would reach the adjacent `G_CHOTH` ID rather than a fourth synth channel.

The persisted `MIDI_PART` currently contains a 32-byte MIDI-learn map plus eight bytes of channel / related settings (40 bytes total). Those eight bytes are already allocated.

### Recommended design

- Add `G_CH4` at the end of the existing global-parameter ID sequence, immediately before the new `G_COUNT`; do not insert it between existing IDs.
- Update the global parameter count and static assertions without renumbering existing `G_*` values.
- Replace `G_CH1 + i` with an explicit four-entry synth-channel table / helper.
- Extend `midi_set` and its defaults with a fourth synth channel; provisional default is MIDI channel 4.
- Retain the current drum channel as a separate setting; provisional default remains channel 10.
- Append one byte to the persisted MIDI settings extension for CH4. Keep the old 32-byte, 36-byte and 40-byte records readable; initialise CH4 to its default when reading an older record.
- Update `midi_part_fill`, `midi_part_read`, `midi_part_default`, settings load / save, `felucca_init`, UI pages, channel-uniqueness enforcement and web-editor backup / restore.
- Keep channel settings device-wide, as they are now; they are not song-project data.

### MIDI acceptance tests

- Four synth channels independently route note on / off, CC, program change and pitch bend.
- Drum channel remains independent and configurable.
- OFF, OTHER = selected track and duplicate-channel correction work.
- Changing a channel while notes are held sends note-offs on the original channel.
- USB MIDI, TRS MIDI, clock, START / STOP, MIDI learn and remote CC remain correct.
- Older persisted MIDI records load with the first three synth channels and drum channel preserved, and CH4 defaulted safely.

---

## 6. Mixer, navigation and visual interface

### 6.1 Five-row mixer proposal

The current FM-1 screen is 240 × 240:
- Header occupies approximately 40 px.
- Four existing track rows are 36 px each.
- The knob footer begins at y = 184 and occupies the bottom 56 px.

Five 36 px rows do not fit. A useful first layout experiment is:

- Header: 40 px.
- Five rows: approximately 28 px each (140 px total).
- Existing knob footer: 56 px beginning around y = 184.
- Four pixels of separation between the rows and footer.

This gives a 240 × 240 screen without removing the four knob readouts. The row content will need redesign: smaller track tile, title / engine name, compact status indicator, a 16-step miniature overview and a short level meter. Treat 28 px as a prototype dimension; validate legibility and operation on the actual panel before locking it.

Detailed sends, inserts and sound editing can remain on secondary pages. Keep the useful four-knob interaction and the existing SLOOP workflow strengths.

### 6.2 Mute / solo layer

The current mixer layer exposes four mute controls and four solo controls, followed by fill / bar / tap functions. With five tracks, the 16-key surface can accommodate:
- Keys 1–5: mute tracks 1–5.
- Keys 6–10: solo tracks 1–5.
- Remaining assigned keys: fill, next-bar fill and tap / tempo functions.

The labels and colors must follow visible order while the stored mute / solo masks remain indexed internally.

### 6.3 Track colours and themes

The current theme is THM2:
- `theme_t` is 40 bytes.
- Four track colours are stored.
- The theme and favourites share an 80-byte side record.
- `ST_SIDE_MAX` is 192 bytes, so a modest expansion is feasible.

Recommended approach:
- Define THM3 with five stored track colours.
- Keep the visible colour order: DRUMS, AFTER POLY, ORGAN / KEYS, MONO BASS, TEXTURE / PERC.
- A five-colour `theme_t` is expected to be 44 bytes after alignment; the side record becomes 84 bytes, still within the 192-byte side-record allowance.
- Continue reading THM1 and THM2. Convert old four-colour themes to the new order: old drum colour to T1; old synth colours 1–3 to T2–T4; derive a sensible fifth colour for T5.
- Update the Theme page in the web editor, its byte protocol, import / export validation and theme tests.
- Keep contrast validation for the background, strongest palette colour and selection accent.

This should be implemented as a versioned migration, not by silently interpreting a THM2 byte sequence as THM3.

### 6.4 AFTERHOURS visual identity

Once the five-track layout is stable:
- Use an original dark-ink / layered-pigment visual language.
- Use turquoise / teal, vermilion, amber and emerald as the palette direction.
- Give all five tracks distinguishable colours.
- Build low-cost, engine-specific reactive imagery from existing parameter / audio metrics.
- Keep text, values and controls legible and primary.
- Do not add full-screen framebuffers or audio-ISR graphics work without measured evidence.

---

## 7. Sound and engine integration sequence

The five-track roles are now fixed, but default engine / preset choices should be made after audition.

| Track | Sound priority | Existing starting points |
|---|---|---|
| T1 DRUMS | Weighty, punchy, hybrid acoustic / synthetic / sampled kits; breaks, dub and industrial options | Existing DEEP / TIGHT / ACOUSTIC / DUST and SYN kits; drum synthesis |
| T2 AFTER POLY | Prophet warmth + Juno movement; rich chords, warm pads, musical brass and subtle modulation | ANALOG first; compare Guru-600 P600 as an optional separate engine experiment |
| T3 ORGAN / KEYS | Soulful drawbar organ, warm Rhodes / Wurlitzer and useful keyboard sounds | DRAWBAR / WHEEL, DIGITAL RHODES / WURLI, FM6 TINE EP |
| T4 MONO BASS | Minimoog weight + Pro-One articulation; stable sub through controlled drive | ANALOG first; TRIO and FM6 only where they add a different sound |
| T5 TEXTURE / PERC | Dark digital / granular / atmospheric sounds plus a small useful selection of resonant / tuned percussion | GRAIN, SAMPLE, PHASE, NOISE, FM6, PHYS and DIGITAL |

Glockenspiel, xylophone, chimes and bells should be present as occasional colours, not a major development stream.

### Guru-600 / P600 gate

Guru-600 is worth a controlled technical investigation because its Prophet-600 engine offers a four-pole ladder filter, dedicated filter envelope, hard sync and Poly-Mod. It is not a Prophet-5, and its engine is not a drop-in component.

Before integration:
1. Compare existing ANALOG poly sounds against the desired Prophet / Juno character.
2. Map all P600 controls to AFTERHOURS parameters without reusing DIGITAL's engine identity or changing existing engine indices.
3. Establish whether the P600 needs more than the current eight generic engine parameters.
4. Port only as an isolated engine experiment, retain the GPL notices and measure target code / data / CPU.
5. Do not import its patch bank or copy its flash addresses.
6. Keep it optional until it demonstrates a clear audible improvement and a safe save / recall design.

### Sound manipulation

The current firmware already offers track filter, distortion, chorus / delay / reverb sends, track inserts (including clipping, fold, fuzz, bit reduction, phasing, flanging and chorus) and master processing / texture.

A full parametric EQ is not established in the current source assessment. Evaluate whether existing filter / tone / insert facilities meet the musical need first. If not, prototype the smallest useful tone-shaping control and measure it before promising a full EQ.

The target is around 40 excellent, distinctive, controllable factory sound / kit programs. The initial 20 prototypes are a listening and comparison programme, not an instruction to fill slots regardless of quality.

---

## 8. Recommended implementation order

This order keeps high-risk data and memory issues in front of visible polish, while ensuring P600 is considered before the storage schema is frozen.

### Stage 0 — Product decisions and design freeze
- [x] Five visible tracks and roles agreed.
- [x] Visible order agreed: DRUMS → AFTER POLY → ORGAN / KEYS → MONO BASS → TEXTURE / PERC.
- [x] Four flexible synth parts plus one dedicated drum part.
- [x] Shared eight-voice synth budget retained as the starting constraint.
- [x] Sonic direction and prototype sound families documented.

**Exit:** one consistent product specification and implementation blueprint.

### Stage 1 — P600 parameter and preset feasibility gate
- Review Guru-600 P600 control count / mapping and differences from the current ANALOG engine.
- Identify a safe engine-index and parameter representation.
- Decide whether P600 is optional first-release scope, later scope or reference-only.
- Decide how its patch data could be stored without overlapping user samples or existing patch banks.
- Do not implement a flash patch store yet.

**Exit:** a clear engine decision and a stable list of parameters that projects / presets must preserve.

### Stage 2 — Project format 7 host implementation
- Define fixed byte offsets and packing routines.
- Prove all parameter / lock ranges before narrowing values.
- Implement pack / unpack and checksum validation.
- Define fixed legacy formats 1–6 with exactly four old tracks.
- Migrate old synth / drum / selected-track indices to the new internal arrangement.
- Test worst-case five-track data and interrupted A/B saves.
- Verify four packed NOINIT records fit the target region.

**Exit:** project format and migration tests pass without changing live firmware track count.

### Stage 3 — Track mapping and four-synth structure
- Introduce central visible / internal mapping helpers and host tests.
- Expand to four synth parts and five total tracks.
- Move drum internal index to 4.
- Audit all direct `trk[]` selections, loops, fixed arrays and masks.
- Keep `song.sel` and runtime masks internally indexed.

**Exit:** all track-index and project-migration tests pass.

### Stage 4 — Audio, engine memory and sequencing
- Add fourth synth-part state.
- Measure the new track and arena sizes.
- Allocate the fourth engine arena in a proven memory region.
- Extend voice allocation while retaining the shared eight-voice limit.
- Update render split, effects, MIDI note state, live recording, undo, strum, arpeggiators and dual-core scheduling.
- Run target memory and worst-case CPU tests.

**Exit:** audio / sequencing tests pass and all memory reserves remain valid.

### Stage 5 — MIDI and settings migration
- Append CH4 without renumbering existing global IDs.
- Extend device settings by one byte with legacy read support.
- Update channel pages, collision handling and web-editor settings.
- Test four synth channels and the separate drum channel.

**Exit:** MIDI routing and old settings migration pass.

### Stage 6 — Five-track mixer, colours and editor
- Prototype five 28 px rows on the 240 × 240 display.
- Implement the visible order everywhere the user selects or sees tracks.
- Extend mute / solo layer controls to five tracks.
- Add THM3 and read THM1 / THM2.
- Update the web editor theme protocol and backup / restore.
- Test legibility, input latency, drawing cost and audio continuity.

**Exit:** five-track navigation and theme compatibility pass on hardware / emulator.

### Stage 7 — Sound library and performance controls
- Audition existing drum kits first.
- Refine AFTER POLY starting sounds.
- Curate ORGAN / KEYS and MONO BASS.
- Curate TEXTURE / PERC.
- Complete the P600 decision / implementation only if it passed its feasibility gate.
- Expose the most useful synthesis, filter, envelope, modulation, drive and effect controls quickly.
- Create and level-match the strongest 20 prototypes, then grow selectively toward 40.

**Exit:** distinctive, useful and balanced factory sounds; no generic filler or unpleasant default harshness.

### Stage 8 — Release and pink FM-1 validation
- Run all host tests, golden audio renders, fuzz tests, ThreadSanitizer and dual-core timing tests.
- Run worst-case four-synth-plus-drums target CPU / memory tests.
- Verify both known flash IDs (`0x856014` and `0xB36014`).
- Back up the actual device, its projects, samples, user presets and flash data.
- Verify exact hardware identity and recovery route.
- Install only a release candidate after all gates pass.
- Test long sessions, save / load, MIDI, audio and recovery on the pink FM-1.

**Exit:** AFTERHOURS runs reliably on the actual hardware and can be recovered using a rehearsed procedure.

---

## 9. Risk register

| Risk | Severity | Mitigation / gate |
|---|---|---|
| Five-track project data exceeds flash or NOINIT | Critical | Compact v7 record, exact byte layout, range tests and power-loss tests |
| P600 needs more parameters than the generic engine model | High | Resolve P600 before format freeze; separate patch identity / storage design |
| Fourth engine arena breaks `.pool` reserve | Critical | Target map, measured split arena allocation and stack / BSS tests |
| Internal index leaks into visible UI order | High | One mapping helper; test every navigation / editor path |
| Fourth synth MIDI channel aliases OTHER | High | Append G_CH4; explicit channel table; settings migration |
| Five-row screen is too cramped | Medium | Prototype 28 px rows; keep detailed controls on secondary pages |
| Theme format / web editor becomes incompatible | Medium | THM3 plus THM1 / THM2 migration and editor protocol tests |
| P600 patch store destroys user sample data | Critical | Never adopt Guru addresses; full flash-map check |
| Presets become harsh, generic or uneven in level | Medium | Audition and scorecard; strict quality gate |
| Audio load becomes unbalanced across cores | High | Worst-case simultaneous-engine and core-load tests |

---

## 10. Explicit non-goals for the first implementation

- No sixth track.
- No second dedicated drum machine.
- No percussion-only synth track.
- No multiplication of the shared synth voice budget to 32 voices.
- No automatic adoption of Guru-600's patch-bank addresses or bundled patch data.
- No project-format freeze until the P600 parameter decision is resolved.
- No promise of a full parametric EQ, unrestricted modulation matrix, Eventide-class effects or full EMS patch matrix without a measured design.
- No chord-generation or generative-progression work ahead of sound quality, sound control and performance workflow.
- No firmware installation on the pink FM-1 before the five-track architecture and recovery path are validated.

---

## 11. Source references

All paths below refer to the `afterhours-five-track` development branch.

- [Core track, voice and parameter definitions](https://github.com/michaelihughes87/afterhours-fm1/blob/afterhours-five-track/firmware/src/core.h)
- [Project formats, migration, capture and apply](https://github.com/michaelihughes87/afterhours-fm1/blob/afterhours-five-track/firmware/src/project.c)
- [A/B flash storage and address map](https://github.com/michaelihughes87/afterhours-fm1/blob/afterhours-five-track/firmware/src/storage.c)
- [Engine arenas and engine-index order](https://github.com/michaelihughes87/afterhours-fm1/blob/afterhours-five-track/firmware/src/engines.c)
- [Voice allocation and shared budget](https://github.com/michaelihughes87/afterhours-fm1/blob/afterhours-five-track/firmware/src/voice.c)
- [Sequencer and MIDI track routing](https://github.com/michaelihughes87/afterhours-fm1/blob/afterhours-five-track/firmware/src/seq.c)
- [Mixer and render split](https://github.com/michaelihughes87/afterhours-fm1/blob/afterhours-five-track/firmware/src/fx.c)
- [Five-row mixer starting point](https://github.com/michaelihughes87/afterhours-fm1/blob/afterhours-five-track/firmware/src/ui_studio.c)
- [Theme storage and track colours](https://github.com/michaelihughes87/afterhours-fm1/blob/afterhours-five-track/firmware/src/gfx.c)
- [Track defaults and interface pages](https://github.com/michaelihughes87/afterhours-fm1/blob/afterhours-five-track/firmware/src/ui.c)
- [Mute / solo layers](https://github.com/michaelihughes87/afterhours-fm1/blob/afterhours-five-track/firmware/src/ui_layers.c)
- [Boot / track initialisation](https://github.com/michaelihughes87/afterhours-fm1/blob/afterhours-five-track/firmware/src/main.c)
- [Guru-600 P600 engine](https://github.com/MarcGoudy/guru-600/blob/main/firmware/firmware/src/eng_p600.c)
- [Guru-600 P600 patch storage](https://github.com/MarcGoudy/guru-600/blob/main/firmware/firmware/src/p600_store.c)
- [Guru-600 licensing notes](https://github.com/MarcGoudy/guru-600/blob/main/docs/firmware/LICENSING.md)

---

**Implementation principle:** measure first, preserve existing data and working audio behaviour, introduce one structural change at a time, and require a passing build plus focused regression tests before proceeding to the next stage.
