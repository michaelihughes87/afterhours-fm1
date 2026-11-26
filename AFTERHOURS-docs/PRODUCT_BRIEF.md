# AFTERHOURS — Product brief

## Identity

A colourful, tactile, slightly strange groovebox for trip-hop, post-punk, psychedelic synth pop, broken-beat, dub and experimental electronic music.

**Character:** analogue warmth + digital grime. Dark musical moods, colourful visual personality.

Musical reference points include the rhythmic and textural experimentation of Radiohead, the abrasive live-drum energy of IDLES, the psychedelic modulation and saturation of Tame Impala, the detailed broken-beat construction of Four Tet, and the warm melodic propulsion of Caribou. These are broad creative coordinates, not targets for copying recordings, signature sounds or protected artwork.

## Core promise

Turn the FM-1 on and find a complete, playable musical instrument: useful kits, expressive polysynths, deep bass, sound textures, immediate mixing and patterns that can grow into arrangements.

## Target track layout

**Six tracks preferred; five is the fallback only if hardware performance or interface constraints make six impractical.**

| Track | Default role | Purpose |
|---|---|---|
| 1 | DRUMS A | Main kit: kick, snare, hats, claps, toms |
| 2 | DRUMS B | Percussion, breaks, industrial hits, found sounds |
| 3 | BASS | Sub, mono synth, acid / sequence bass |
| 4 | POLY A | Main Prophet-inspired analogue polysynth |
| 5 | POLY B | Pads, chords, strings, second poly voice |
| 6 | TEXTURE / LEAD | FM, sample, noise, lead or atmosphere |

Roles are defaults, not hard locks: where the engine architecture permits, users should be able to assign a different sound engine to a track. The two default drum tracks must remain independent, with their own kit, pattern, level, pan, sends and effect treatment.

## Drums

The drum identity must be broad rather than exclusively industrial. Include familiar 808/909/606-style electronic kits, acoustic / live-sounding kits, hip-hop and breakbeat material, house/electro, jungle/UKG, dub and experimental percussion. Add a strong post-punk / industrial family: dry and room-heavy acoustic drums, hard transient snares, toms, metallic impacts, chains / sheet-metal-like hits, distorted claps, noise bursts and processed found-sound percussion.

Both drum tracks need the same broad sound-shaping and effect access. A user should be able to put a standard 808 kit on one track and an abrasive, noisy industrial kit on the other.

## Mixing

Make mixing immediate and tactile:
- Six clearly differentiated track strips, each with level meter, level, pan, mute and solo.
- Fast access to per-track filter and reverb / delay / modulation sends.
- Dedicated access to the two drum buses and master processing.
- Clear visual indication of clipping, muted/soloed tracks and active effects.
- Web editor / desktop workflow should complement the hardware mixer, not replace it.

## Polyphonic synthesis

A dedicated **AFTER POLY** engine should take inspiration from classic analogue polysynths such as the Prophet '08 without claiming to reproduce the original instrument.

Target voice controls:
- Two band-limited oscillators with saw, pulse / PWM and triangle options.
- Oscillator mix, fine detune, octave range and sync where CPU permits.
- Optional sub / noise layer.
- Resonant low-pass filter with filter envelope; HP / BP options if resources allow.
- Amp and filter envelopes, LFO and a small, useful modulation matrix.
- Unison / voice spread and polyphonic glide options.
- Chorus, drive and tone shaping suited to slow chords, arpeggios and evolving pads.

The existing SLOOP ANALOG engine already has two band-limited oscillators, detune, noise, drive and a state-variable filter. First investigate extending and voicing that engine before introducing a separate duplicate oscillator engine.

## Visual identity

**A neon nocturnal ecosystem:** colourful, organic, kinetic, playful and slightly uncanny. Do not merely repaint JIANT; develop a distinct AFTERHOURS art direction.

- Distinct colour identity for each track and engine.
- Sound-reactive imagery: shape, colour, intensity and movement driven by the parameters and audio.
- Drum tracks as animated colonies / percussive organisms; kick, snare, hats and metallic hits should have distinguishable visual behaviour.
- Poly synths represented by interacting oscillator forms / membranes / wave structures that respond to detune, filter and envelope.
- FM represented by linked operator nodes; noise and texture by particles, grain or signal-weather.
- Large readable values and controls remain primary; graphics must not obscure editing or reduce frame rate.
- Themes should be configurable, with a vivid default palette and a calmer high-contrast alternative.

## Complete groovebox requirements

Preserve and validate:
- Step sequencing and piano-roll editing.
- Swing, microtiming, fills, ratchets, parameter locks and live recording.
- Song sections / arrangement and performance controls.
- Presets, user sounds, samples and reliable storage.
- MIDI input / output, clock sync and USB audio where supported.
- Mixer, effects and project save / load.

## Quality bar

AFTERHOURS should sound coherent at default levels, be fast to operate, recover gracefully from overloaded projects, and remain fun to look at during both sound design and live performance.
