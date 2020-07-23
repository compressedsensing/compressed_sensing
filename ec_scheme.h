#ifndef EC_H_
#define EC_H_

#include "contiki.h"
#include <stdio.h>
#include <string.h>
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

/**
* @brief Macro defined to draw L random bits from L bernoulli distributed sequences, L=3
* @param output An array of size L. Will contain the bits drawn from the sequences in output[0], output[1] and output[2] respectively 
* @param lfsr An array of size L-1 of type FSR64_t containing the LFSRs
* @param nfsr An NFSR of type FSR8_t
* @param bit16 An empty uint16 variable to perform the state changes of the LFSRs
* @param bit8 An empty uint8 variable to perform the state changes of the NFSR
*/
#define DRAW_RANDOM_BITS(output, lfsr, nfsr, bit16, bit8) ({                                                                              \
            /* Get first LFSR bit */                                                                                        \
            output[0] = lfsr[0].state[0] & 0x01;                                                                            \
            bit16 = (lfsr[0].state[0] >> 0) ^ (lfsr[0].state[0] >> 1) ^ (lfsr[0].state[0] >> 2) ^ (lfsr[0].state[0] >> 3);  \
                                                                                                                            \
            lfsr[0].state64 >>= 1;                                                                                          \
            lfsr[0].state[3] |= (bit16 << 15);                                                                              \
                                                                                                                            \
            /* Get second LFSR bit */                                                                                       \
            output[1] = lfsr[1].state[0] & 0x01;                                                                            \
            bit16 = (lfsr[1].state[0] >> 0) ^ (lfsr[1].state[0] >> 1) ^ (lfsr[1].state[0] >> 2) ^ (lfsr[1].state[0] >> 3);  \
                                                                                                                            \
            lfsr[1].state64 >>= 1;                                                                                          \
            lfsr[1].state[3] |= (bit16 << 15);                                                                              \
                                                                                                                            \
            /* Get NFSR bit */                                                                                              \
            output[2] = nfsr & 0x01;                                                                                        \
            bit8 = ((nfsr >> 0) ^ (nfsr >> 1) ^ (nfsr >> 5) ^ (((nfsr>> 1) & (nfsr >> 5))));                                \
                                                                                                                            \
            nfsr = (nfsr >> 1) | (bit8 << 7);                                                                               \
})                                                                                                                          \

#define ALPHA_MAX ILOG2(N_PRIME-1)
// #define ALPHA_MAX 8
#define BETA_BITS 8

void ec_transform(int16_t* signal);
void ec_transform_structured(int16_t* signal);

#endif /* EC_H_ */