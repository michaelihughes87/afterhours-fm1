# AFTERHOURS sound design specification

## Direction

Hybrid analogue warmth + digital grime. The aim is musical character and dynamic range, not literal analogue-component modelling.

## Reference territories

- Trip-hop / alternative electronics: dusty breaks, layered textures, deep bass, unexpected harmony.
- Post-punk / industrial: physical drums, hard transients, toms, metal, noise and repetition.
- Psychedelic synth pop: warm two-oscillator chords, chorus, phasing, tape movement and saturation.
- Broken-beat / experimental dance: detailed microtiming, syncopation, evolving loops and field-recording textures.
- Melodic electronic: warm bass lines, repeating motifs and lush polyphonic chords.

## Drum sound palette

### Main kit track
808 / 909 / 606-style electronic kits, classic drum-machine voices, acoustic kits, dry / roomy snares, kicks, toms, claps, hats, cymbals, rimshots and break kits.

### Percussion / industrial track
Metal strikes, sheet-metal resonances, chains / machine clanks, concrete / wood impacts, processed acoustic hits, noise bursts, distorted claps, reverse hits, shakers and found-sound percussion.

### Per-kit treatment
Any kit should be able to use the same track insert and send options. Proposed effects:
- FILTER: LP / HP / BP, resonance and envelope where available.
- DRIVE: tape-like saturation, soft clip, fuzz or hard distortion.
- CRUSH: bit reduction and sample-rate reduction.
- MOD: chorus, flange, phase and ring-like movement where affordable.
- SPACE: dark reverb and short room.
- ECHO: tempo sync, feedback and filtered repeats.
- TRANSIENT / SHAPE: tune, decay, attack and lane envelope shaping.

Give each drum track independent processing, with shared FX buses where possible. Per-hit full insert processing is optional and must pass CPU tests.

## Bass

- Deep sine / triangle sub; round upper harmonic support.
- Mono bass, portamento and sequenced slides.
- Driven midrange bass for post-punk / industrial sequences.
- Filter envelope and accent response.

## AFTER POLY

Prophet '08-inspired, not a clone:
- Two band-limited oscillators with saw / pulse / triangle.
- Fine detune, oscillator mix, pulse width and modulation.
- Sync, sub and noise options as resources permit.
- Resonant low-pass filter and distinct filter / amp envelopes.
- LFO and compact modulation routing.
- Unison / voice spread, poly glide, chorus and drive.

## FM / digital

- Six-operator FM metallic percussion, electric-piano-like chords and glassy dissonance.
- Digital bass, inharmonic textures, unstable noise and brittle transients.
- Lo-fi reduction should be controllable, not baked into everything.

## Texture

- Vinyl / tape hiss, room tone, rain, city / mechanical ambience and user recordings.
- Noise and grain beds that can pulse, filter or duck rhythmically.
- Avoid cluttering the low end or masking kick / bass.

## Signature macro concepts

| Macro | Musical result | Guardrails |
|---|---|---|
| TAPE | Saturation, softened top end, slight wow / flutter | Output compensation; no runaway gain |
| DUST | Adds hiss / crackle / grain | Level independently controllable |
| DRIFT | Slow pitch / filter instability | Bounded depth and predictable reset |
| SPACE | Dark, damped ambience | CPU budget and mono compatibility |
| DECAY | Gradual degradation of selected tone parameters | Never changes tempo, project data or levels unexpectedly |

## DSP acceptance criteria

- No clicks on parameter changes or bypass.
- No runaway feedback or DC offset.
- No unexpected clipping at default preset levels.
- CPU measured against upstream baseline.
- Parameters save and recall exactly.
- Bypass is level-matched closely enough to judge the effect.
