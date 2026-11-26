# AFTERHOURS — Prototype Sound Bank

**Status:** Prototype register, not a completed or approved factory bank.
**Creative source:** `AFTERHOURS-docs/SOUND_DESIGN.md`.
**Technical source:** `AFTERHOURS-docs/ENGINE_FEASIBILITY.md`.
**Baseline:** `afterhours-five-track` commit `46d8cd6a00cf3c3830593b3b95bb4d7dc68083de`.

---

## 1. Approach

The first audition bank should contain **15–20 prototypes**, approximately four concepts for each visible instrument role. The purpose is to test distinct sonic territories and existing engines before writing new DSP.

The longer-term target is approximately **40 excellent factory sound / kit programs**, not 150 generic variations. The exact distribution between kits and synth presets remains open until audition.

A prototype may be:
- A refined version of an existing factory preset.
- A new preset using an existing engine.
- A sound assembled from a sample only when its source and redistribution rights are clear.
- A provisional engine experiment (for example Guru-600 P600) clearly marked as not yet integrated.

No prototype should be described as complete until it has been auditioned on the intended FM-1 hardware and checked for level, tuning, range, CPU, save / recall and musical usefulness.

## 2. Prototype set

### T1 — DRUMS: dedicated 16-lane drum machine

| ID | Working name | Sound brief | First implementation route | Evaluation points |
|---|---|---|---|---|
| D01 | **Basement Machine** | Dry, weighty kick, firm snare, close hats and restrained room; the everyday AFTERHOURS kit | Existing synthesised drum kit and / or existing sample material | Kick weight, snare body, transient balance, no harsh hat buildup |
| D02 | **Vermona Room** | Organic analogue-style kick / tom, noise-led snare and rounded percussion | Drum synth tone + noise + pitch envelope + resonant filter | Does it feel organic and full rather than thin or over-clicked? |
| D03 | **Wire & Glass** | Tuned metallic hits, resonant pings, clangs and industrial accents | Drum synth FM / bell / metallic noise / filter models | Metallic character must be pitched and controlled, not broadband mess |
| D04 | **Dusty Break** | Dry, characterful sampled / break-oriented kit for swung trip-hop and broken beats | Existing sample kits or properly licensed / original samples | Sample provenance, transient consistency, lane balance and groove |

### T2 — PERCUSSION: flexible synth part with percussion-focused presets

| ID | Working name | Sound brief | First engine | Evaluation points |
|---|---|---|---|---|
| P01 | **Felt Glass** | Soft, tuned glass / mallet strike with a rounded attack and controlled ringing tail | PHYS MODAL | Avoid brittle top end; playable over a useful range |
| P02 | **Woodgrain** | Warm wooden bar / marimba-like strike with a little body and short decay | DIGITAL XYLOPHONE / MARIMBA or PHYS MODAL | Compare sample-like digital clarity with modelled organic response |
| P03 | **Bell Foundry** | Inharmonic metal bell / struck plate with a dark body and a few bright partials | FM6 GLASS BELL or PHYS MODAL | Ensure pitch centre is identifiable; avoid piercing transient |
| P04 | **Resonant Relay** | Pitch-swept electronic tom / tuned resonant impact | Dedicated drum-synth concept adapted as ANALOG / TRIO synth preset, or PHYS MEMB | Determine whether ordinary synth note articulation is preferable to a drum lane |

T2 remains a normal synth part. These are preset concepts only; T2 must still load any supported engine and ordinary bass / pad / lead preset.

### T3 — BASS: Minimoog weight + Pro-One articulation

| ID | Working name | Sound brief | First engine | Evaluation points |
|---|---|---|---|---|
| B01 | **Night Weight** | Deep, rounded bass with a solid fundamental and restrained upper harmonics | ANALOG | Low-note consistency, headroom, mono performance |
| B02 | **Pulse Runner** | Tight, articulate pulse / saw sequence bass with glide and decisive envelope | ANALOG | Note articulation, slide behaviour and clean transients |
| B03 | **Soft Dirt** | Warm bass that can move from clean to saturated and resonant | ANALOG + existing drive / insert | Degradation must be controllable; maintain fundamental |
| B04 | **Chrome Sub** | FM / digital bass with a firm low end and a metallic upper edge that does not dominate | FM6 or DIGITAL | Useful tuning range, note-to-note consistency and CPU |

### T4 — AFTER POLY: Prophet warmth + Juno movement

| ID | Working name | Sound brief | First engine | Evaluation points |
|---|---|---|---|---|
| A01 | **Afterglow EP** | Warm Rhodes-like electric piano with a tine attack, rounded body and gentle movement | Existing DIGITAL RHODES; compare FM6 TINE EP | Audition current presets first; compare decay, velocity response and chord clarity |
| A02 | **Mellow Wheels** | Warm tonewheel organ for soulful chords, dub stabs and sustained harmony | DRAWBAR | Smooth registration, no overly bright upper bars, level with other presets |
| A03 | **Blue Velvet** | Full, rounded analogue poly pad with gentle detune and slow Juno-like movement | ANALOG + existing chorus send | Chord density, movement, filter warmth and no sharp string / horn edge |
| A04 | **Soft Prophet** | Prophet-inspired two-oscillator poly voice with oscillator interaction, filter envelope and expressive modulation | ANALOG prototype first; Guru-600 P600 as a separately marked candidate | Compare current engine result with P600 only after a measured port; no assumed clone |

### T5 — TEXTURE / SECOND SYNTH: granular, digital and atmospheric

| ID | Working name | Sound brief | First engine | Evaluation points |
|---|---|---|---|---|
| X01 | **Tape Bloom** | Soft, slowly evolving sample / grain pad with gentle pitch wear | SAMPLE / GRAIN | Stable level, no distracting clicks, no muddy low end |
| X02 | **Rain Window** | Quiet filtered rain / air / hiss texture that can pulse rhythmically | NOISE with controlled filter / envelope, or existing texture bed | Noise must have shape and space; never uncontrolled full-band static |
| X03 | **Ghost Chime** | Soft, distant bell / mallet resonance with evolving partials | PHYS / FM6 / GRAIN | A musical tonal centre, rounded attack, controlled tail |
| X04 | **Slow Signal** | Dark digital pad / drone with gradual timbral movement | PHASE / GRAIN | Movement should be audible but not distract from drums or bass |

## 3. Additional audition queue

These are not extra commitments. They should be auditioned from the existing factory material before deciding whether a new preset or engine is necessary.

| Sound | Existing source to audition | Why it matters |
|---|---|---|
| DX Rhodes / Wurlitzer | DIGITAL | Distinguish the warm EP family from the Rhodes prototype |
| Clav / music box | DIGITAL | Add percussive keyboard choices without a new engine |
| Celesta / kalimba | DIGITAL | Explore soft mallet and pluck tones |
| Vibra bar / chimes / glass bowl | PHYS | Test rounded physical-modelled mallets and bells |
| Wood bars / glass bell | FM6 | Compare FM attack and harmonic body |
| B3-style registrations | DRAWBAR | Organ variations can come from registration and percussion choices |
| Dark string pad | ANALOG / SAMPLE / GRAIN | Avoid generic synthetic ensemble presets |
| Sync / ring stabs | TRIO / PHASE | Add experimental colour without forcing it into every family |

## 4. Audition protocol

Each prototype should be assessed using the same short process:

1. **Solo sound:** listen for the basic character at a sensible register and velocity.
2. **Musical role:** play a simple phrase, bass line, chord or rhythmic pattern appropriate to its intended job.
3. **Range:** check low, middle and high registers; note where it becomes thin, harsh or unnaturally loud.
4. **Control:** turn the primary filter, envelope, modulation and drive / effects controls. They should produce useful changes with predictable ranges.
5. **Mix:** play alongside a representative kick, snare, bass and pad. Check masking and default level.
6. **Repeatability:** stop / restart and reload the preset. Check tuning, transient, level and state.
7. **Resources:** record engine polyphony limit, CPU / target test observations and any storage / patch dependency.

Record an audio example and a short written evaluation for every candidate. A name alone is not evidence of a successful preset.

## 5. Quality gate

A prototype progresses toward the factory bank only when it:
- Has a distinctive audible identity.
- Serves a clear musical role.
- Is not merely a small parameter variation of another preset.
- Sounds good at its default level.
- Has controllable brightness, decay, modulation and degradation where relevant.
- Avoids unexpected clipping, shrill attacks and muddy tails.
- Has a useful pitch / velocity range.
- Does not create an unacceptable CPU or voice-allocation burden.
- Has clean sample / patch provenance and redistribution permission.
- Saves and recalls correctly.

## 6. Initial exclusions

Do not spend the first prototype cycle on:
- Generic supersaws or generic EDM lead variations.
- Sharp, tacky synthetic brass / horn sounds.
- Thin, artificial string ensembles.
- Unfiltered noise bursts with no musical role.
- Large banks of near-identical presets.
- Complex generative chord / progression features.
- New DSP solely to imitate a named instrument where an existing engine can already produce a useful approximation.

## 7. Prototype outcome

After the first audition round, produce:
- A list of prototypes retained, revised and rejected.
- A comparison of DIGITAL RHODES versus FM6 TINE EP.
- A comparison of DRAWBAR organ registrations.
- A comparison of DIGITAL / FM6 / PHYS mallet and bell sounds.
- ANALOG bass and poly sound evaluations.
- A dedicated drum-kit balance and character report.
- A short decision on whether the Guru-600 P600 engine fills a demonstrated gap.
- A refined plan for growing toward approximately 40 excellent factory programs.

The first objective is not to fill a bank. It is to discover which sounds make AFTERHOURS unmistakably AFTERHOURS.
