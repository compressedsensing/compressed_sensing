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
    
    c_16 = fp_sqrt(c, 10) >> FPART;

    return c_16;
}

void multiply_sensing_matrix(int16_t *signal)
{
    // LFSR stuff
    uint16_t bit16;
    uint8_t bit8;
    uint8_t output[L] = { 0 };

    uint16_t m, n;
    int16_t result[M] = { 0 };

    for (m = 0; m < M; m++) {
        for (n = 0; n < N_CS; n++) {
            DRAW_RANDOM_BITS(output,lfsr,nfsr,bit16,bit8);
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

uint8_t alphas[N_CS] = { 0 }; // If index is set to one alpha value is used

void multiply_structured_sensing_matrix(int16_t *signal)
{
    // LFSR stuff
    uint16_t bit16;
    uint8_t bit8;
    uint8_t a;
    uint8_t output[L] = { 0 };
    int8_t basis[N_CS] = { 0 };

    int16_t m,n = 0;
    uint16_t alpha = 0;
    int16_t result[M] = { 0 };

    // Generate first row and base random matrix on that
    for (n = 0; n < N_CS; n++) {
            DRAW_RANDOM_BITS(output,lfsr,nfsr,bit16,bit8);
            if ((output[0] && output[1]) || (output[0] && output[2]) || (output[1] && output[2])) {
                basis[n] = 1;
                result[0] += signal[n];
            } else {
                basis[n] = 0;
                result[0] -= signal[n];
            }
    }

    for (m = 1; m < M; m++) {
        watchdog_periodic();
        // Draw random alpha uniformly from the RNG
        alpha = 0;
        for (a = 0; a < ALPHA_MAX; a++) {
            DRAW_RANDOM_BITS(output,lfsr,nfsr,bit16,bit8);

            alpha <<= 1;
            alpha |= (output[0] && output[1]) || (output[0] && output[2]) || (output[1] && output[2]);
        }

        // Make sure alpha is unique
        while (alphas[alpha]) {
            alpha += 1 % N_CS;
        }
        alphas[alpha] = 1;

        for (n = 0; n < BETA_BITS; n++) {
            DRAW_RANDOM_BITS(output,lfsr,nfsr,bit16,bit8);
            // Flip first BETA_BITS depending on random number, to preserve DC
            if (basis[(n + alpha) % N_CS] ^ ((output[0] && output[1]) || (output[0] && output[2]) || (output[1] && output[2]))) {
                result[m] -= signal[n];
            } else {
                result[m] += signal[n];
            }
        }
        for (n = BETA_BITS; n < N_CS; n++) {
            if (basis[(n + alpha) % N_CS]) {
                result[m] += signal[n];
            } else {
                result[m] -= signal[n];
            }
        }
    }

    // Reset alpha map values for next time
    memset(alphas, 0, N_CS * sizeof(uint8_t));

    /* Copy result into signal */
    memset(signal, 0, N_CS * sizeof(int16_t));
    memcpy(signal, result, M * sizeof(int16_t));
}

void ec_transform(int16_t *signal)
{
    signal[0] = generate_ec_variable(signal);
    multiply_sensing_matrix(signal);
}

void ec_transform_structured(int16_t *signal)
{
    signal[0] = generate_ec_variable(signal);
    multiply_structured_sensing_matrix(signal);
}