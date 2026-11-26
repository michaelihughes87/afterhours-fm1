# AFTERHOURS — sound design specification

## Direction

Hybrid analogue warmth + digital grime. The aim is musical character and dynamic range, not literal analogue-component modelling.

## Reference territories

- Trip-hop / alternative electronics: dusty breaks, layered textures, deep bass, unexpected harmony.
- Post-punk / industrial: physical drums, hard transients, toms, metal, noise and repetition.
- Psychedelic synth pop: warm two-oscillator chords, chorus, phasing, tape movement and saturation.
- Broken-beat / experimental dance: detailed microtiming, syncopation, evolving loops and field-recording textures.
- Melodic electronic: warm bass lines, repeating motifs and lush polyphonic chords.

## Five-track sound roles

1. **DRUMS — dedicated drum machine.** The conventional 16-lane kit instrument, with electronic, acoustic, hip-hop / breakbeat, dance, dub and industrial families.
2. **PERCUSSION — flexible synth.** A standard synth part with access to every engine. The factory bank should make it immediately useful for tuned percussion and rhythmic timbres, but it is not restricted to percussion.
3. **BASS — flexible synth.** Deep sub, mono bass, acid sequences, driven midrange and FM / digital bass.
4. **AFTER POLY — flexible synth.** Main analogue-style polyphonic voice, pads, chords, plucks and leads.
5. **TEXTURE / SECOND SYNTH — flexible synth.** Atmospheres, strings, noise, sample manipulation, FM textures and supplementary leads / chords.

These are factory defaults and curated preset roles, not track locks. Any synth track can load any available synth engine.

## Dedicated drum-machine palette

The drum identity must be broad rather than exclusively industrial:
- Electronic: 808 / 909 / 606-inspired kicks, snares, hats, claps, toms and cymbals.
- Acoustic / live: dry and roomy kits, tight and loose snares, rimshots, toms, brushes and room hits.
- Hip-hop / break: dusty breaks, chopped hits, boom-bap and loose swing.
- Dance: house, electro, techno, jungle / DnB and UKG.
- Dub / organic: hand percussion, shakers, congas, rim / wood and sparse accents.
- Post-punk / industrial: hard room snare, trashy acoustic kit, metal, clangs, impacts, noise bursts and processed objects.

Retain the existing 16 lanes as the starting point. Any per-lane feature expansion must be measured against CPU and storage limits.

## Percussion-synth preset direction

Build a curated bank across multiple engines, not one dedicated percussion engine:
- **PHYS:** modal bells, bars, struck plates, membrane toms, plucked metal / string objects.
- **FM6:** metallic operators, tuned hits, clangs, brittle bells and inharmonic attacks.
- **DRAWBAR:** percussive partials, short organ stabs and unusual struck registrations.
- **SAMPLE:** tuned found sounds, wood / metal hits and short acoustic material where licensed.
- **NOISE / DIGITAL:** noise bursts, clicks, zaps, synthetic hats and transient textures.
- **ANALOG:** short envelopes, resonant filter strikes, pulse plucks and tuned tom-like voices.

Percussion presets should have short, useful envelopes, safe default levels, clear tuning and musically useful pitch ranges. They must remain editable and must not stop the player loading a pad, bass or sustained sound on T2.

## Bass

- Deep sine / triangle sub; round upper harmonic support.
- Mono bass, portamento and sequenced slides.
- Driven midrange bass for post-punk / industrial sequences.
- Filter envelope and accent response.
- FM / digital bass as a contrasting option.

## AFTER POLY

Prophet '08-inspired, not a clone:
- Two band-limited oscillators with saw / pulse / triangle.
- Fine detune, oscillator mix, pulse width and modulation.
- Sync, sub and noise options as resources permit.
- Resonant low-pass filter and distinct filter / amp envelopes.
- LFO and compact modulation routing.
- Unison / voice spread, poly glide, chorus and drive.

Extend and voice the existing ANALOG engine first. Keep the sound musical at default levels and validate oscillator / filter changes for clicks and aliasing.

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
- CPU measured against the passing baseline and tested under five-track worst-case load.
- Parameters save and recall exactly.
- Bypass is level-matched closely enough to judge the effect.
