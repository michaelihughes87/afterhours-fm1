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
| 2 | PERCUSSION | A normal, fully flexible synth part intended for percussion design; can load any available synth engine and its ordinary presets, with a curated percussion-focused preset collection |
| 3 | BASS | Sub, mono synth, acid / sequence bass, driven midrange bass |
| 4 | AFTER POLY | Main Prophet-inspired analogue-style polysynth |
| 5 | TEXTURE / SECOND SYNTH | Pads, chords, strings, FM, sample, noise, lead or atmosphere |

The four synth parts must remain genuinely flexible. PERCUSSION is a suggested musical role and starter preset collection, not a restricted percussion engine or a special track type. A user can load any existing or future synth engine on it. The same principle applies to the other synth roles: labels and default sounds guide the player without preventing reassignment.

The dedicated DRUMS track remains the conventional multi-lane drum instrument. It is not replaced by a synth, and the percussion-synth track does not take away or weaken the dedicated drum machine.

## Drums

The dedicated drum-machine track should offer a broad palette rather than being exclusively industrial. Include familiar 808/909/606-inspired electronic kits, acoustic / live-sounding kits, hip-hop and breakbeat material, house/electro, jungle/UKG, dub and experimental percussion. Add a strong post-punk / industrial family: dry and room-heavy acoustic drums, hard transient snares, toms, metallic impacts, chains / sheet-metal-like hits, distorted claps, noise bursts and processed found-sound percussion.

Retain the existing 16-lane drum workflow as the starting point. Improve kit browsing, lane editing, level / velocity, tune, decay, choke behaviour and access to track processing where resources permit. Use properly licensed, original or CC0 sample material, with attribution where required.

## Percussion synth part

Track 2 is a full synth part, not a second drum-machine track. It should be immediately useful for tuned percussion, mallets, bells, metal, struck objects, plucks, noisy transients, tom-like synths, FM hits, resonant textures and unusual rhythmic voices.

Build a dedicated percussion-focused preset collection across the existing engines. Candidate engines include PHYS, FM6, DRAWBAR, SAMPLE, NOISE, DIGITAL and ANALOG, chosen by sound suitability. Presets should have sensible envelopes, useful pitch ranges and controlled levels. The player must still be able to browse all engines and load any normal synth sound on this track.

## Mixing

Make mixing immediate and tactile:
- Five clearly differentiated track strips, each with a level meter, level, pan, mute and solo.
- Fast access to per-track filter and reverb / delay / modulation sends.
- A clear distinction between the dedicated drum-machine track and the four synth parts.
- Clear visual indication of clipping, muted / soloed tracks, recording and active effects.
- A compact overview that fits the FM-1 display, with deeper per-track controls on secondary pages.
- The web editor / desktop workflow complements the hardware mixer; it does not replace it.

## Polyphonic synthesis

A dedicated **AFTER POLY** voice / sound identity should take inspiration from classic analogue polysynths such as the Prophet '08 without claiming to reproduce the original instrument.

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
