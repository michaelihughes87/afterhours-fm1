# AFTERHOURS — Product brief

## Identity

A colourful, tactile, slightly strange groovebox for trip-hop, post-punk, psychedelic synth pop, broken-beat, dub and experimental electronic music.

**Character:** analogue warmth + digital grime. Dark musical moods, colourful visual personality.

Musical reference points include the rhythmic and textural experimentation of Radiohead, the abrasive live-drum energy of IDLES, the psychedelic modulation and saturation of Tame Impala, the detailed broken-beat construction of Four Tet, and the warm melodic propulsion of Caribou. These are broad creative coordinates, not targets for copying recordings, signature sounds or protected artwork.

## Core promise

Turn the FM-1 on and find a complete, playable five-track instrument: a dedicated drum machine, four flexible synth parts, useful kits, expressive polysynths, deep bass, sound textures, immediate mixing and patterns that can grow into arrangements.

## Target track layout

**The agreed target is five tracks: one dedicated drum-machine track plus four independent, flexible synth parts.** The roles below are useful starting points, not locked track types.

| Track | Default role | Purpose |
|---|---|---|
| 1 | DRUMS | Dedicated conventional drum machine: kick, snare, hats, claps, toms and 16-lane kit sequencing |
| 2 | AFTER POLY | Main Prophet-warmth / Juno-movement polysynth |
| 3 | ORGAN / KEYS | Soulful tonewheel organs, warm Rhodes / Wurlitzer-style electric keys and useful keyboard sounds |
| 4 | MONO BASS | Minimoog-weight bass, Pro-One articulation, sub, pulse / saw sequences, glide and controlled drive |
| 5 | TEXTURE / PERC | Granular, digital and atmospheric sounds, plus a compact curated selection of tuned / synthetic percussion |

The four synth parts must remain genuinely flexible. Their labels describe the default musical role and starting preset collection, not restricted track types. Any supported engine and ordinary preset may be loaded on any of the four synth tracks. T5 combines textures and percussion because the agreed instrument has five tracks; percussion is not a separate sixth part.

The visible order is deliberate: drums first, then the main poly, organ / keys, mono bass and finally textures / percussion. It reflects the way the instrument should be approached musically, while leaving every synth part independently assignable.

## Drums

The dedicated drum-machine track should offer a broad palette rather than being exclusively industrial. Include familiar 808/909/606-inspired electronic kits, acoustic / live-sounding kits, hip-hop and breakbeat material, house/electro, jungle/UKG, dub and experimental percussion. Add a strong post-punk / industrial family: dry and room-heavy acoustic drums, hard transient snares, toms, metallic impacts, chains / sheet-metal-like hits, distorted claps, noise bursts and processed found-sound percussion.

Retain the existing 16-lane drum workflow as the starting point. Improve kit browsing, lane editing, level / velocity, tune, decay, choke behaviour and access to track processing where resources permit. Use properly licensed, original or CC0 sample material, with attribution where required.

## Organ / keys

Organ and warm keyboard sounds are a core musical role, not incidental extras. Prioritise soulful tonewheel registrations, rounded B3-style sounds, dub / house organ stabs, warm Rhodes-like tine sounds and useful Wurlitzer-style bite. Keep the factory selection focused and musical; a few excellent registrations and electric-key sounds are more valuable than a large collection of thin imitations. DIGITAL, DRAWBAR / WHEEL and FM6 provide existing starting points to audition before new DSP is considered.

## Mono bass

The bass role should combine Minimoog-like weight with Pro-One articulation. Cover stable sub, rounded two-oscillator bass, tight pulse / saw sequences, glide, resonant movement and controlled saturation. A clean sound should be able to become more aggressive through accessible filter, drive and modulation controls without losing its fundamental. ANALOG is the first implementation route; TRIO and FM6 are contrasting options where they add a genuinely different character.

## Texture and percussion synth part

Track 5 is a normal, fully flexible synth part. Its default sound library combines granular / sampled movement, dark digital atmospheres, controlled noise and a small set of useful tuned or synthetic percussion sounds: resonant pitch sweeps, metallic FM hits, tom-like tones and a few mallet / bell colours. Chimes, glockenspiel and xylophone are supporting colours rather than a major development focus.

T5 is not a percussion-only engine or a second drum machine. The player can select any supported engine and load any ordinary sound on it. Candidate engines include GRAIN, SAMPLE, PHASE, FM6, PHYS, NOISE, DIGITAL and ANALOG, selected by sound suitability. Presets should have musical envelopes, controlled levels and meaningful performance ranges.

## Mixing

Make mixing immediate and tactile:
- Five clearly differentiated track strips, each with a level meter, level, pan, mute and solo.
- Fast access to per-track filter and reverb / delay / modulation sends.
- A clear distinction between the dedicated drum-machine track and the four synth parts.
- Clear visual indication of clipping, muted / soloed tracks, recording and active effects.
- A compact overview that fits the FM-1 display, with deeper per-track controls on secondary pages.
- The web editor / desktop workflow complements the hardware mixer; it does not replace it.

## Polyphonic synthesis

A dedicated **AFTER POLY** voice / sound identity should combine Prophet-family warmth with Juno-style movement: full, rounded chords, subtle detuning, useful pulse-width movement, gentle chorus and expressive filter shaping. Guru-600's Prophet-600 engine is a separate technical candidate, not a claim that the target is a Prophet-600 or Prophet-5 clone.

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

**A nocturnal, organic signal-world:** layered and marbled pigment, dark ink-like negative space, saturated turquoise / teal, vermilion / orange, amber and emerald. The visual language should feel tactile, fluid, slightly strange and kinetic. Use the *In Rainbows* artwork as a broad mood reference only; do not copy its compositions, marks or distinctive artwork.

- Distinct colour identity for all five tracks and recognisable motifs for each engine.
- Sound-reactive imagery: shape, colour, intensity and movement driven by parameters and audio.
- The drum machine as a percussive organism; kick, snare, hats and metallic hits should have distinguishable visual behaviour.
- Synths represented by interacting oscillator forms, membranes or wave structures that respond to detune, filter and envelope.
- FM represented by linked operator nodes; noise and texture by particles, grain, pigment or signal-weather.
- Large readable values and controls remain primary; graphics must not obscure editing or reduce frame rate.
- Themes should be configurable, with a vivid default palette and a calmer high-contrast / reduced-motion alternative.
- Reuse the existing display and small-canvas rendering approach; do not allocate a full-screen framebuffer without a measured memory case.

## Complete groovebox requirements

Preserve and validate:
- Step sequencing and piano-roll editing.
- Swing, microtiming, fills, ratchets, parameter locks and live recording on all applicable tracks.
- Song sections / arrangement and performance controls.
- Presets, user sounds, samples and reliable project / autosave storage.
- MIDI input / output, unique channels for the four synth parts, drum-channel routing, clock sync and USB audio where supported.
- A five-strip mixer, per-track processing, shared effects and master processing.
- Reliable import of existing four-track SLOOP projects without losing their original content.

## Quality bar

AFTERHOURS should sound coherent at default levels, be fast to operate, recover gracefully from overloaded projects, and remain fun to look at during both sound design and live performance. The five-track architecture must pass worst-case CPU, memory, audio-continuity, MIDI and storage tests on the actual FM-1 before a release build is offered for installation.
