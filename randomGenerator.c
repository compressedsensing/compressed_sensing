#include "./randomGenerator.h"
#include "stdio.h"
#include "inttypes.h"

/**
 * @brief Get the next bit in an LFSR register sequence, given a LFSR register
 * @param reg pointer to a LFSR register
 * @return The next 
 */
static uint8_t LFSR_bit(LFSR *reg)
{
    uint16_t bit;
    uint8_t output;

    output = (*reg) & 0x01;
    bit = (((*reg) >> 0) ^ ((*reg) >> 2) ^ ((*reg) >> 3) ^ ((*reg) >> 5));
    (*reg) = ((*reg) >> 1) | (bit << 15);

    return output;
}

static uint8_t NFSR_bit(NFSR *reg)
{
    uint8_t bit;
    uint8_t output;

    output = (*reg) & 1;
    bit = (((*reg) >> 0) ^ ((*reg) >> 3) ^ ((((*reg) >> 2) & ((*reg) >> 4))));
    (*reg) = ((*reg) >> 1) | (bit << 7);

    return output;
}

/* Define initial states for LFSR and NLFSR*/
static LFSR lfsr[L - 1] = { 
    0b1011001000111101, 
    0b1100011111100011
};

static NFSR nfsr = { 0b11101010 };

static const int8_t converter[4] = {-1, -1, 1, 1};

/**
 * @brief Method to generate a random number, from a pseudorandom generator
 * @return Returns a random number drawn from an LFSR sequence
 */
static int8_t get_random_number()
{
    return converter[LFSR_bit(&lfsr[0]) + LFSR_bit(&lfsr[1]) + NFSR_bit(&nfsr)];
}

const struct random_driver random_driver = {get_random_number};