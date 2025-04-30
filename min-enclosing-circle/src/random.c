#include "random.h"
#include <time.h>

static uint64_t rng_state[2];

static inline uint64_t rotl(uint64_t x, int k) {
    return (x << k) | (x >> (64 - k));
}

uint64_t xoroshiro128plus(void) {
    const uint64_t s0 = rng_state[0];
    uint64_t s1 = rng_state[1];
    const uint64_t result = s0 + s1;

    s1 ^= s0;
    rng_state[0] = rotl(s0, 55) ^ s1 ^ (s1 << 14);
    rng_state[1] = rotl(s1, 36);

    return result;
}

void seed_rng(uint64_t seed1, uint64_t seed2) {
    rng_state[0] = seed1;
    rng_state[1] = seed2;
}

void seed_rng_auto() {
    seed_rng((uint64_t)time(NULL), (uint64_t)clock());
}

void shuffle(Point* points, int count) {
    if (count <= 1) return;

    for (int i = count - 1; i > 0; --i) {
        int j = xoroshiro128plus() % (i + 1);
        Point temp = points[i];
        points[i] = points[j];
        points[j] = temp;
    }
}

