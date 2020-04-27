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
    uint8_t output, carry;

    output = (*reg)[1] & 0x01;

    bit = (((*reg)[1] >> 0) ^ ((*reg)[1] >> 1) ^ ((*reg)[1] >> 2) ^ ((*reg)[0] >> 6));
    carry = (*reg)[0] & 0x01;
    (*reg)[1] = ((*reg)[1] >> 1) | (carry << 15);
    (*reg)[0] = ((*reg)[0] >> 1) | (bit << 15);

    return output;
}

static uint8_t NFSR_bit(NFSR *reg)
{
    uint16_t bit;
    uint8_t output;

    output = (*reg) & 0x01;
    bit = (((*reg) >> 0) ^ ((*reg) >> 3) ^ ((((*reg) >> 2) & ((*reg) >> 4))));
    (*reg) = ((*reg) >> 1) | (bit << 15);

    return output;
}

static LFSR lfsr[L - 1] = { 
    { 0b0111011010010101, 0b0100111001010010 }, 
    { 0b1101011101001111, 0b1000111010110011 }
};

static NFSR nfsr = { 0b0101001110101001 };

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