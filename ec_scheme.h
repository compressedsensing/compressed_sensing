#ifndef EC_H_
#define EC_H_

#include "contiki.h"
#include <stdio.h>
#include "sys/log.h"
#include "./cs_config.h"
#include "./fixedpoint.h"
#include "./random_generator.h"

// Idea from https://stackoverflow.com/questions/27581671/how-to-compute-log-with-the-preprocessor
#define IS_REPRESENTIBLE_IN_D_BITS(D, N)                \
  (((uint16_t) N >= (1U << (D - 1)) && (uint16_t) N < (1U << D)) ? D : -1)

#define ILOG2(N) (N == 0 ? 1 : (15                       \
                 + IS_REPRESENTIBLE_IN_D_BITS( 1, N)    \
                 + IS_REPRESENTIBLE_IN_D_BITS( 2, N)    \
                 + IS_REPRESENTIBLE_IN_D_BITS( 3, N)    \
                 + IS_REPRESENTIBLE_IN_D_BITS( 4, N)    \
                 + IS_REPRESENTIBLE_IN_D_BITS( 5, N)    \
                 + IS_REPRESENTIBLE_IN_D_BITS( 6, N)    \
                 + IS_REPRESENTIBLE_IN_D_BITS( 7, N)    \
                 + IS_REPRESENTIBLE_IN_D_BITS( 8, N)    \
                 + IS_REPRESENTIBLE_IN_D_BITS( 9, N)    \
                 + IS_REPRESENTIBLE_IN_D_BITS(10, N)    \
                 + IS_REPRESENTIBLE_IN_D_BITS(11, N)    \
                 + IS_REPRESENTIBLE_IN_D_BITS(12, N)    \
                 + IS_REPRESENTIBLE_IN_D_BITS(13, N)    \
                 + IS_REPRESENTIBLE_IN_D_BITS(14, N)    \
                 + IS_REPRESENTIBLE_IN_D_BITS(15, N)    \
                 + IS_REPRESENTIBLE_IN_D_BITS(16, N)    \
))

// #define ALPHA_MAX ILOG2(N_CS-1)
#define ALPHA_MAX 8
#define BETA_BITS 64

#define EC energy_concealment_driver

struct energy_concealment_driver
{
    void (* ec_transform)(int16_t* signal);
};

extern const struct energy_concealment_driver EC;

#endif /* EC_H_ */