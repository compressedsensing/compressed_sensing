#include "./randomGenerator.h"
#include "stdio.h"

#define L 3

/* Defines an struct for LFSR registers. */
struct LFSR
{
    uint16_t state;
    uint16_t polynomiel;
};

typedef struct LFSR LFSR;

/**
 * @brief Reverses the order of bits in a 2 Bytes
 * @param b Bit to be inverted
 * @return Reverse bits of input 
 */
uint16_t reverse_bits16(uint16_t b)
{
    b = (b & 0xFF00) >> 8 | (b & 0x00FF) << 8;
    b = (b & 0xF0F0) >> 4 | (b & 0x0F0F) << 4;
    b = (b & 0xCCCC) >> 2 | (b & 0x3333) << 2;
    b = (b & 0xAAAA) >> 1 | (b & 0x5555) << 1;
    return b;
}

/**
 * @brief Get the next bit in an LFSR register sequence, given a LFSR register
 * @param reg pointer to a LFSR register
 * @return The next 
 */
static unsigned char getLFSR_bit(struct LFSR *reg)
{
    uint16_t cs, cp, nbit;
    int i = 0;

    cs = reg->state;

    cp = nbit = reverse_bits16(cs & reg->polynomiel);

    for (i = 1; i < 16; i++)
    {
        /* xor all bits together */
        nbit ^= (cp >> i);
    }
    reg->state = (cs >> 1) | (nbit << 15); /*  rotate in new bit */

    return cs & 0x01;
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

static struct LFSR gen[L] =
    {{0b1010100011000100, 0b1100000000000001},
     {0b1010111001011011, 0b1001000000000001},
     {0b1010101010001010, 0b1000010000000001}};

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
        for (j = 0; j < L; j++)
        {
            sum += converter(getLFSR_bit(&gen[j]));

        }
    } while (sum == L || sum == -L);

    return sum;
}

const struct random_driver random_driver = {get_random_number};