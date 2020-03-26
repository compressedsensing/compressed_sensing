#include "ec_scheme.h"

/**
 * @brief Does compressed sensing with a energy concealment scheme. 
 * @param signal The signal to compress. Should be length N-1
 * @param result The result vector. Should be length M
 * @param length The length of the signal, with the c variable.
 */
void ec_transform(int16_t *signal)
{
    LOG_INFO("EC transform begun\n");

    /* Find energy concealment variable 'c' */
    int16_t summing_variable, i;
    int32_t c, e_max;
    c = 0;

    /* sum og xn^2*/
    for (i = 1; i < N_CS; i++)
    {
        summing_variable = FP.fp_multiply(signal[i] >> 2,signal[i] >> 2);

        c += (int32_t)summing_variable << 8;
    }
    
    e_max = 0x03840000; /* 900 */

    c = e_max - c; 
    
    c = FP.fp_sqrt(c, 20); /* 20 iterations */

    /* Add c to the signal */
    signal[0] = (int16_t)(c >> 8);

    /* Sensing matrix multiplication*/
    LINALG.multiply_sensing_matrix(signal);
}

/**
 * @brief Pretty prints the final output value for a signal
 * @param signal The signal to pprint
 * @param length Length of the signal
 */
#if DEBUG
void pprint(int16_t *signal)
{
    int i;
    printf("\n[");
    for (i = 0; i < M; i++)
    {
#if FLOAT
        printf("%.2f", FP.fixed_to_float16(signal[i]));
#else
        printf("%04x", (uint16_t)signal[i]);
#endif
    }
    printf("]\n");
}
#endif

#if DEBUG
const struct energy_concealment_driver energy_concealment_driver = {ec_transform, pprint};
#else 
const struct energy_concealment_driver energy_concealment_driver = {ec_transform};
#endif