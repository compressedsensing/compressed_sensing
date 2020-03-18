#include "./randomGenerator.h"
#include "stdio.h"
#include "inttypes.h"

#define L 3

/* Defines an struct for LFSR registers. */
struct LFSR
{
    uint16_t state;
};

typedef struct NLFSR_struct
{
    uint8_t state;
} NLFSR;

typedef struct LFSR LFSR;

/**
 * @brief Get the next bit in an LFSR register sequence, given a LFSR register
 * @param reg pointer to a LFSR register
 * @return The next 
 */
static uint8_t getLFSR_bit(struct LFSR *reg)
{
    uint16_t bit;
    uint8_t output;

    output = reg->state & 0x01;
    bit = ((reg->state >> 0) ^ (reg->state >> 2) ^ (reg->state >> 3) ^ (reg->state >> 5));
    reg->state = (reg->state >> 1) | (bit << 15);

    return output;
}

static uint8_t getNLSFR(NLFSR *reg)
{

    uint8_t bit;
    uint8_t output;
    output = reg->state & 0x01;
    bit = ((reg->state >> 0) ^ (reg->state >> 3) ^ (((reg->state >> 2) & (reg->state >> 4))));
    
    reg->state = (reg->state >> 1) | (bit << 7);
    return output;
}

/**
 * @brief Converts a bit from 0 to -1 and 1-MAX to 1
 * @param input Expects a binary value saved in an unsigned char
 * @return returns -1 or 1 depending on input 0 or 1
 */
static int16_t converter(uint16_t input)
{
    if (!input)
    {
        // printf("ZERO\n");
        return (-1);
    }
    // printf("ONE\n");
    return 1;
}

static struct LFSR gen[L-1] =
    {{0b1010100011000100},
     {0b1010111001011011}};

static NLFSR ngen = {0b11101010};

/**
 * @brief Method to generate a random number, from a pseudorandom generator
 * @return Returns a random number drawn from an LFSR sequence
 */
static int16_t get_random_number()
{
    int16_t sum, j;

    /* As long as the value is equal to -+ L, keep drawing new numbers*/
    do
    {
        sum = 0;
        for (j = 0; j < L-1; j++)
        {
            sum += converter(getLFSR_bit(&gen[j]));
        }
        /* Draw a single NLFSR bit */
        sum += converter(getNLSFR(&ngen));

    } while (sum == L || sum == -L);

    return sum;
}

const struct random_driver random_driver = {get_random_number};