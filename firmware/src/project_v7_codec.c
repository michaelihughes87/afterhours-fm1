/* SPDX-License-Identifier: GPL-3.0-only
 * AFTERHOURS FUN7 codec prototype.
 *
 * Standalone, round-trip-tested five-track storage codec. It is deliberately
 * not wired into project_save/project_load yet: legacy FUN1..6 remain the
 * active project format until cache and migration integration is implemented.
 *
 * Layout:
 *   4 synth tracks: 63 common + 8 engine parameters (biased bytes), engine +
 *                   preset, 64 x 8-byte packed steps, 64 micro/fill bytes,
 *                   24 x 3-byte locks = 721 bytes each.
 *   drum track:     63 common parameters, kit byte, seven 16-bit drum
 *                   tune/decay words, 64 x 10-byte lane steps, 64
 *                   micro/fill bytes, 24 x 3-byte locks = 854 bytes.
 *   Project header/globals/checksum bring the C object to 3820 bytes,
 *   including two explicitly reserved tail bytes and 4-byte alignment.
 */
#include <stddef.h>
#include <stdint.h>

#define PROJ7_MAGIC 0x46554E37u
#define PROJ7_COMMON 63u
#define PROJ7_ENGINE_PARAMS 8u
#define PROJ7_SYNTH_TRACKS 4u
#define PROJ7_TRACKS (PROJ7_SYNTH_TRACKS + 1u)
#define PROJ7_STEP_BYTES 8u
#define PROJ7_LOCK_BYTES 3u

typedef struct {
    uint8_t p[PROJ7_COMMON];
    uint8_t e[PROJ7_ENGINE_PARAMS];
    uint8_t engine, preset;
    uint8_t step[NSTEP * PROJ7_STEP_BYTES];
    uint8_t mf[NSTEP];
    uint8_t lock[NLOCK * PROJ7_LOCK_BYTES];
} proj7_synth_t;

typedef struct {
    uint8_t p[PROJ7_COMMON];
    uint8_t kit;
    uint8_t tune_decay[14];       /* seven little-endian 16-bit lane-pair words */
    uint8_t step[NSTEP * sizeof(dstep_t)];
    uint8_t mf[NSTEP];
    uint8_t lock[NLOCK * PROJ7_LOCK_BYTES];
} proj7_drum_t;

typedef struct {
    uint32_t magic, size;
    int16_t g[PROJ_NG];
    uint8_t sel, drdly, rsv[2];
    proj7_synth_t synth[PROJ7_SYNTH_TRACKS];
    proj7_drum_t drum;
    uint8_t rsv_tail[2];
    uint32_t sum;
} project_v7_t;

typedef struct {
    int16_t p[P_COUNT];
    uint8_t engine, preset;
    step_t step[NSTEP];
    uint8_t mf[NSTEP];
    plock_t lock[NLOCK];
} proj7_synth_data_t;

typedef struct {
    int16_t p[P_COUNT];                /* P_E1..P_E7 are represented by tune_decay below */
    int16_t tune_decay[7];
    dstep_t step[NSTEP];
    uint8_t mf[NSTEP];
    plock_t lock[NLOCK];
} proj7_drum_data_t;

typedef struct {
    int16_t g[PROJ_NG];
    uint8_t sel, drdly, rsv[2];         /* includes the legacy TEXTURE metadata bytes */
    proj7_synth_data_t synth[PROJ7_SYNTH_TRACKS];
    proj7_drum_data_t drum;
} project_v7_data_t;

_Static_assert(P_E0 == PROJ7_COMMON && P_COUNT == 71u, "FUN7 prototype freezes the current 71-parameter base");
_Static_assert(PROJ_NG == 32u && NSTEP == 64u && NLOCK == 24u, "FUN7 prototype dimensions");
_Static_assert(sizeof(step_t) == 10u && sizeof(dstep_t) == 10u, "FUN7 step codecs expect current step layouts");
_Static_assert(sizeof(proj7_synth_t) == 721u, "FUN7 synth track must be 721 bytes");
_Static_assert(sizeof(proj7_drum_t) == 854u, "FUN7 drum track must be 854 bytes");
_Static_assert(sizeof(project_v7_t) == 3820u && sizeof(project_v7_t) <= 3840u,
               "FUN7 project must fit the 3840-byte storage payload");
_Static_assert(4u * sizeof(project_v7_t) <= 0x3D50u - 256u,
               "four retained FUN7 sections must fit the existing .noinit budget");

static int proj7_byte_put(uint8_t *out, int16_t value, const param_desc_t *desc)
{
    if (!out || !desc || desc->min < -64 || desc->max > 127 ||
        value < desc->min || value > desc->max)
        return 0;
    *out = (uint8_t)(value + 64);
    return 1;
}

static int16_t proj7_byte_get(uint8_t value, const param_desc_t *desc)
{
    int32_t v = (int32_t)value - 64;
    if (v < desc->min) v = desc->min;
    if (v > desc->max) v = desc->max;
    return (int16_t)v;
}

static int proj7_common_put(uint8_t out[PROJ7_COMMON], const int16_t p[P_COUNT])
{
    uint32_t i;
    for (i = 0; i < PROJ7_COMMON; i++)
        if (!proj7_byte_put(&out[i], p[i], &TP[i]))
            return 0;
    return 1;
}

static void proj7_common_get(int16_t p[P_COUNT], const uint8_t in[PROJ7_COMMON])
{
    uint32_t i;
    for (i = 0; i < PROJ7_COMMON; i++)
        p[i] = proj7_byte_get(in[i], &TP[i]);
}

static int proj7_step_valid(const step_t *s)
{
    uint32_t i;
    if (!s || s->n > 4u || s->time > ST_REST || s->vel > 127u)
        return 0;
    for (i = 0; i < 4u; i++)
        if (s->note[i] > 127u)
            return 0;
    return 1;
}

static void proj7_step_put(uint8_t out[PROJ7_STEP_BYTES], const step_t *s)
{
    uint64_t bits = 0;
    uint32_t i, n = s->n;
    uint32_t time = s->time;

    for (i = 0; i < 4u; i++)
        bits |= (uint64_t)s->note[i] << (7u * i);
    bits |= (uint64_t)(n & 7u) << 28;
    bits |= (uint64_t)(time & 3u) << 31;
    bits |= (uint64_t)s->flags << 33;
    bits |= (uint64_t)s->vel << 41;
    bits |= (uint64_t)s->lvl << 48;
    bits |= (uint64_t)s->rat << 56;
    for (i = 0; i < PROJ7_STEP_BYTES; i++)
        out[i] = (uint8_t)(bits >> (8u * i));
}

static void proj7_step_get(step_t *d, const uint8_t in[PROJ7_STEP_BYTES])
{
    uint64_t bits = 0;
    uint32_t i, n, time;
    memset(d, 0, sizeof *d);
    for (i = 0; i < PROJ7_STEP_BYTES; i++)
        bits |= (uint64_t)in[i] << (8u * i);
    for (i = 0; i < 4u; i++)
        d->note[i] = (uint8_t)((bits >> (7u * i)) & 0x7Fu);
    n = (uint32_t)((bits >> 28) & 7u);
    time = (uint32_t)((bits >> 31) & 3u);
    d->n = (uint8_t)(n > 4u ? 4u : n);
    d->time = (uint8_t)(time > ST_REST ? ST_REST : time);
    d->flags = (uint8_t)(bits >> 33);
    d->vel = (uint8_t)((bits >> 41) & 0x7Fu);
    d->lvl = (uint8_t)(bits >> 48);
    d->rat = (uint8_t)(bits >> 56);
}

static int proj7_lock_put(uint8_t out[PROJ7_LOCK_BYTES], const plock_t *l)
{
    if (l->step == LOCK_FREE) {
        out[0] = out[1] = out[2] = 0;
        return 1;
    }
    if (l->step >= NSTEP || l->param >= P_COUNT || l->param >= 128u ||
        l->val < -64 || l->val > 127)
        return 0;
    out[0] = (uint8_t)(l->step + 1u);  /* 0 is free; 1..64 represent steps 0..63 */
    out[1] = l->param;
    out[2] = (uint8_t)(l->val + 64);
    return 1;
}

static int proj7_lock_get(plock_t *d, const uint8_t in[PROJ7_LOCK_BYTES])
{
    if (!in[0]) {
        d->step = LOCK_FREE;
        d->param = 0;
        d->val = 0;
        return 1;
    }
    if (in[0] > NSTEP || in[1] >= P_COUNT || in[2] > 191u)
        return 0;
    d->step = (uint8_t)(in[0] - 1u);
    d->param = in[1];
    d->val = (int16_t)((int32_t)in[2] - 64);
    return 1;
}

static const param_desc_t PROJ7_RAW_EDIT_DESC = {"RAW", F_INT, -64, 127, 0, 0, 0};

int proj7_synth_pack(proj7_synth_t *d, const int16_t p[P_COUNT], uint8_t engine, uint8_t preset,
                     const step_t steps[NSTEP], const uint8_t mf[NSTEP], const plock_t locks[NLOCK])
{
    uint32_t i;
    if (!d || !p || !steps || !mf || !locks || !proj7_common_put(d->p, p))
        return 0;
    for (i = 0; i < PROJ7_ENGINE_PARAMS; i++) {
        const param_desc_t *desc = engine < NENGINES ? &ENGINES[engine]->edit[i] : &PROJ7_RAW_EDIT_DESC;
        if (!proj7_byte_put(&d->e[i], p[P_E0 + i], desc))
            return 0;
    }
    for (i = 0; i < NSTEP; i++)
        if (!proj7_step_valid(&steps[i]))
            return 0;
    d->engine = engine;
    d->preset = preset;
    for (i = 0; i < NSTEP; i++) {
        proj7_step_put(&d->step[i * PROJ7_STEP_BYTES], &steps[i]);
        d->mf[i] = mf[i];
    }
    for (i = 0; i < NLOCK; i++)
        if (!proj7_lock_put(&d->lock[i * PROJ7_LOCK_BYTES], &locks[i]))
            return 0;
    return 1;
}

int proj7_synth_unpack(const proj7_synth_t *s, int16_t p[P_COUNT], uint8_t *engine, uint8_t *preset,
                       step_t steps[NSTEP], uint8_t mf[NSTEP], plock_t locks[NLOCK])
{
    uint32_t i;
    if (!s || !p || !engine || !preset || !steps || !mf || !locks)
        return 0;
    memset(p, 0, P_COUNT * sizeof p[0]);
    proj7_common_get(p, s->p);
    for (i = 0; i < PROJ7_ENGINE_PARAMS; i++) {
        const param_desc_t *desc = s->engine < NENGINES ? &ENGINES[s->engine]->edit[i] : &PROJ7_RAW_EDIT_DESC;
        p[P_E0 + i] = proj7_byte_get(s->e[i], desc);
    }
    *engine = s->engine;
    *preset = s->preset;
    for (i = 0; i < NSTEP; i++) {
        proj7_step_get(&steps[i], &s->step[i * PROJ7_STEP_BYTES]);
        if (!proj7_step_valid(&steps[i]))
            return 0;
        mf[i] = s->mf[i];
    }
    for (i = 0; i < NLOCK; i++)
        if (!proj7_lock_get(&locks[i], &s->lock[i * PROJ7_LOCK_BYTES]))
            return 0;
    return 1;
}

int proj7_drum_pack(proj7_drum_t *d, const int16_t p[P_COUNT], const int16_t tune_decay[7],
                    const dstep_t steps[NSTEP], const uint8_t mf[NSTEP], const plock_t locks[NLOCK])
{
    uint32_t i;
    if (!d || !p || !tune_decay || !steps || !mf || !locks ||
        !proj7_common_put(d->p, p) || !proj7_byte_put(&d->kit, p[P_E0], &DRUM_KIT_DESC))
        return 0;
    for (i = 0; i < 7u; i++) {
        uint16_t v = (uint16_t)tune_decay[i];
        d->tune_decay[i * 2u] = (uint8_t)v;
        d->tune_decay[i * 2u + 1u] = (uint8_t)(v >> 8);
    }
    memcpy(d->step, steps, sizeof d->step);
    memcpy(d->mf, mf, sizeof d->mf);
    for (i = 0; i < NLOCK; i++)
        if (!proj7_lock_put(&d->lock[i * PROJ7_LOCK_BYTES], &locks[i]))
            return 0;
    return 1;
}

int proj7_drum_unpack(const proj7_drum_t *s, int16_t p[P_COUNT], int16_t tune_decay[7],
                      dstep_t steps[NSTEP], uint8_t mf[NSTEP], plock_t locks[NLOCK])
{
    uint32_t i;
    if (!s || !p || !tune_decay || !steps || !mf || !locks)
        return 0;
    memset(p, 0, P_COUNT * sizeof p[0]);
    proj7_common_get(p, s->p);
    p[P_E0] = proj7_byte_get(s->kit, &DRUM_KIT_DESC);
    for (i = 0; i < 7u; i++)
        tune_decay[i] = (int16_t)((uint16_t)s->tune_decay[i * 2u] |
                                  (uint16_t)((uint16_t)s->tune_decay[i * 2u + 1u] << 8));
    memcpy(steps, s->step, sizeof s->step);
    memcpy(mf, s->mf, sizeof s->mf);
    for (i = 0; i < NLOCK; i++)
        if (!proj7_lock_get(&locks[i], &s->lock[i * PROJ7_LOCK_BYTES]))
            return 0;
    return 1;
}

static uint32_t proj7_hash(const void *data, uint32_t n)
{
    const uint8_t *b = (const uint8_t *)data;
    uint32_t i, h = 0x811C9DC5u;
    for (i = 0; i < n; i++)
        h = (h ^ b[i]) * 16777619u;
    return h;
}

void proj7_begin(project_v7_t *p, const int16_t g[PROJ_NG], uint8_t sel, uint8_t drdly)
{
    memset(p, 0, sizeof *p);
    p->magic = PROJ7_MAGIC;
    p->size = sizeof *p;
    memcpy(p->g, g, sizeof p->g);
    p->sel = sel;
    p->drdly = drdly;
}

void proj7_seal(project_v7_t *p)
{
    p->rsv_tail[0] = p->rsv_tail[1] = 0;
    p->sum = proj7_hash(p, (uint32_t)offsetof(project_v7_t, sum));
}

int proj7_valid(const project_v7_t *p)
{
    return p && p->magic == PROJ7_MAGIC && p->size == sizeof *p &&
           p->rsv_tail[0] == 0u && p->rsv_tail[1] == 0u &&
           p->sum == proj7_hash(p, (uint32_t)offsetof(project_v7_t, sum));
}

int proj7_project_pack(project_v7_t *out, const project_v7_data_t *in)
{
    uint32_t i;
    if (!out || !in || in->sel >= PROJ7_TRACKS)
        return 0;
    proj7_begin(out, in->g, in->sel, in->drdly);
    memcpy(out->rsv, in->rsv, sizeof out->rsv);
    for (i = 0; i < PROJ7_SYNTH_TRACKS; i++)
        if (!proj7_synth_pack(&out->synth[i], in->synth[i].p, in->synth[i].engine,
                              in->synth[i].preset, in->synth[i].step,
                              in->synth[i].mf, in->synth[i].lock))
            return 0;
    if (!proj7_drum_pack(&out->drum, in->drum.p, in->drum.tune_decay,
                         in->drum.step, in->drum.mf, in->drum.lock))
        return 0;
    proj7_seal(out);
    return proj7_valid(out);
}

int proj7_project_unpack(const project_v7_t *in, project_v7_data_t *out)
{
    uint32_t i;
    if (!in || !out || !proj7_valid(in) || in->sel >= PROJ7_TRACKS)
        return 0;
    memset(out, 0, sizeof *out);
    memcpy(out->g, in->g, sizeof out->g);
    out->sel = in->sel;
    out->drdly = in->drdly;
    memcpy(out->rsv, in->rsv, sizeof out->rsv);
    for (i = 0; i < PROJ7_SYNTH_TRACKS; i++)
        if (!proj7_synth_unpack(&in->synth[i], out->synth[i].p,
                                &out->synth[i].engine, &out->synth[i].preset,
                                out->synth[i].step, out->synth[i].mf, out->synth[i].lock))
            return 0;
    if (!proj7_drum_unpack(&in->drum, out->drum.p, out->drum.tune_decay,
                           out->drum.step, out->drum.mf, out->drum.lock))
        return 0;
    return 1;
}
