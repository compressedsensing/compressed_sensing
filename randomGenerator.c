#include "./randomGenerator.h"

#define L 3

struct LFSR
{
    unsigned char state;
    unsigned char polynomiel;
};

typedef struct LFSR LFSR;

/**
 * @brief Get the next bit in an LFSR register sequence, given a LFSR register
 * @param reg pointer to a LFSR register
 * @return The next 
 */
static unsigned char getLFSR_bit(struct LFSR *reg)
{
    unsigned char cs, cp, nbit;
    int i = 0;

    cs = reg->state;

    cp = nbit = cs & reg->polynomiel;

    for (i = 1; i < 8; i++)
    {
        /* xor all bits together */
        nbit ^= (cp >> i);
    }
    reg->state = (cs >> 1) | (nbit << 7); /*  rotate in new bit */

    // printf("%0.1x", cs & 0x01);
    return cs & 0x01;
}

/**
 * @brief Converts a bit from 0 to -1 and 1-MAX to 1
 * @param input Expects a binary value saved in an unsigned char
 * @return returns -1 or 1 depending on input 0 or 1
 */
signed char converter(unsigned char input)
{
    if (input)
    {
        return (-1);
    }
    return 1;
}

static struct LFSR gen[3] =
    {{0b01001100, 0b00000011},
     {0b10001000, 0b01010001},
     {0b10001101, 0b10010011}};

/**
 * @brief Method to generate a random number, from a pseudorandom generator
 * @return Returns a random number drawn from an LFSR sequence
 */
static float get_random_number()
{
    int j;
    signed char sum;

    do
    {
        sum = 0;
        for (j = 0; j < L; j++)
        {
            sum += converter(getLFSR_bit(&gen[j]));
        }
    } while (sum == L);

    return (float)sum;
}

const struct random_driver random_driver = {get_random_number};