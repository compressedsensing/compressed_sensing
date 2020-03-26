#include "./randomGenerator.h"
#include "stdio.h"
#include "inttypes.h"

#define L 3

/* Defines an struct for LFSR registers. */
typedef struct LFSR_strut
{
    uint16_t state;
} LFSR;

typedef struct NLFSR_struct
{
    uint8_t state;
} NLFSR;

/**
 * @brief Get the next bit in an LFSR register sequence, given a LFSR register
 * @param reg pointer to a LFSR register
 * @return The next 
 */
static uint8_t getLFSR_bit(LFSR *reg)
{
    uint8_t i;
    uint16_t bit;
    uint8_t output;

    output = reg->state & 0x00FF; /* Take eight bits*/

    for (i = 0; i < 8; i++)
    {
        bit = ((reg->state >> 0) ^ (reg->state >> 2) ^ (reg->state >> 3) ^ (reg->state >> 5));
        
        /* Rotate in new bit (C)*/ 
        reg->state = (reg->state >> 1) | (bit << 15);
        
        // /* Rotate in new bit (assembly) - Sadly very little gain */ 
        // asm("AND #0x1, %1\n\t"      /* Bit &= 1u*/
        //     "AND #0xFFFE, %0\n\t"   /* LFSR &= ~1u */
        //     "BIS %1, %0\n\t"        /* Logical inclusive or */
        //     "rrc %1\n\t"            /* Rotate bit into Carry bit*/
        //     "rrc %0"                /* Rotate LFSR right*/
        //     : "=r"(reg->state)            /* Outputs */
        //     : "r"(bit), "0"(reg->state)); /* Inputs*/
    }

    return output;
}

static uint8_t getNLSFR(NLFSR *reg)
{
    uint8_t i;
    uint8_t bit;
    uint8_t output;

    output = reg->state;

    for (i = 0; i < 8; i++)
    {
        bit = ((reg->state >> 0) ^ (reg->state >> 3) ^ (((reg->state >> 2) & (reg->state >> 4))));
        reg->state = (reg->state >> 1) | (bit << 7);
    }

    return output;
}

/* Define initial states for LFSR and NLFSR*/
static LFSR gen[L - 1] =
    {{0b1011001000111101},
     {0b1100011111100011}};

static NLFSR ngen = {0b11101010};

/*Global states used by get_random_number*/
static uint8_t iter = 0;
static uint8_t fsr_vals[3];
static const int8_t lookup[4] = {0, -1, 1, 0};

/**
 * @brief Method to generate a random number, from a pseudorandom generator
 * @return Returns a random number drawn from an LFSR sequence
 */
static int8_t get_random_number()
{
    int8_t sum;

    do
    {
        /* Draw new values every 8 iterations*/
        if (iter == 0)
        {
            fsr_vals[0] = getLFSR_bit(&gen[0]);
            fsr_vals[1] = getLFSR_bit(&gen[1]);
            fsr_vals[2] = getNLSFR(&ngen);
        }

        sum = fsr_vals[0] & 1;
        sum += fsr_vals[1] & 1;
        sum += fsr_vals[2] & 1;

        fsr_vals[0] >>= 1;
        fsr_vals[1] >>= 1;
        fsr_vals[2] >>= 1;

        iter = (iter + 1) % 8;

    } while (!lookup[sum]);

    return lookup[sum];
}

const struct random_driver random_driver = {get_random_number};