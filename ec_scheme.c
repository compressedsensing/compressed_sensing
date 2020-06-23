#include "ec_scheme.h"
#include "./randomGenerator.h"

static FSR64_t lfsr[L - 1] = { 
    { .state64 = 0xa0aa3e11dff2ddaf  }, 
    { .state64 = 0xe02df35627e20498  }
};

static FSR8_t nfsr = 0b10010110;

/**
 * @brief Does compressed sensing with a energy concealment scheme. 
 * @param signal The signal to compress. Should be length N-1
 * @param result The result vector. Should be length M
 * @param length The length of the signal, with the c variable.
 */

int16_t generate_ec_variable(int16_t *signal)
{
    int16_t i;
    int32_t c = 0;

    for (i = 1; i < N_CS; i++)
    {
        c += FP.fp_multiply(signal[i],signal[i]);
    }

    c <<= 8;
    c = EMAX - c; 
    
    c = FP.fp_sqrt(c, 20); /* 20 iterations */

    return (int16_t)(c >> 8);
}

void multiply_sensing_matrix(int16_t *signal)
{
    // LFSR stuff
    uint16_t bit16;
    uint8_t bit8;
    uint8_t output[L] = { 0 };

    uint16_t m, n;
    int16_t result[M] = { 0 };

    // Generate first two column and base random matrix on that
    for (m = 0; m < M; m++)
    {
        result[m] = 0;
        for (n = 0; n < N_CS; n++)
        {
            // Get first LFSR bit
            output[0] = lfsr[0].state[0] & 0x01;
            bit16 = (lfsr[0].state[0] >> 0) ^ (lfsr[0].state[0] >> 1) ^ (lfsr[0].state[0] >> 2) ^ (lfsr[0].state[0] >> 3);

            lfsr[0].state64 >>= 1;
            lfsr[0].state[3] |= (bit16 << 15);

            // Get second LFSR bit
            output[1] = lfsr[1].state[0] & 0x01;
            bit16 = (lfsr[1].state[0] >> 0) ^ (lfsr[1].state[0] >> 1) ^ (lfsr[1].state[0] >> 2) ^ (lfsr[1].state[0] >> 3);

            lfsr[1].state64 >>= 1;
            lfsr[1].state[3] |= (bit16 << 15);

            // Get NFSR bit
            output[2] = nfsr & 0x01;
            bit8 = ((nfsr >> 0) ^ (nfsr >> 1) ^ (nfsr >> 5) ^ (((nfsr>> 1) & (nfsr >> 5))));

            nfsr = (nfsr >> 1) | (bit8 << 7);


            if ((output[0] && output[1]) || (output[0] && output[2]) || (output[1] && output[2])) {
                result[m] += signal[n];
            } else {
                result[m] -= signal[n];
            }
        }
    }

    /* Copy result into signal */
    memset(signal, 0, N_CS * sizeof(int16_t));
    memcpy(signal, result, M * sizeof(int16_t));
}

void ec_transform(int16_t *signal)
{
    signal[0] = generate_ec_variable(signal);
    multiply_sensing_matrix(signal);
}


const struct energy_concealment_driver energy_concealment_driver = {ec_transform};