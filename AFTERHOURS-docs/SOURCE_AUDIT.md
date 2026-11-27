# AFTERHOURS — five-track source audit

**Audit baseline:** `46e51ce433e9e73c8d6cac0e8eeebfce519feb2c`
**Development branch:** `afterhours-five-track`
**Product decision:** five visible tracks — one dedicated drum machine plus four fully flexible synth parts.

This is a source-level design audit. It identifies existing assumptions and proposes implementation strategies. It is not a firmware patch, a target memory measurement after modification, or a claim that the proposed packed project format has already passed tests.

---

## 1. Agreed instrument architecture

### Visible track order

| Visible track | Role | Track type |
|---|---|---|
| 1 | DRUMS | Dedicated 16-lane drum machine |
| 2 | AFTER POLY | Ordinary, fully flexible synth part; Prophet warmth + Juno movement |
| 3 | ORGAN / KEYS | Ordinary, fully flexible synth part; soulful organ and warm electric keys |
| 4 | MONO BASS | Ordinary, fully flexible synth part; Minimoog weight + Pro-One articulation |
| 5 | TEXTURE / PERC | Ordinary, fully flexible synth part; atmosphere, granular / digital sounds and selected percussion |

All four synth tracks must be able to use any existing or future synth engine. T5 is not a second drum-machine track or a percussion-only engine; it combines textures and selected percussion presets because the agreed instrument has five tracks.

### Recommended internal arrangement

Keep the four synth parts contiguous for the existing DSP architecture:

```text
Internal trk[] indices:
0 = synth part A (visible T2, AFTER POLY role)
1 = synth part B (visible T3, ORGAN / KEYS role)
2 = synth part C (visible T4, MONO BASS role)
3 = synth part D (visible T5, TEXTURE / PERC role)
4 = dedicated drum part (visible T1)

Visible-to-internal mapping:
[4, 0, 1, 2, 3]
```

The exact default engines and presets can be curated later. This mapping is a low-disruption proposal, not yet implemented.

**Do not assume visible row number equals `trk[]` index.** Add two explicit, tested helpers, for example:

- `trk_from_visible(visible_index)`
- `trk_to_visible(internal_index)`

Every user-facing selection and editor request must go through the mapping. DSP loops should continue to address the four contiguous synth parts and the separate drum part.

### Existing project migration

Existing projects store three synth tracks followed by the dedicated drum track. With the proposed internal arrangement:

- Old synth track 1 -> new internal synth 0 / visible T2.
- Old synth track 2 -> new internal synth 1 / visible T3.
- Old synth track 3 -> new internal synth 2 / visible T4.
- Old drum track -> new internal drum 4 / visible T1.
- New internal synth 3 / visible T5 starts empty with its chosen TEXTURE / PERC default sound.
- If an old project selected the old drum track (index 3), migrate the selected index to new internal index 4. Existing synth selections retain indices 0–2.

This preserves existing sounds and patterns while introducing the new layout.

---

## 2. Source audit: track and audio assumptions

The current firmware is built around `NPART=3`, `NTRK=4`, `TRK_DRUM=3`.

### Core and engine state

| Source | Current assumption | Required work |
|---|---|---|
| `firmware/src/core.h` | `NPART=3`, `NTRK=4`, `TRK_DRUM=3`; `trk[NTRK]`; selected track is an internal array index | Move to four synth parts, five total tracks, drum index 4; document index semantics |
| `firmware/src/engines.c` | `eng_arena[NPART]`; one large engine-state arena per synth part | Add a fourth arena, but first resolve memory placement |
| `firmware/src/voice.c` | Voice allocation, victim search, note-hit arrays and engine fades loop over `NPART`; shared `NVOICE=8` budget | Include four synth parts; initially retain one shared budget of eight simultaneous synth voices |
| `firmware/src/fx.c` | Synth filters, INSERT state, render units, core split masks and drum render bit depend on `NPART` / `NTRK` | Audit every array, loop and mask; keep drum processing separate |
| `firmware/src/drums.c` | Drum mix uses `TDRUM` / `TRK_DRUM` | Update the constant and retain the dedicated drum-only path |

Useful source locations:

- [core.h](https://github.com/michaelihughes87/afterhours-fm1/blob/46e51ce433e9e73c8d6cac0e8eeebfce519feb2c/firmware/src/core.h#L9-L13)
- [engines.c](https://github.com/michaelihughes87/afterhours-fm1/blob/46e51ce433e9e73c8d6cac0e8eeebfce519feb2c/firmware/src/engines.c#L36-L68)
- [voice.c](https://github.com/michaelihughes87/afterhours-fm1/blob/46e51ce433e9e73c8d6cac0e8eeebfce519feb2c/firmware/src/voice.c#L69-L105)
- [fx.c render units](https://github.com/michaelihughes87/afterhours-fm1/blob/46e51ce433e9e73c8d6cac0e8eeebfce519feb2c/firmware/src/fx.c#L811-L915)
- [drums.c](https://github.com/michaelihughes87/afterhours-fm1/blob/46e51ce433e9e73c8d6cac0e8eeebfce519feb2c/firmware/src/drums.c#L379-L381)

### Important DSP detail: do not multiply the voice budget

`NVOICE` is currently a shared eight-voice sounding budget across all synth parts; it is not eight independent voices per synth part in practice. The fourth synth part must participate in the same allocation / voice-stealing policy. Do not increase polyphony to 32 as a side effect of adding a part.

The four parts still need independent held-note state, arpeggiators, sequencer state, engine state and fades. Existing per-engine polyphony caps (for example GRAIN and PHYS) must remain effective.

### Other arrays and systems to audit

`NPART` / `NTRK` appear in more than the obvious track array. These are known source locations from the baseline:

- `voice.c`: `note_hits[NPART][4]`, `vis_note[NTRK]`, voice counts, allocation, engine fade bookkeeping and ENV-sync arrays.
- `fx.c`: `tflt[NTRK]`, `ins[NPART + 4]`, part INSERT indexing, `U_DRUMS`, `U_ALL`, `mix_units()` and `units_split()`.
- `seq.c`: program-change queues, MIDI note-output tracking, voice-leading memory, note holds, sustain, rolls, live-recording arrays, step-entry queues, panic masks and track/channel routing.
- `arranger_scene.c`: snapshot / restore loops across all tracks.
- `main.c`: track initialization and the `TRK_DEF` default synth table.
- `ui.c` / `ui_input.c` / `ui_layers.c`: selection, record, clear, mute, solo, panic and layer controls.
- `ui_draw.c` / `ui_studio.c` / `ui_vis.c`: meters, live screens, graphics and visualiser arrays.

The source audit must also search for literal `4`, `% 4`, `& 3`, `"/4"`, fixed `[4]` arrays and fixed track-color lists. Not every occurrence means four tracks (some are musical divisions, MIDI note words or knob counts), so each match must be classified rather than blindly replaced.

---

## 3. Project storage: a feasible compact format

### Existing limit

`storage.c` defines a 4 KiB sector, a 256-byte header area and a maximum payload of 3,840 bytes.

The current format-6 project is 3,816 bytes. A fifth full `proj_trk_t` would increase it to approximately 4,750 bytes, which cannot be stored in one existing project copy.

Relevant sources:

- [project.c format definitions](https://github.com/michaelihughes87/afterhours-fm1/blob/46e51ce433e9e73c8d6cac0e8eeebfce519feb2c/firmware/src/project.c#L27-L153)
- [project capture / apply](https://github.com/michaelihughes87/afterhours-fm1/blob/46e51ce433e9e73c8d6cac0e8eeebfce519feb2c/firmware/src/project.c#L460-L530)
- [storage payload limit and map](https://github.com/michaelihughes87/afterhours-fm1/blob/46e51ce433e9e73c8d6cac0e8eeebfce519feb2c/firmware/src/storage.c#L16-L70)
- [storage size validation](https://github.com/michaelihughes87/afterhours-fm1/blob/46e51ce433e9e73c8d6cac0e8eeebfce519feb2c/firmware/src/storage.c#L177-L232)

### Proposed format 7 packing

A compact, fixed-length representation appears able to fit in the existing 3,840-byte payload. The following is an exact size calculation based on the current structures and the proposed bit layout; it must be implemented and validated by host tests before any firmware migration is changed.

**Synth step: pack into 8 bytes (64 bits).**

| Field | Bits |
|---|---:|
| Four MIDI note values | 28 (4 × 7) |
| Note count (0–4) | 3 |
| Step time (NOTE / TIE / REST) | 2 |
| Step flags | 8 |
| Velocity | 7 |
| Per-note levels | 8 (4 × 2) |
| Per-note ratchets | 8 (4 × 2) |
| **Total** | **64** |

The fields exactly fill eight bytes. The current drum step is already a distinct 10-byte structure: 16 lane-on bits, 32 level bits and 32 ratchet bits. Keep drum steps at ten bytes so existing lane semantics are not weakened.

**Parameter locks: pack into 3 bytes each.**

The current lock is four bytes (`step`, `param`, signed 16-bit `value`). The current parameter count is below 128, a step is 0–63 (with `0xFF` meaning free), and engine preset values are already documented as signed 8-bit values. Subject to range tests, a lock can be stored as:

- One byte: step (0–63, or `0xFF` for free).
- One byte: parameter ID (0–126).
- One byte: signed value.

This saves 24 bytes per track (24 locks × 1 byte).

**Track parameter block: 73 bytes.**

- 53 common parameters: 53 signed bytes.
- 8 engine parameters: 8 signed bytes.
- 10 post-format-5 byte parameters: 10 bytes.
- Engine and preset: 2 bytes.

The engine preset structure already stores its eight engine values as signed bytes and documents that every value fits. Still add host tests that assert every common and engine-specific descriptor stays within `[-128, 127]` before using this packed representation.

**Total calculated format-7 size:**

| Component | Calculation | Bytes |
|---|---:|---:|
| Four synth tracks | 4 × (73 metadata + 512 synth steps + 64 nudge/fill + 72 locks) | 2,884 |
| One drum track | 73 metadata + 640 drum steps + 64 nudge/fill + 72 locks | 849 |
| Header, globals, selection, reserved bytes and checksum | Existing 80-byte project header | 80 |
| **Total** | | **3,813** |
| Existing payload limit | | 3,840 |
| **Remaining margin** | | **27** |

This is preferable to immediately allocating more flash sectors or borrowing space from user samples. It preserves the existing A/B storage design and has 27 bytes of payload margin. The format should therefore be fixed and versioned: future additions must be planned rather than appended casually.

### Required implementation safeguards

- Separate the larger in-RAM five-track project representation from the compact on-flash format-7 representation. Do not keep using one `project_t` for both purposes.
- Retain explicit read-only definitions for formats 1–6 and import them into the new runtime representation.
- Add `pack_format7()` / `unpack_format7()` (or equivalent) and reject any out-of-range value before narrowing.
- Preserve the existing checksum, size and magic validation.
- Keep save atomic: the A/B sector scheme must leave the previous complete project recoverable if power is lost.
- Test fully populated patterns, all 24 parameter locks on every track, drum steps, project sections, autosave, erase, interrupted save and older project migration.
- Audit web-editor project backup / restore commands and user preset staging, not just the firmware's `project_save()` path.
- Add compile-time size assertions for the exact serialized byte representation. Do not rely on C struct padding to achieve the calculated size.

---

## 4. Engine arena and RAM constraints

The passing baseline build reported:

| Region | Baseline usage | Limit / reserve |
|---|---:|---:|
| `.data + .bss` | 59,340 bytes | 98,304 bytes |
| `.pool` | 333,900 bytes | 344,064 bytes |
| Pool headroom | 10,164 bytes | At least 8,192 bytes must remain |
| Pool headroom above required reserve | 1,972 bytes | — |

`engines.c` places one `eng_arena_t` per synth part in `.pool`. The arena union contains GRAIN, DRAWBAR, FM6 and PHYS state.

GRAIN alone demonstrates the scale of the problem:

- 12 grain states.
- 12 reverse windows × 128 samples × 2 bytes = 3,072 bytes.
- Seek index: 1,024 × 2-byte predictor plus 1,024 × 1-byte step index = 3,072 bytes.
- Zone tables and other state.

On the 32-bit target, the GRAIN part state is approximately 7,020 bytes. The engine arena is at least this large and may be larger if PHYS is the union's largest member.

**Conclusion:** adding a fourth arena to the existing `.pool` array would breach the required 8 KiB pool reserve. Do not just change `NPART` and hope the build fits.

The baseline `.data + .bss` has approximately 38,964 bytes free. Moving the engine arenas out of `.pool` and into `.bss` is a plausible investigation, but it is not yet approved: the new synth track, larger runtime project slots and all additional arrays also consume RAM.

### Required memory investigation before implementation

1. Add a temporary diagnostic that reports `sizeof(track_t)`, `sizeof(eng_arena_t)`, `sizeof(project_runtime_t)`, `sizeof(gr_part_t)` and `PHYS_ARENA` for the actual target compiler.
2. Generate a linker symbol / section report for the baseline.
3. Calculate the exact increase for four track objects, four engine arenas, four RAM project slots and the working autosave buffer.
4. Prototype the arena placement in `.bss`, then build and confirm pool reserve, BSS ceiling, low RAM, stack, DMA buffers and second-core RAM.
5. Keep the audio and dual-core stress tests green after the move. `eng_arena_of()` / PHYS layout ownership must still resolve the correct part.

References:

- [GRAIN state structures](https://github.com/michaelihughes87/afterhours-fm1/blob/46e51ce433e9e73c8d6cac0e8eeebfce519feb2c/firmware/src/eng_grain.c#L70-L110)
- [PHYS arena sizing](https://github.com/michaelihughes87/afterhours-fm1/blob/46e51ce433e9e73c8d6cac0e8eeebfce519feb2c/firmware/src/eng_phys.c#L75-L110)
- [Build memory checks](https://github.com/michaelihughes87/afterhours-fm1/blob/46e51ce433e9e73c8d6cac0e8eeebfce519feb2c/tools/build.py#L235-L260)

---

## 5. MIDI routing and settings

This is a concrete existing assumption that would break if `NPART` were changed alone.

### The channel-index trap

In `core.h`, the global IDs are ordered:

```text
G_CH1, G_CH2, G_CH3, G_CHOTH
```

`seq.c` currently uses `song.g[G_CH1 + i]` for synth part `i`. With four synth parts, `i == 3` would read `G_CHOTH`, not a fourth synth channel. The same issue exists in `midi_own()`.

Do not insert a new global ID between existing IDs: that would shift the stored numeric IDs used by projects and editor commands.

### Recommended compatibility approach

- Add `G_CH4` at the end of the global parameter enum, after the existing IDs, so no existing global parameter numbers move.
- Replace `G_CH1 + i` with an explicit helper / table for the four synth channels.
- Extend `midi_set` and `MIDI_SET_DEF` with a fourth synth channel (provisionally channel 4).
- The current `MIDI_PART` settings extension is 40 bytes: 32 bytes of MIDI-learn map plus 8 bytes of channel / related settings. Extend it by one byte for CH4; keep 40-byte legacy records readable and assign the default CH4 value when the extra byte is absent.
- Update `midi_part_fill`, `midi_part_read`, `midi_part_default`, settings load/save, `felucca_init`, UI pages and editor backup / restore support.
- Keep the drum channel distinct and configurable.
- Treat CH4 as a hardware-wide MIDI setting, like the existing three synth channels and drum channel, rather than saving it in every song project.

Test four separate synth channels, drum-channel routing, OFF, duplicate channel settings, OTHER = selected track, USB MIDI, TRS MIDI, MIDI clock, program change, CC, pitch bend, MIDI learn and all note-offs.

References:

- [Global parameter IDs](https://github.com/michaelihughes87/afterhours-fm1/blob/46e51ce433e9e73c8d6cac0e8eeebfce519feb2c/firmware/src/core.h#L78-L108)
- [Current synth channel selection](https://github.com/michaelihughes87/afterhours-fm1/blob/46e51ce433e9e73c8d6cac0e8eeebfce519feb2c/firmware/src/seq.c#L75-L110)
- [MIDI input track routing](https://github.com/michaelihughes87/afterhours-fm1/blob/46e51ce433e9e73c8d6cac0e8eeebfce519feb2c/firmware/src/seq.c#L2900-L2940)
- [MIDI persistent settings](https://github.com/michaelihughes87/afterhours-fm1/blob/46e51ce433e9e73c8d6cac0e8eeebfce519feb2c/firmware/src/project.c#L875-L945)
- [Panel MIDI settings](https://github.com/michaelihughes87/afterhours-fm1/blob/46e51ce433e9e73c8d6cac0e8eeebfce519feb2c/firmware/src/panel.c#L80-L95)

---

## 6. UI, colours and web editor

### Five-row mixer

The 240 × 240 display currently draws four 36-pixel track rows starting at y=40; the existing knob footer starts at y=184. Five rows at 36 pixels would collide with the footer.

A compact 28-pixel row gives:

- 5 × 28 = 140 pixels.
- Track rows y=40..179.
- Four pixels of separation before the existing y=184 footer.

That gives a plausible five-strip mixer without removing the knob footer. It requires a deliberate row redesign: smaller track-number tile, compact name / engine label, a compressed 16-step strip and a short level meter. Record, mute and solo status must remain legible. Detailed sends and inserts can remain on secondary pages.

### Fixed four-colour assumptions

`gfx.c` has four track colours in:

- `TE_COL_DEF[4]`, `TE_MID_DEF[4]`, `TE_DIM_DEF[4]`.
- Runtime `TE_COL[4]`, `TE_MID[4]`, `TE_DIM[4]`.
- `theme_t.trk[4]`.
- THM2 theme data, currently 40 bytes.

`ui_draw.c`, `ui_layers.c`, `ui_studio.c`, `ui_vis.c` and `ui_menu.c` use four-colour indexing or masks, including `% 4` / `& 3`.

Proposed direction:

- Extend built-in and user themes to five track colours.
- Add a THM3 theme format; preserve THM1 and THM2 import by retaining their four colours and deriving a controlled fifth colour.
- Keep the screen palette (five screen brightness steps) distinct from the five track colours.
- Update the web editor's theme encode / decode and backup protocol at the same time.
- Use five original AFTERHOURS colours: teal / turquoise, vermilion / orange, amber, emerald and a fifth contrasting hue chosen for legibility.
- Use reduced-motion / high-contrast alternatives; visuals must not consume audio-ISR time.

### Web editor

The editor is a large single-file application, `web/editor.html`. The baseline has explicit four-track assumptions:

- `const NTRK = 4, TRK_DRUM = 3`.
- Fixed four track colours `--t1` through `--t4` and a `TCOL` list.
- `% 4` track accent selection in the mixer and live views.
- Fixed four-track assumptions in the theme panel and track-target selectors.
- Mixer / performance controls assume the drum track is the final track.

The firmware editor protocol document explicitly describes v3 as four tracks and uses track IDs 0–3 with the drum track last. The five-track firmware needs a coordinated protocol update and editor update.

Recommended approach:

- Keep internal DSP indices as four synths plus drum.
- Use visible track order `[drum, synth0, synth1, synth2, synth3]` in the new editor.
- Centralize conversion at the firmware editor boundary; never leak internal array indices into user-facing track IDs.
- Add a protocol version that explicitly reports five tracks and defines visible IDs / track roles. Keep legacy parsing safe; do not silently let an old four-track editor interpret a five-track reply incorrectly.
- Test INFO, TRACK, TRACK_MIX, TRACK_DUMP, TRACK_STEP, TRACK_PARAM, TRACK_CHANGED, project backup / restore, drum commands, lock / micro / fill commands, FM6 patch commands, live sync and theme operations.
- Update the editor's theme format and palette simultaneously.

References:

- [UI studio mixer](https://github.com/michaelihughes87/afterhours-fm1/blob/46e51ce433e9e73c8d6cac0e8eeebfce519feb2c/firmware/src/ui_studio.c#L230-L320)
- [Theme and colour structures](https://github.com/michaelihughes87/afterhours-fm1/blob/46e51ce433e9e73c8d6cac0e8eeebfce519feb2c/firmware/src/gfx.c#L20-L115)
- [Web editor track constants](https://github.com/michaelihughes87/afterhours-fm1/blob/46e51ce433e9e73c8d6cac0e8eeebfce519feb2c/web/editor.html#L3140-L3150)
- [Web editor theme record](https://github.com/michaelihughes87/afterhours-fm1/blob/46e51ce433e9e73c8d6cac0e8eeebfce519feb2c/web/editor.html#L4400-L4495)
- [Editor protocol: four-track model](https://github.com/michaelihughes87/afterhours-fm1/blob/46e51ce433e9e73c8d6cac0e8eeebfce519feb2c/web/EDITOR_PROTOCOL.md#L1-L22)

---

## 7. Build and test strategy

Before changing `NPART` / `NTRK`:

1. Keep `main` and commit `46e51ce` as the known-good baseline.
2. Add target-compiler diagnostics for structure sizes and the linker memory map.
3. Add host tests for visible/internal track mapping, including old project migration of selected drum track index 3 to internal index 4.
4. Implement and test the packed format-7 serializer independently of the live track-array change.
5. Add tests for all track parameter and lock value ranges before using signed-byte storage.
6. Add MIDI CH4 settings migration tests for both old 40-byte and new 41-byte settings records.
7. Add UI / editor protocol tests for five visible tracks and five theme colours.
8. Only then change the live track architecture and integrate the new project format.

Keep the current host CPU baseline separate from compiler-derived target-cost references. The target-cost test is a static compiler-output check, not a hardware performance measurement. After each structural step, run the existing golden audio, voice allocation, dual-core race, project, storage, MIDI, editor fuzz and web tests.

### Required five-track release gates

- Four synth parts plus one drum-machine part initialise and select in the correct visible order.
- Each synth can load every available engine and preset.
- T5's texture / percussion presets work, but T5 can load ordinary bass, pad, lead, sample and other supported synth sounds.
- Drum sequencing and 16 lanes remain separate from synth sequencing.
- Every track has independent patterns, level, pan, mute, solo, recording and supported processing.
- Four synth MIDI channels and one drum channel work over USB and TRS.
- Format 1–6 projects migrate without losing patterns, locks, drum data, sections or sounds.
- Format 7 worst-case project saves fit the existing payload, with checksum and A/B recovery.
- Worst-case CPU, pool, BSS, low RAM, stack and dual-core tests pass.
- The web editor, protocol and five-colour themes agree with the firmware.
- The actual pink FM-1 is backed up and tested only after the new package and recovery process are verified.

---

## 8. Immediate next engineering task

Do **not** start by changing `#define NPART 3` to `4`.

The next coding change should be a diagnostic-only commit that:

1. Reports target sizes for `track_t`, `eng_arena_t`, `gr_part_t`, `PHYS_ARENA` and the project runtime representation.
2. Adds an exact target linker map / symbol report to the CI artifact or build log.
3. Adds host-side format-7 pack / unpack tests and descriptor-range tests without changing the live track count.
4. Adds tests for the explicit visible/internal mapping.

Once those measurements and host tests exist, the first architectural implementation can be planned against real sizes rather than guesses.

## 9. Critical NOINIT cache constraint (follow-up finding)

The target linker script defines a separate `NOINIT` RAM region:

- Origin: `0x01C7C000`.
- Length: `0x3D50` = 15,696 bytes.
- The four cached project objects are `proj_slot[4]`, explicitly placed in `.noinit`.
- The existing format-6 project object is 3,816 bytes, so `proj_slot[4]` occupies 15,264 bytes by itself.
- `panel` in `.noinit` is 32 bytes; `settings` in `.noinit` are 16 bytes. Those three objects account for at least 15,312 bytes, leaving at most 384 bytes for any other `.noinit` objects and alignment.

A naïve five-track runtime project object would be 4,750 bytes (80-byte header plus five 934-byte tracks). Four such cached runtime objects would be 19,000 bytes: 3,304 bytes larger than the entire NOINIT region, before panel/settings or any other NOINIT state. **Therefore a five-track `project_t proj_slot[4]` cannot remain as four expanded runtime objects in NOINIT.**

The compact format-7 calculation in this audit (3,813 bytes per serialized project) remains a promising *on-flash and NOINIT-cache* candidate, but it is only a design calculation. It has not been implemented or range-tested. If used, the likely design is to keep the four section caches in compact, versioned records and unpack one project into a single runtime staging buffer when loading / applying / saving. That staging buffer's placement and lifetime must be measured against `.bss`, `.pool`, stack and autosave use. Do not merely change `NTRK` and expand `proj_slot`.

The baseline build summary did not report NOINIT usage. The diagnostic build update now adds `_noinit_start` / `_noinit_end` linker symbols, checks the exact NOINIT occupancy against the region capacity, saves the application symbol table and section table, and reports byte sizes for the track array, engine arenas, project slots, autosave buffer, import staging union, shared scratch and INSERT state when the linker symbol table exposes them.

The new diagnostic artifacts are `build/felucca.sym` and `build/felucca.sections.txt`. They are for engineering inspection only; they do not change the firmware's audio or track behaviour.
