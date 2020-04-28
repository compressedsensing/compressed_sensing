#include "./randomGenerator.h"
#include "stdio.h"
#include "inttypes.h"

/**
 * @brief Get the next bit in an LFSR register sequence, given a LFSR register
 * @param reg pointer to a LFSR register
 * @return The next 
 */
static uint8_t LFSR_bit(FSR *reg)
{
    uint16_t bit;
    uint8_t output;

    // Generic code

    // output = (*reg)[1] & 0x01;

    // bit = (((*reg)[1] >> 0) ^ ((*reg)[1] >> 1) ^ ((*reg)[1] >> 2) ^ ((*reg)[0] >> 6));
    // carry = (*reg)[0] & 0x01;
    // (*reg)[1] = ((*reg)[1] >> 1) | (carry << 15);
    // (*reg)[0] = ((*reg)[0] >> 1) | (bit << 15);

    // Note probably compiler dependant

    output = reg->state[0] & 0x01;

    bit = ((reg->state[0] >> 0) ^ (reg->state[0] >> 1) ^ (reg->state[0] >> 2) ^ (reg->state[1] >> 6));
    
    reg->state32 >>= 1;
    reg->state[1] |= (bit << 15);

    return output;
}

static uint8_t NFSR_bit(FSR *reg)
{
    uint16_t bit;
    uint8_t output;

    // output = (*reg) & 0x01;
    // bit = (((*reg) >> 0) ^ ((*reg) >> 2) ^ ((*reg) >> 13) ^ ((((*reg) >> 2) & ((*reg) >> 3))));
    // (*reg) = ((*reg) >> 1) | (bit << 15);

    output = reg->state[0] & 0x01;
    bit = ((reg->state[0] >> 0) ^ (reg->state[0] >> 2) ^ (reg->state[0] >> 13) ^ (((reg->state[0] >> 2) & (reg->state[0] >> 3))));
    reg->state32 >>= 1;
    reg->state[1] |= (bit << 15);

    return output;
}

static FSR lfsr[L - 1] = { 
    { .state32 = 0b01110110100101010100111001010010 }, 
    { .state32 = 0b11010111010011111000111010110011 }
};

static FSR nfsr = { .state32 = 0b10010110010101010010001011101101 };

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