#include "./randomGenerator.h"
#include "stdio.h"
#include "inttypes.h"

/**
 * @brief Get the next bit in an LFSR register sequence, given a LFSR register; Taps from: https://www.xilinx.com/support/documentation/application_notes/xapp052.pdf
 * @param reg pointer to a LFSR register
 * @return The next 
 */
static uint8_t LFSR_bit(FSR64_t *reg)
{
    uint16_t bit;
    uint8_t output;

    // Note probably compiler dependant
    output = reg->state[0] & 0x01;

    bit = ((reg->state[0] >> 0) ^ (reg->state[0] >> 1) ^ (reg->state[0] >> 2) ^ (reg->state[0] >> 3));
    
    reg->state64 >>= 1;
    reg->state[3] |= (bit << 15);

    return output;
}

static uint8_t NFSR_bit(FSR8_t *reg)
{
    uint8_t bit;
    uint8_t output;

    output = (*reg) & 0x01;
    bit = (((*reg) >> 0) ^ ((*reg) >> 1) ^ ((*reg) >> 5) ^ ((((*reg) >> 1) & ((*reg) >> 5))));
    (*reg) = ((*reg) >> 1) | (bit << 7);

    return output;
}

static FSR64_t lfsr[L - 1] = { 
    { .state64 = 0xa0aa3e11dff2ddaf  }, 
    { .state64 = 0xe02df35627e20498  }
};

static FSR8_t nfsr = 0b10010110;

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