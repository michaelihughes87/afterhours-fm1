# Firmware overlay plan

No AFTERHOURS firmware code has been changed yet.

After importing the upstream baseline:
1. Map UI identity strings, colour/theme settings and factory content.
2. Map preset storage and editor import/export.
3. Map DSP effect chain and per-engine modulation.
4. Add changes as small commits with tests.
5. Keep upstream changes isolated and documented.

Do not begin by replacing the audio engine or project format.
