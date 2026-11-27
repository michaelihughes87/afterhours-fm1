# AFTERHOURS — Engine Feasibility Assessment

**Assessment baseline:** `afterhours-five-track` commit `46d8cd6a00cf3c3830593b3b95bb4d7dc68083de`.
**Purpose:** Map the updated sonic brief to the actual SLOOP-derived FM-1 firmware.
**Decision status:** Research and design assessment only. No DSP, project format, track architecture or hardware changes are authorised by this document.

---

## 1. Executive findings

The current firmware already contains a broad set of synthesis engines and sound resources. Several of the user's newly emphasised sounds are already present in the factory material:

- DIGITAL has presets including RHODES, DX RHODES, WURLI, CLAV, MARIMBA, GLOCKEN, XYLOPHONE, CELESTA, KALIMBA and related keyboard / mallet sounds.
- DRAWBAR provides a nine-partial tonewheel-style organ with registrations, percussion, click, drive and a rotary-speaker approximation.
- FM6 already has TINE EP, GLASS BELL, WOOD BARS, ROUND BASS and other useful starting points.
- PHYS has modal, string, membrane and sympathetic-string models, with existing bell, bar, mallet, tom, chime and tuned-object presets.
- The dedicated drum machine already combines sampled kits with synthesised drum models.

The first sound-design work should therefore be **audition, curation, level balancing and refinement of existing engines and presets**, not adding engines indiscriminately.

The agreed visible track / sound priority is:
1. T1 DRUMS — best kits, weight, punch, breaks and hybrid analogue / sampled / synthetic character.
2. T2 AFTER POLY — Prophet warmth + Juno movement.
3. T3 ORGAN / KEYS — soulful organ and warm electric keys.
4. T4 MONO BASS — Minimoog weight + Pro-One articulation.
5. T5 TEXTURE / PERC — granular / digital / atmospheric sounds and a small, useful percussion selection.

All four synth parts remain unrestricted. This order guides the default sound library and the audition programme; it does not restrict engine selection. Bells and mallets should be represented, but they are supporting sounds rather than a major development stream.

The most important candidate for new engine work is Guru-600's Prophet-600 engine. It is technically interesting and potentially complementary, but it is not a drop-in addition and is not the same instrument architecture as a Prophet-5. It needs a controlled porting and benchmarking investigation before inclusion.

The principal implementation risks remain:
- Shared CPU / eight-voice synth budget under simultaneous load.
- Per-part engine state and memory.
- The crowded current project / preset storage model.
- Preset parameter representation and compatibility.
- Flash map and patch-bank ownership if an engine brings its own persistent bank.

## 2. Current engine inventory

The table describes the actual engine families in the current source tree. “Preset-first” means the existing synthesis model appears capable of reaching useful parts of the sonic target without changing its DSP implementation. It does not imply that a convincing preset already exists for every reference.

| Engine | Existing capability | Best AFTERHOURS opportunities | Feasibility / cautions |
|---|---|---|---|
| ANALOG | Two band-limited oscillators; saw, square, triangle, sine and PWM; detuning, mix, noise, drive; resonant state-variable LP / BP / HP filter | Minimoog-like bass approximations, warm poly, Pro-One / SH-101-like sequences, restrained brass-like tones, dark pads | Strong preset-first foundation. Not a three-oscillator Minimoog or a literal Prophet / Juno circuit. Filter is an SVF, not a four-pole P600 ladder. |
| DIGITAL | Algorithmic digital / FM-style voice with factory keyboard and mallet presets | Rhodes / DX Rhodes / Wurlitzer-like keys, glockenspiel, xylophone, marimba, bells, digital plucks and FM bass | Very strong existing match for the user's Rhodes / mallet preference. First audition and refine current sounds before engine work. |
| PHASE | Phase-distortion waveforms, alternate waveform line, detuning, mix / ring, sub and envelope modulation | CZ-style keys, glassy plucks, resonant tones, unusual brass-like textures and digital movement | Existing synthesis can create interesting digital timbres. Not a PPG wavetable engine. |
| TRIO | Three oscillators, ring modulation, hard sync and a 12 dB/oct multimode filter | Pro-One-like sync bass, aggressive stabs, metallic / industrial tones, experimental poly stabs | Useful but can become harsh or dense. Use restrained levels and carefully selected wave / filter settings. |
| DRAWBAR | Nine sine partials in tonewheel footages, drawbar registrations, percussion, click, per-voice drive and economical rotary effect | Warm organ, B3-like registrations, soulful chords, subdued organ stabs and percussive organ | Strong direct match for organ. Its nine partials are an additive tonewheel model, not a Rhodes / electric piano. |
| FM6 | Six-operator FM, 32 algorithms, operator envelopes, feedback, ratios / fixed frequencies and patch macros | Tine EP, glass bells, wood bars, metallic percussion, FM bass and complex digital timbres | Strong for electric-piano and metallic families. Engine polyphony is capped at six per part; the device still shares its overall eight synth voices. |
| PHYS | Modal resonators, plucked strings, membranes and sympathetic strings | Rounded mallets, tuned bars, glock / vibraphone-like tones, bells, wood / metal objects and synthetic toms | Excellent percussion resource. Usually limited to three voices per part, or two for SYMP. Some models can be CPU-intensive. Avoid overly bright strikes and excessively long ringing tails. |
| SAMPLE | Multizone IMA ADPCM sample playback, looping and pitch tracking; four user sample slots | Rhodes / Wurli layers if properly licensed, organic drum hits, acoustic mallets, field recordings and found sounds | Great for authenticity where recording material is available. Sample provenance, flash capacity, zones and pitch range must be controlled. |
| GRAIN | Granular playback over existing sample material; grain density, position, spread, random detune / reverse, size and tone | Tape-worn pads, evolving drones, frozen keys, atmospheric beds and degraded textures | Strong for soundscapes. Current design has 12 grains per part and a three-voice cap. It uses substantial per-part state and needs careful worst-case CPU testing. |
| LOFI | Chip / stepped waveforms, wave RAM, sample-and-hold and pitch sweep | Digital grime, restrained aliasing, broken-circuit accents and deliberately degraded tones | Good as a contrasting colour. Not a substitute for analogue warmth. Use it selectively; avoid defaulting to harsh bit-crushed sounds. |
| NOISE | Analogue-style noise, dust / impulses, LFSR and metallic shift-register modes, with resonant filtering | Controlled hiss, crackle, filtered air, rhythmic bursts, tuned metallic noise and atmospheric layers | Capable but easy to make messy. Every noise preset must have a clear envelope, filtering / resonance, useful level and musical role. |
| FORMANT / VOICE | Formant-based vowel / vocal-like synthesis, with a four-voice limit | Soft ghostly vowel layers, breathy atmosphere, distant vocal-like textures and selected effects | Secondary colour only. Avoid sharp synthetic horns / strings or obvious novelty choir presets. |
| Dedicated DRUMS | 16 lanes; sampled kits and synthesised per-hit tone, FM / bell, noise, click, pitch envelope, filter, drive and crush | Analogue-style kicks, synthetic toms, layered snares, claps, metallic hats, pitch-swept hits and hybrid kits | Strong existing foundation for the Machinedrum / Vermona / Jomox / Syncussion territory. Kit curation and level balance are more urgent than a new drum engine. |

### Source references

- [Engine table](https://github.com/michaelihughes87/afterhours-fm1/blob/46d8cd6a00cf3c3830593b3b95bb4d7dc68083de/firmware/src/engines.c)
- [ANALOG](https://github.com/michaelihughes87/afterhours-fm1/blob/46d8cd6a00cf3c3830593b3b95bb4d7dc68083de/firmware/src/eng_analog.c)
- [DIGITAL](https://github.com/michaelihughes87/afterhours-fm1/blob/46d8cd6a00cf3c3830593b3b95bb4d7dc68083de/firmware/src/eng_digital.c)
- [PHASE](https://github.com/michaelihughes87/afterhours-fm1/blob/46d8cd6a00cf3c3830593b3b95bb4d7dc68083de/firmware/src/eng_phase.c)
- [TRIO](https://github.com/michaelihughes87/afterhours-fm1/blob/46d8cd6a00cf3c3830593b3b95bb4d7dc68083de/firmware/src/eng_trio.c)
- [DRAWBAR](https://github.com/michaelihughes87/afterhours-fm1/blob/46d8cd6a00cf3c3830593b3b95bb4d7dc68083de/firmware/src/eng_drawbar.c)
- [FM6](https://github.com/michaelihughes87/afterhours-fm1/blob/46d8cd6a00cf3c3830593b3b95bb4d7dc68083de/firmware/src/eng_fm6.c)
- [PHYS](https://github.com/michaelihughes87/afterhours-fm1/blob/46d8cd6a00cf3c3830593b3b95bb4d7dc68083de/firmware/src/eng_phys.c)
- [SAMPLE](https://github.com/michaelihughes87/afterhours-fm1/blob/46d8cd6a00cf3c3830593b3b95bb4d7dc68083de/firmware/src/eng_sample.c)
- [GRAIN](https://github.com/michaelihughes87/afterhours-fm1/blob/46d8cd6a00cf3c3830593b3b95bb4d7dc68083de/firmware/src/eng_grain.c)
- [NOISE](https://github.com/michaelihughes87/afterhours-fm1/blob/46d8cd6a00cf3c3830593b3b95bb4d7dc68083de/firmware/src/eng_noise.c)
- [Drum synthesis](https://github.com/michaelihughes87/afterhours-fm1/blob/46d8cd6a00cf3c3830593b3b95bb4d7dc68083de/firmware/src/drum_synth.c)
- [Drum track](https://github.com/michaelihughes87/afterhours-fm1/blob/46d8cd6a00cf3c3830593b3b95bb4d7dc68083de/firmware/src/drums.c)

## 3. Key sound targets mapped to existing engines

| Sound target | First engine / approach | Secondary option | New DSP needed? |
|---|---|---|---|
| Warm Rhodes-like keys | DIGITAL RHODES preset; audition and refine | FM6 TINE EP; SAMPLE only if a properly licensed recording is useful | Not initially |
| Wurlitzer-like keys | DIGITAL WURLI preset | DIGITAL / FM6 editing, sample layer if justified | Not initially |
| Clavinet / plucked keys | DIGITAL CLAV | PHASE or ANALOG pluck | Not initially |
| Warm tonewheel organ | DRAWBAR registrations and gentle percussion / drive | Existing sampled organ material if available and licensed | Not initially |
| Glockenspiel / xylophone | DIGITAL GLOCKEN / XYLOPHONE | PHYS modal / bar models; FM6 GLASS BELL / WOOD BARS | Not initially |
| Rounded vibraphone / mallet | PHYS modal model with soft strike / damping | DIGITAL / FM6 | Not initially |
| Minimoog-like bass | ANALOG with two oscillators, restrained detune and filter movement | TRIO for more aggressive stacked / sync sounds | Approximation only |
| Pro-One / SH-101 bass | ANALOG or TRIO, short envelopes, glide and sync where appropriate | PHASE | Not initially |
| Dirty MS-20-like bass | ANALOG drive / resonance or TRIO multimode filter | Per-track distortion / FUZZ / FOLD | Approximation only |
| Prophet / Juno-like poly | ANALOG for oscillator-based tones; chorus send for movement | P600 candidate; DIGITAL for complementary digital layer | P600 optional |
| Dark strings / soft pads | ANALOG with slow envelopes and subtle chorus | SAMPLE / GRAIN / PHASE | Not initially |
| FM metallic percussion | FM6 or PHYS | DIGITAL / TRIO | Not initially |
| Syncussion / Simmons tom | Dedicated synth drum pitch envelope; PHYS MEMB for pitched membrane notes | ANALOG short-envelope resonant hit | Existing drum synth may suffice |
| Industrial transient | Drum synth noise / filter / pitch / drive | NOISE or SAMPLE | Not initially |
| Tape-worn ambience | SAMPLE / GRAIN with controlled source and modulation | Master texture / DUST features | True tape effect would be new work |
| Evolving digital texture | GRAIN / PHASE / FM6 | SAMPLE and NOISE | True wavetable scan would be new work |
| EMS-like feedback / patch matrix | Existing routing, delay and modulation approximations | Experimental future modulation architecture | Full matrix is new work |

## 4. Guru-600 / Prophet-600 investigation

### Why it is interesting

Guru-600 is a Prophet-600 emulator firmware for the FM-1, based on Felucca. Its P600 engine source describes:
- Two oscillators per voice, each combining saw / triangle / pulse.
- Oscillator A hard sync to oscillator B.
- A four-pole (24 dB/oct) resonant low-pass ladder filter.
- A dedicated filter ADSR.
- Prophet-style Poly-Mod from the filter envelope and oscillator B.
- Keyboard tracking, unison and LFO behaviour.
- Additional Guru-600 options including high-pass, sub, noise and a second LFO.

This provides a more specifically vintage-polyphonic voice architecture than the existing ANALOG engine's two-oscillator state-variable-filter design.

### Important distinction

The main AFTER POLY creative reference is Prophet-5 warmth blended with Juno movement. Guru-600 emulates a Prophet-600, a different Prophet model. The P600 engine offers useful related synthesis ideas, but it should not automatically define the entire AFTER POLY voice.

### Porting complexity

The P600 source is not a drop-in file:
- Guru-600 is based on its own Felucca source revision and uses its own engine-memory interface (`ENG_MEM`, `ENG_MEM_FITS`) and track / engine wiring.
- AFTERHOURS' current SLOOP-derived source uses a different engine-arena access pattern (`eng_arena_of`).
- The P600 engine maps much of its additional parameter set into parameter positions historically associated with another engine. AFTERHOURS must review parameter ownership and avoid collisions with existing stored values and editor controls.
- The engine requires its source tables, factory program data, SysEx / patch handling and any dedicated user patch storage that is selected for the port.
- The P600 engine must be appended to the engine table; existing engine indices are stored in projects, user presets and editor messages and must not be reordered.
- Project and preset save / recall must be designed before deciding how a P600-specific patch is referenced or embedded.

### CPU and memory

The P600 engine uses a four-stage ladder calculation per sample and additional oscillator / Poly-Mod work. Its target CPU cost has not been measured in this AFTERHOURS branch. It must be compiled with the pinned JieLi toolchain and tested at realistic simultaneous voice / track loads.

Its per-part auxiliary state in Guru-600 is comparatively small (per-voice high-pass / sub state plus a part LFO), so the main uncertainty is not automatically a large new arena. A target size / linker check and integration build are still required; do not assume zero RAM or flash cost.

### Licensing and sound-bank provenance

Guru-600's repository declares GPL-3.0, matching the AFTERHOURS project's GPL-3.0 licence. A code port must retain applicable copyright / licence notices and identify modifications. This is a preliminary compatibility observation, not a substitute for checking all files and notices during an actual port.

The sound data must be evaluated separately from the engine code. Do not import a complete preset / patch collection merely because it is present in the repository. Record the source and redistribution permissions of each bank and sound. Factory program names, community patches, adapted third-party sounds and original Guru-600 sounds may have different provenance and obligations.

References:
- [Guru-600 repository and README](https://github.com/MarcGoudy/guru-600)
- [Guru-600 P600 engine](https://github.com/MarcGoudy/guru-600/blob/main/firmware/firmware/src/eng_p600.c)
- [Guru-600 licensing notes](https://github.com/MarcGoudy/guru-600/blob/main/docs/firmware/LICENSING.md)
- [AFTERHOURS GPL-3.0 licence](https://github.com/michaelihughes87/afterhours-fm1/blob/46d8cd6a00cf3c3830593b3b95bb4d7dc68083de/LICENSE)

### Recommendation

**Investigate, prototype and benchmark the P600 engine as an optional additional engine. Do not make it a dependency for the first AFTERHOURS sound release.**

The first comparison should be:
1. Existing ANALOG preset designed for warm two-oscillator poly.
2. Existing DIGITAL / PHASE options for alternative poly colours.
3. P600 port prototype, if the integration and target performance are acceptable.

Keep the main sound target “Prophet warmth + Juno movement” regardless of which engine wins. The instrument's sound identity matters more than the name of the oscillator model.

## 5. Effects, EQ and sound manipulation

The current code already contains:
- Per-track effect sends for distortion, chorus, delay and reverb.
- Shared chorus, tempo-related delay and reverb buses.
- A track INSERT with soft / hard clipping, folding, fuzz, bit reduction, phaser, flanger and chorus types.
- Track filtering and a master DJ-style filter.
- Master DUST / degradation and a configurable texture bed with sources such as vinyl, tape, rain, wind, radio, room and user slots.

This is a useful effects foundation. However:
- A texture-bed source called TAPE is not the same as a dedicated tape-delay emulation.
- The existing distortion / tone controls are not a full multiband or parametric EQ.
- Track LFO routing is useful but is not a fully unrestricted modular patch matrix.
- Dedicated pitch-shifting / harmonising and detailed Eventide-style processing are not established capabilities in the current effect list.

### EQ recommendation

Treat EQ as a high-value sound-manipulation design requirement, not a guaranteed feature. First evaluate what can be achieved through existing filter, tone and effect controls. If a dedicated EQ is still needed, prototype the smallest useful musical version (for example a low / high shelf or simple two-band tone control) and measure CPU, memory, interaction and bypass behaviour before adding it.

## 6. Resource and benchmark interpretation

Known architecture constraints:
- Synth parts share a global budget of eight sounding voices initially.
- PHYS is typically capped at three voices per part, or two for SYMP.
- GRAIN has a three-voice cap and twelve grains per part.
- FM6 has a six-voice engine cap.
- The engine state arena is allocated per synth part, so a new engine must fit the existing arena or trigger a deliberate memory change.
- Drum playback voices are separate from the synth voice budget.

Benchmark sources must be interpreted correctly:
- `tests/cpu_baseline.txt` is a host-side instruction / timing regression reference, not an FM-1 hardware cycle measurement.
- `tests/target_budget.txt` is a compiler-derived static loop-cost check from the target disassembly. It is useful for comparing build output but is not itself a real-time hardware measurement.
- The successful baseline build and its memory report are the starting reference. New engine work requires a fresh target build, audio regression, voice / routing tests and worst-case simultaneous-load tests.

Relevant files:
- [Host CPU baseline](https://github.com/michaelihughes87/afterhours-fm1/blob/46d8cd6a00cf3c3830593b3b95bb4d7dc68083de/tests/cpu_baseline.txt)
- [Target static-cost references](https://github.com/michaelihughes87/afterhours-fm1/blob/46d8cd6a00cf3c3830593b3b95bb4d7dc68083de/tests/target_budget.txt)
- [Core voice / track definitions](https://github.com/michaelihughes87/afterhours-fm1/blob/46d8cd6a00cf3c3830593b3b95bb4d7dc68083de/firmware/src/core.h)
- [Effects](https://github.com/michaelihughes87/afterhours-fm1/blob/46d8cd6a00cf3c3830593b3b95bb4d7dc68083de/firmware/src/fx.c)

## 7. Preset-first versus engine-development decisions

### Preset-first: do before new DSP

- Audition the existing DIGITAL RHODES, DX RHODES and WURLI sounds.
- Audition the existing DIGITAL GLOCKEN, XYLOPHONE, MARIMBA, CELESTA and related mallet sounds.
- Build and compare DRAWBAR organ registrations.
- Explore FM6 TINE EP, GLASS BELL and WOOD BARS.
- Explore PHYS modal bars, bells, membrane and sympathetic models with rounded attacks and controlled decay.
- Develop ANALOG presets for Minimoog-weight bass, Pro-One-like articulation, warm poly and Juno-style movement using the existing controls and sends.
- Create drum-kit variants using the existing synthesised drum model and sample kits.
- Test GRAIN / SAMPLE / NOISE textures at deliberately low levels and with controlled filtering / envelopes.

### Potential engine changes: investigate after audition

- P600 engine port from Guru-600.
- A more expressive or musical modulation layer if current routes prove insufficient.
- A dedicated EQ / tone-shaping control only if existing filtering and inserts cannot meet the brief.
- A true wavetable engine only if preset experiments show a clear sound gap that PHASE / FM6 / SAMPLE / GRAIN cannot fill.

### Not first-release priorities

- Full EMS-style pin-matrix patching.
- Faithful circuit-by-circuit emulation of every named vintage synth.
- Dedicated Eventide-class pitch / spatial processing.
- Extensive chord / progression generation.
- Expanding polyphony beyond the shared eight-voice budget without measured evidence.

## 8. Recommended evaluation order

1. **Audition existing material:** DIGITAL keys / mallets, DRAWBAR organ, FM6 EP / bells, PHYS bars / bells, ANALOG bass / poly, current drum kits.
2. **Build the first 15–20 prototypes:** four sound concepts for each visible instrument role, with no new DSP.
3. **Identify real gaps:** describe what the prototype cannot do, not simply which famous instrument has an interesting feature.
4. **P600 spike:** port in isolation only if the sound gap justifies it; compile and benchmark before integration.
5. **Complete the 40-sound curation:** expand from prototypes only when new sounds are clearly distinct and musically useful.
6. **Finalise preset / project storage:** once required engine parameters and patch-bank needs are known.
7. **Resume five-track implementation:** maintain existing architecture decisions and regression / resource gates.

**Decision rule:** choose the smallest technical change that produces an audible, meaningful improvement to the instrument. If an existing engine can produce the sound convincingly, use it.
