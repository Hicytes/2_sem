#ifndef RANDOM_H
#define RANDOM_H

#include "geometry.h"
#include <stdint.h>

void seed_rng(uint64_t seed1, uint64_t seed2);
void seed_rng_auto();
uint64_t xoroshiro128plus(void);
void shuffle(Point* points, int count);

#endif

