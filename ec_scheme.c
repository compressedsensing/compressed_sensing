#include "./ec_scheme.h"

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
    int16_t i, c_16;
    int32_t c = 0;

    for (i = 1; i < N_CS; i++) {
        c += (int32_t) signal[i] * signal[i];
    }

    c = EMAX - c;
    c_16 = c >> FPART;
    
    c_16 = FP.fp_sqrt_fast(c_16);

    return c_16;
}

void multiply_sensing_matrix(int16_t *signal)
{
    // LFSR stuff
    uint16_t bit16;
    uint8_t bit8;
    uint8_t a;
    uint8_t output[L] = { 0 };
    int8_t basis[N_CS] = {0};

    uint16_t m, n, alpha = 0;
    int16_t result[M] = { 0 };

    // Generate first row and base random matrix on that
    for (n = 0; n < N_CS; n++) {
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
                basis[n] = 1;
                result[0] += signal[0];
            } else {
                basis[n] = -1;
                result[0] -= signal[0];
            }
    }

    for (m = 1; m < M; m++) {
        // Draw random alpha
        alpha = 0;
        for (a = 0; a < ALPHA_MAX; a++) {
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

            alpha <<= 1;
            alpha |= (output[0] && output[1]) || (output[0] && output[2]) || (output[1] && output[2]);
        }
        // Make sure alpha is uneven
        if (!(alpha & 0x0001)) {
            alpha += 1;
        }

        for (n = 0; n < N_CS; n++) {
            if (basis[((n - m) * alpha) % N_CS] & 0x80) {
                result[m] -= signal[n];
            } else {
                result[m] += signal[n];
            }
        }
    }

    // for (m = 0; m < M; m++) {
    //     result[m] = 0;
    //     for (n = 0; n < N_CS; n++) {
    //         // Get first LFSR bit
    //         output[0] = lfsr[0].state[0] & 0x01;
    //         bit16 = (lfsr[0].state[0] >> 0) ^ (lfsr[0].state[0] >> 1) ^ (lfsr[0].state[0] >> 2) ^ (lfsr[0].state[0] >> 3);

    //         lfsr[0].state64 >>= 1;
    //         lfsr[0].state[3] |= (bit16 << 15);

    //         // Get second LFSR bit
    //         output[1] = lfsr[1].state[0] & 0x01;
    //         bit16 = (lfsr[1].state[0] >> 0) ^ (lfsr[1].state[0] >> 1) ^ (lfsr[1].state[0] >> 2) ^ (lfsr[1].state[0] >> 3);

    //         lfsr[1].state64 >>= 1;
    //         lfsr[1].state[3] |= (bit16 << 15);

    //         // Get NFSR bit
    //         output[2] = nfsr & 0x01;
    //         bit8 = ((nfsr >> 0) ^ (nfsr >> 1) ^ (nfsr >> 5) ^ (((nfsr>> 1) & (nfsr >> 5))));

    //         nfsr = (nfsr >> 1) | (bit8 << 7);


    //         if ((output[0] && output[1]) || (output[0] && output[2]) || (output[1] && output[2])) {
    //             result[m] += signal[n];
    //         } else {
    //             result[m] -= signal[n];
    //         }
    //     }
    // }

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