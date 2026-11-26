# AFTERHOURS — Sound Design Specification

**Status:** Creative source of truth for AFTERHOURS sound, presets and sound-manipulation priorities.
**Firmware assessment baseline:** `afterhours-five-track` at `46d8cd6a00cf3c3830593b3b95bb4d7dc68083de`.
**Scope:** Design direction only. This document does not authorise DSP changes, track-architecture changes, project-format changes or new hardware assumptions.

---

## 1. Purpose

AFTERHOURS should become a distinctive, expressive electronic instrument, not a generic groovebox with a large collection of near-identical presets.

The design should draw from analogue synthesisers, digital instruments, drum machines, hybrid keyboards and experimental sound-design equipment. Their useful musical characteristics should be translated into sounds and controls that work on the M-VAVE FM-1.

The references are creative coordinates, not requirements to reproduce every circuit or feature. Technical feasibility must be established against the actual firmware, processor, memory, voice allocation and storage.

**The instrument should sound exceptional first.** Feature count, preset count and theoretical synthesis completeness are secondary to sound quality and musical usefulness.

## 2. Updated priority hierarchy

The priorities are deliberately ordered:

1. **Sound quality and character.** Distinctive, convincing and musical drums, percussion, bass, keys, polyphonic sounds, pads, textures and noise.
2. **Sound manipulation.** Meaningful access to synthesis parameters, filters, envelopes, modulation, tone-shaping / EQ where technically justified, effects and mixing.
3. **Performance and workflow.** Immediate access to the controls that matter, with an intuitive surface and deeper editing available without weakening the proven SLOOP workflow.
4. **Creative extras.** Chord generation, inversions, scale assistance and generative progressions are optional enhancements. They must not displace sound, sound manipulation or performance work.

Chord generation and Orchid-inspired musical functions are nice-to-have additions, not core release requirements. Existing sequencing and musical tools should be preserved where practical; new work in this area is lower priority.

A carefully curated collection of around **40 genuinely distinctive, controllable factory sounds / kit programs** is a better target than 150 generic presets. Quality, range and usefulness matter more than filling slots.

## 3. Overall sonic identity

### Hybrid analogue warmth / digital grime

AFTERHOURS should combine:

- Warm, rounded analogue-style tones and expressive oscillator interaction.
- Deep bass with weight, definition and articulation.
- Rich but controlled polyphonic chords, keys and pads.
- Characterful electronic drums and synthetic percussion.
- Metallic, FM and resonant sounds that remain musical.
- Tape-like softening, saturation and degradation where achievable.
- Granular, sampled and digital textures with movement and atmosphere.
- Unusual sounds, instability and noise used deliberately rather than indiscriminately.

The result should feel tactile, slightly imperfect and expressive. It should be capable of warmth and beauty as well as aggression and strangeness.

### Musical imperfection, not uncontrolled randomness

Analogue drift, detuning, saturation, hiss, crackle and unstable movement are valuable when they contribute to the musical result.

They must be controllable, bounded and intentional. A preset should not become noisy, harsh or unpredictable merely to signal that it is “vintage” or “experimental”. Stable settings should remain available. The intensity of degradation should be a sound-design choice, not an unavoidable default.

## 4. Positive tonal preferences

The survey clarified several important preferences that should influence preset selection and engine work.

### Warm keys and harmonic instruments

Organ and warm electric-piano sounds are important parts of the AFTERHOURS palette.

Prioritise:
- Rhodes-like warmth and tine character.
- Wurlitzer-like bite where it remains rounded and musical.
- Soft, soulful and slightly worn electric keys.
- Warm tonewheel organ and restrained drawbar registrations.
- Clavinet / plucked keyboard sounds where they are not excessively sharp.
- Glockenspiel, xylophone, celesta, vibraphone, bells and rounded mallet tones.

These sounds should be treated as first-class musical voices, not incidental preset-bank filler.

### Polyphonic sounds

The main polyphonic identity should combine **Prophet warmth with Juno movement**:
- Full, rounded, harmonically rich chords.
- Gentle detuning and subtle instability.
- Warm pulse / saw combinations.
- Soft chorus, ensemble-like movement and slow modulation.
- Rounded brass-like tones rather than piercing synthetic horns.
- Strings and pads that are dark, layered and organic rather than thin, bright or tacky.

The Prophet-5 is a primary *sonic* reference. Guru-600's Prophet-600 engine is a separate technical reference and potential additional engine; it is not automatically a substitute for a Prophet-5-inspired sound.

### Bass

The bass identity should blend:
- Minimoog-like weight and fullness.
- Pro-One articulation, sync and movement.
- SH-101-like rhythmic clarity.
- MS-20-inspired aggression when deliberately selected.
- FM bass as a contrasting digital colour.

Sub-bass should remain solid and controlled. Upper harmonics should provide definition without sacrificing the fundamental. Distortion and instability should be available as deliberate transformations.

### Percussion

Tuned percussion should cover several complementary characters:
- Rounded mallets and wooden bars.
- Glassy and bell-like tones.
- Inharmonic metallic strikes.
- Resonant membranes and synthetic toms.
- Pitch-swept electronic percussion.
- Short FM attacks and industrial impacts.

The xylophone / glockenspiel preference is a strong reason to prioritise smooth, tuned, playable mallet presets alongside more aggressive metallic sounds.

## 5. Primary synthesiser references

| Reference | Desired characteristics | AFTERHOURS interpretation |
|---|---|---|
| Moog Minimoog Model D | Thick bass, oscillator weight, detuning, resonant filter movement | Deep, rounded and articulate analogue-style bass |
| Sequential Prophet-5 | Warm polyphony, brass, strings, unison and cross-modulation | Main polyphonic warmth; full chords and musical modulation |
| Roland Juno-106 | Chorus pads, warm sub character, plucks and mellow polyphony | Soft movement, ensemble-like pads and rounded poly sounds |
| Oberheim OB-Xa / OB-8 | Wide chords, brass, unison and dark strings | Broad, rich chords without brittle synthetic edges |
| Korg MS-20 | Dirty bass, aggressive resonance, noise and filter character | Selectable aggressive / industrial sounds, not the default tonal character |
| ARP 2600 | Experimental percussion, metallic sounds, drones and modulation | Resonant percussion and unconventional textures |
| Yamaha CS-80 | Cinematic pads, evolving textures and expressive brass | Slow, expressive and layered sounds where technically achievable |
| Roland SH-101 | Tight mono bass, sequences and direct analogue character | Clear, sequenced and punchy bass |
| Sequential Pro-One | Aggressive bass, sync and modulation | Articulated bass and sharper sync-led sounds |
| Roland Jupiter-8 | Rich polyphonic sounds, brass, strings and leads | Selective wide polyphonic tones |
| PPG Wave 2.2 | Digital wavetable character and evolving metallic tones | Digital timbre and evolving textures; a true wavetable engine is not assumed |
| EMS Synthi AKS | Experimental noise, feedback and unstable drones | Controlled noise, feedback-like movement and unusual textures |
| Korg Polysix | Warm strings, ensemble and analogue pads | Soft, warm pads and sustained harmonic beds |

The Minimoog and Prophet-5 are foundational sound references. MS-20, ARP 2600, PPG and EMS influences should prevent the palette becoming predictable, but should not make the overall sound harsh or chaotic.

## 6. Drum machine and percussion references

### Primary references

| Reference | Desired characteristics |
|---|---|
| Elektron Machinedrum | Synthetic drum variety, metallic percussion, glitches and programmable sound design |
| Elektron Analog Rytm | Deep kicks, snares, distortion and layered percussion |
| Vermona DRM1 | Organic analogue-style kicks, toms, noise snares and metallic percussion |
| Jomox XBase / MBase | Powerful, sub-heavy kicks and aggressive low end |
| Pearl Syncussion SY-1 | Pitch sweeps and synthetic toms |
| Simmons SDS-V | Electronic toms and resonant percussion |
| Korg Electribe ER-1 | FM-like percussion, metallic timbres and ring-modulated character |
| Yamaha RX5 | Distinctive electronic and sampled percussion |
| Linn LM-1 / Oberheim DMX / E-mu Drumulator | Dry, punchy and characterful sampled drums |
| Roland CR-78 | Vintage rhythmic textures |

The Machinedrum, Vermona, Jomox, Syncussion and Simmons territories should be particularly influential.

### Desired drum categories

- Deep analogue-style kick and clean sub kick.
- Punchy and distorted electronic kick.
- Acoustic-style and analogue-style snare.
- Noise-based snare and clap.
- Closed / open hats and metallic hats.
- Synthetic toms and pitch-swept percussion.
- Industrial impacts, metallic hits and FM percussion.
- Digital glitches, resonant pings and controlled noise bursts.

The dedicated 16-lane drum machine should remain broad: electronic, sampled, acoustic-style, breakbeat, dub, dance and industrial kits should coexist.

## 7. Bass synthesis references

| Reference | Desired characteristics |
|---|---|
| Minimoog / Minitaur | Deep, rounded, powerful bass |
| Sequential Pro-One | Aggressive, articulated bass and sequences |
| Roland SH-101 | Tight rhythmic bass and sub character |
| Korg MS-20 | Dirty, distorted and resonant bass |
| Novation Bass Station II | Acid, overdrive and modern analogue bass |
| Yamaha DX7 / TX81Z | Metallic, hard-edged FM bass |
| Waldorf Pulse | Tight, powerful analogue-style mono bass |

Target bass families:
1. Deep sine / triangle sub.
2. Rounded analogue bass.
3. Detuned oscillator bass.
4. Bouncy / rubber bass.
5. Resonant acid bass.
6. Saturated dirty bass.
7. Metallic FM bass.
8. Industrial bass.
9. Tight sequenced bass.
10. Sustained drone bass.

A key performance idea is transforming a clean bass into a more distorted, aggressive or unstable sound through accessible controls.

## 8. Pads, soundscapes and experimental textures

| Reference | Desired characteristics |
|---|---|
| Roland D-50 | Digital / analogue hybrid textures and cinematic pads |
| PPG Wave 2.2 | Evolving digital timbres and metallic character |
| Korg Wavestation | Evolving sequences and atmospheric layers |
| Ensoniq ESQ-1 | Hybrid digital oscillators and analogue filters |
| Roland JX-8P | Smooth, dark pads and layered brass |
| EMS Synthi AKS | Experimental drones, noise and feedback |
| Make Noise 0-Coast | Unconventional synthesis and organic electronic textures |

Target textures:
- Evolving atmospheric drones.
- Dark cinematic pads.
- Warm analogue strings and ensemble-like sounds.
- Chorus-heavy pads.
- Slowly moving detuned textures.
- Tape hiss and carefully controlled degradation.
- Industrial noise and metallic resonances.
- Feedback-like textures.
- Glitch and digital artefacts.
- Wavetable-like movement, without assuming a true wavetable engine.
- Spacey echoes, ghostly pads and broken-circuit textures.

Noise must have a musical purpose: pitched, resonant, rhythmic, filtered, transient, atmospheric or dynamically shaped. Avoid messy broadband noise with no tonal or rhythmic identity.

## 9. Effects and processing references

| Reference | Desired character |
|---|---|
| Roland Space Echo RE-201 | Tape-style delay, warmth and modulation |
| Lexicon PCM 70 | Atmospheric digital reverbs |
| Eventide H3000 | Pitch shifting, modulation and spatial effects |
| Electro-Harmonix Memory Man | Organic analogue delay |
| Strymon Deco | Tape saturation and double tracking |
| Boss SP-303 | Degraded samples, vinyl character and lo-fi processing |

These are tonal references, not implementation requirements. Use existing processing first. Any new effect must justify its CPU cost and provide a clear musical improvement.

## 10. Five-track sonic identity

The existing five-track architecture remains the agreed design. Track roles are default musical orientations and preset collections, not restrictions.

| Track | Role | Primary sound territories |
|---|---|---|
| T1 | Dedicated drum machine | Machinedrum, Linn, Vermona, Jomox, DMX, Syncussion |
| T2 | Flexible percussion synth | Syncussion, Simmons, ER-1, ARP, FM, modal and mallet percussion |
| T3 | Flexible bass synth | Minimoog, Pro-One, MS-20, SH-101, DX / FM bass |
| T4 | Main poly synth | Prophet-5, Juno, Oberheim, Jupiter, warm keys and pads |
| T5 | Texture / second synth | PPG, D-50, Wavestation, EMS, CS-80, samples and granular textures |

T2 remains a normal, fully flexible synth part. Every synth track must be able to load any supported engine.

## 11. Sound manipulation and performance

The user should have both immediate musical results and meaningful sound-design depth.

Priorities:
- Useful, well-balanced factory presets.
- Accessible oscillator / tone, filter, envelope and modulation controls.
- Clear access to drive, effects and mix controls.
- Tone-shaping and EQ capability where the current architecture supports it or a measured extension justifies it.
- Predictable, musical parameter ranges.
- Immediate access to the controls most important to playing and sequencing.
- Deeper editing without a maze of menus.
- Safe defaults and level consistency across engines.
- Presets that are genuinely editable, not opaque demonstrations of hidden modulation.

The existing firmware does not appear to provide a conventional fully parametric per-track EQ or an unrestricted modular modulation matrix. These are design aspirations to assess, not existing capabilities to claim.

## 12. Preset design philosophy

A smaller collection of distinctive sounds is preferred over a large collection of superficial variations.

Every preset should:
- Have a recognisable character and musical purpose.
- Differ meaningfully from other presets.
- Be useful within a specific register or performance role.
- Have coherent naming and a short description.
- Expose useful synthesis controls.
- Have appropriate polyphony and CPU cost.
- Be level-matched and free of unexpected clipping or harsh transients.
- Have a controlled default level of noise, drive and modulation.
- Save and recall consistently.

The working library target is approximately 40 excellent factory sound / kit programs, subject to audition and feasibility. Begin with 15–20 prototypes and expand only when each new sound adds a genuinely different use.

## 13. Technical constraints and decision rules

- Preserve the agreed five-track design and the initial shared eight-voice synth budget unless a measured assessment recommends otherwise.
- Distinguish what can be achieved by presets from what requires DSP, architecture, sample content or storage changes.
- Evaluate CPU under realistic simultaneous use; isolated engine cost is not sufficient.
- Respect engine-specific voice limits and the existing per-part engine memory design.
- Do not assume that sample libraries can be redistributed simply because they are downloadable. Verify the licence and attribution for every distributed sample set.
- Do not copy protected recordings, proprietary sound banks or artwork.
- Keep chord generation, inversions, scale assistance and generative progressions secondary.
- Do not implement new DSP or change project / track architecture solely because a reference instrument has a feature.

## 14. What success sounds like

AFTERHOURS should combine:
- The weight of a Minimoog.
- The polyphonic warmth of a Prophet and Juno.
- The aggression of an MS-20.
- The experimental character of an ARP 2600 and EMS.
- The tuned synthetic percussion of a Syncussion and Simmons.
- The rhythmic diversity of a Machinedrum.
- The digital atmosphere of a PPG Wave and Roland D-50.
- The warmth of Rhodes and organ.
- The musical clarity of xylophones, glockenspiels and other tuned mallet instruments.

**Most importantly, these references should inform the instrument's overall sound and controls, not simply become vintage equipment names attached to presets.**
