#include "./randomGenerator.h"

#define L 3

struct LFSR
{
    uint16_t state;
    uint16_t polynomiel;
};

typedef struct LFSR LFSR;

/**
 * @brief Get the next bit in an LFSR register sequence, given a LFSR register
 * @param reg pointer to a LFSR register
 * @return The next 
 */
static uint16_t getLFSR_bit(struct LFSR *reg)
{
    uint16_t cs, cp, nbit;
    int i = 0;

    cs = reg->state;

    cp = nbit = cs & reg->polynomiel;

    for (i = 1; i < 16; i++)
    {
        /* xor all bits together */
        nbit ^= (cp >> i);
    }
    reg->state = (cs >> 1) | (nbit << 15); /*  rotate in new bit */

    // printf("%0.1x", cs & 0x01);
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
        return (-1);
    }
    return 1;
}


static struct LFSR gen[3] =
    {{0b1010100011000100, 0b1000000000000001},
     {0b1010111001011011, 0b1000000000000001},
     {0b1010101010001010, 0b1000000000000001}};
// static struct LFSR gen[3] =
//     {{0b1110001101001100, 0b1100110000000011},
//      {0b1110001110001000, 0b1100110001010001},
//      {0b1110001110001101, 0b1100110010010011}};

/**
 * @brief Method to generate a random number, from a pseudorandom generator
 * @return Returns a random number drawn from an LFSR sequence
 */
static int32_t get_random_number()
{
    int32_t sum, j;
    int16_t tmp;
    uint16_t hep;

    do
    {
        sum = 0;
        for (j = 0; j < L; j++)
        {
            sum += (int32_t)converter(getLFSR_bit(&gen[j]));
            // printf("%d",sum);
        }
    } while (sum == L || sum == -L);

    return sum;
}

const struct random_driver random_driver = {get_random_number};