# AFTERHOURS — Prototype Sound Bank

**Status:** Prototype register, not a completed or approved factory bank.
**Creative source:** `AFTERHOURS-docs/SOUND_DESIGN.md`.
**Technical source:** `AFTERHOURS-docs/ENGINE_FEASIBILITY.md`.
**Planning baseline:** `afterhours-five-track` commit `a0b4bec`; firmware is still the original three-synth-plus-drum baseline.

---

## 1. Priorities and method

The visible instrument order and sound-development priorities are:

1. **T1 DRUMS** — the strongest possible dedicated drum-machine experience.
2. **T2 AFTER POLY** — Prophet warmth + Juno movement.
3. **T3 ORGAN / KEYS** — soulful organs and warm Rhodes / Wurlitzer-style keys.
4. **T4 MONO BASS** — Minimoog weight + Pro-One articulation.
5. **T5 TEXTURE / PERC** — granular / digital / atmospheric sounds and a small selection of useful tuned / synthetic percussion.

The first audition set contains **20 concepts**, distributed across the five roles. This is a comparison programme, not a requirement to create 20 new presets. Start with existing factory material; keep, refine, combine or reject each candidate after listening. The longer-term target is around **40 genuinely distinctive factory sound / kit programs**, not 150 generic variations.

All four synth tracks remain fully flexible. The role names guide the default library only; they do not restrict engine selection.

No sound should be described as approved until it has been auditioned on FM-1 hardware, level checked, tested musically and verified for save / recall and resource use.

## 2. T1 — DRUMS: five kit prototypes

| ID | Working name | Sound brief | First route | Evaluation |
|---|---|---|---|---|
| D01 | **Basement Machine** | Dry, weighty kick, firm snare, close hats and restrained room; dependable everyday kit | Existing DEEP / TIGHT kits and current drum synth | Kick weight, snare body, transient balance, hat harshness |
| D02 | **Heavy Weather** | Deep sub kick, full toms, aggressive but controlled snare and low percussion | Existing kit models; tune / decay / tone / drive | Low-end stability, punch without clipping |
| D03 | **Room Service** | Organic, acoustic-style kit with useful room and breakbeat character | ACOUSTIC kit and properly licensed / original samples | Natural dynamics, sample provenance, useful swing |
| D04 | **Wire & Glass** | Metallic hits, resonant pings, industrial impacts and synthetic accents | SYN kits, drum FM / bell / metallic models | Pitched and controlled, not broadband noise |
| D05 | **Dusty Break** | Dry, worn sampled / break-oriented kit for trip-hop, dub and broken beats | DUST / sample kits, original or redistributable breaks | Transient consistency, groove, low-mid clarity |

## 3. T2 — AFTER POLY: five polyphonic prototypes

| ID | Working name | Sound brief | First route | Evaluation |
|---|---|---|---|---|
| A01 | **Soft Prophet** | Full, rounded two-oscillator poly voice with gentle detune and warm filter movement | ANALOG baseline | Chord weight, tuning, filter character, voice sharing |
| A02 | **Blue Velvet** | Juno-inspired pad with soft pulse-width movement and restrained chorus | ANALOG + existing chorus | Movement without seasick modulation or thin strings |
| A03 | **Slow Brass** | Warm, swelling poly tone with a rounded attack and no tacky synthetic horn edge | ANALOG / TRIO comparison | Smooth attack, warmth, useful chord range |
| A04 | **Night Choir** | Dark, layered sustained poly texture with subtle beating and slow evolution | ANALOG / FM6 / GRAIN comparison | Must remain soft and organic, not artificial choir |
| A05 | **Wide Awake** | Expressive unison / lead-poly hybrid with controlled spread and useful articulation | ANALOG; assess P600 only as a separate experiment | Lead clarity, unison level, CPU under shared voice budget |

Guru-600's Prophet-600 engine remains a separate optional experiment. Do not make it a dependency for these first AFTER POLY prototypes.

## 4. T3 — ORGAN / KEYS: three keyboard prototypes

| ID | Working name | Sound brief | First route | Evaluation |
|---|---|---|---|---|
| K01 | **Soul Wheels** | Warm tonewheel organ for soulful chords and sustained harmony | DRAWBAR SOUL ORGAN / JAZZ ORGAN | Smooth registration, body, upper-partial harshness |
| K02 | **Dub Organ** | Rounded organ stabs with useful decay and space for delay / spring-like effects | DRAWBAR / WHEEL REGGAE / HOUSE registrations | Short-note definition, space in the mix |
| K03 | **Afterglow EP** | Warm Rhodes-like electric piano with a tine attack and rounded body | DIGITAL RHODES vs FM6 TINE EP; WURLI as contrast | Attack / decay, chord warmth, velocity response |

Some Wurlitzer bite, clav and organ variants can join the supporting library if they are genuinely useful. A large bank of generic electric pianos is not the objective.

## 5. T4 — MONO BASS: four bass prototypes

| ID | Working name | Sound brief | First route | Evaluation |
|---|---|---|---|---|
| B01 | **Night Weight** | Deep, rounded bass with a stable fundamental and restrained upper harmonics | ANALOG SUB BASS | Low-note consistency, mono weight, headroom |
| B02 | **Pulse Runner** | Tight Pro-One / SH-101-inspired pulse or saw bass with glide and decisive articulation | ANALOG FUNK / MONO BASS | Note attack, slide and rhythmic clarity |
| B03 | **Soft Dirt** | Warm bass that moves from clean to driven and resonant through accessible controls | ANALOG drive / filter / insert | Preserve the fundamental; avoid uncontrolled fuzz |
| B04 | **Chrome Sub** | Digital / FM bass with strong low end and a restrained metallic edge | FM6 ROUND BASS or DIGITAL | Tuning range, note consistency, CPU |

## 6. T5 — TEXTURE / PERC: three supporting prototypes

| ID | Working name | Sound brief | First route | Evaluation |
|---|---|---|---|---|
| X01 | **Tape Bloom** | Soft, slowly evolving sample / grain atmosphere with gentle pitch wear | SAMPLE / GRAIN | Stable level, no clicks, no muddy low end |
| X02 | **Slow Signal** | Dark digital pad or drone with gradual timbral movement | PHASE / GRAIN / FM6 | Movement should be audible but not distracting |
| P01 | **Resonant Relay** | Musical pitch-swept percussion / tuned tom with a defined note centre | PHYS MEMB / existing drum pitch model translated as a synth concept | Attack, useful pitch range, decay and CPU |

Keep a small supporting selection of glass / bell / xylophone / metallic FM sounds in the finished library. They are welcome colours, not the main sound-development priority.

## 7. Additional existing sounds to audition

These are comparisons, not an instruction to add more presets:

| Sound | Existing source | Purpose |
|---|---|---|
| RHODES / DX RHODES / WURLI | DIGITAL | Compare warm and bright electric-key characters |
| SOUL ORGAN / JAZZ ORGAN / GOSPEL | DRAWBAR / WHEEL | Find the best core organ registrations |
| TINE EP | FM6 | Compare FM tine character against DIGITAL RHODES |
| WARM PAD / ATMOS PAD / SINE PAD | ANALOG | Find starting points for AFTER POLY |
| SUB BASS / FUNK BASS / REESE | ANALOG | Find clean weight, articulation and controlled aggression |
| FAT BASS / DUB CHORD | TRIO | Compare oscillator stack and sync / chord character |
| VIBRA BAR / MODAL BAR / BIG BELL | PHYS | Supporting tuned-percussion colours |
| GLASS BELL / WOOD BARS | FM6 | Supporting metallic / mallet colours |
| DEEP / TIGHT / ACOUSTIC / DUST | DRUMS | Core drum-kit audition set |
| SYN1–SYN4 | DRUMS | Compare synthesised kick, snare, hat, tom and metallic models |

## 8. Audition protocol

For each candidate:

1. Play single notes at low, middle and high registers.
2. Play a short, relevant musical phrase: a bass line, chord progression, organ stab or rhythmic pattern.
3. Test soft / medium / hard velocity where supported.
4. Sweep the most important tone, filter, envelope, modulation, drive and effect controls.
5. Check that the useful range is musical and that the sound does not become harsh, muddy or excessively loud.
6. Play it with a representative kick, snare, bass and pad.
7. Save, change away, reload and confirm the sound returns consistently.
8. Record a short dry and effected example; note the engine, preset and settings.

Score each candidate from 1–5 for character, musical usefulness, warmth / body, control / playability, mix fit and distinctiveness. Mark it **keep**, **refine**, **combine** or **reject**.

## 9. Quality gate

A prototype progresses only if it:
- Has a distinct audible identity and clear musical role.
- Is not a superficial variation of another sound.
- Sounds good at its default level and has no unexpected clipping.
- Has a useful range and predictable controls.
- Avoids shrill transients, thin fake strings / horns, uncontrolled noise and muddy tails.
- Fits the FM-1's voice, CPU and memory limits.
- Uses original or properly redistributable samples / patch material.
- Saves and recalls consistently.

## 10. First decision after audition

Produce:
- The strongest five drum kits and a short list of kit refinements.
- The preferred ANALOG poly starting point and whether P600 fills a real gap.
- The best DRAWBAR organ registrations and electric-key choice.
- The strongest mono bass starting points and their control ranges.
- Two or three useful texture / percussion sounds.
- A keep / refine / combine / reject decision for every prototype.

The goal is a coherent, exceptional-sounding instrument—not a full preset list for its own sake.
