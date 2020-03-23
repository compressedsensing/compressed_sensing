#include "ec_scheme.h"

/**
 * @brief Does compressed sensing with a energy concealment scheme. 
 * @param signal The signal to compress. Should be length N-1
 * @param result The result vector. Should be length M
 * @param length The length of the signal, with the c variable.
 */
void ec_transform(Vector *signal, Vector_M *result)
{
    LOG_INFO("EC transform begun\n");

    // Find energy concealment variable 'c'
    int16_t hep;
    int32_t c;
    c = 0;

    uint16_t i;

    /* sum og xn^2*/
    for (i = 1; i < N_CS; i++)
    {
        hep = FP.fp_pow(signal->data[i] >> 2, 2);

        c += (int32_t)hep << 8;
    }
    
    int32_t e_max;
    e_max = 0x03840000;

    c = e_max - c;
    
    c = FP.fp_sqrt(c, 20);


    /* Add c to the signal */
    Vector aug_signal;

    aug_signal.data[0] = (int16_t)(c >> 8);

    for (i = 1; i < N_CS; i++)
    {
        aug_signal.data[i] = signal->data[i - 1];
    }


    LOG_INFO("Energy variable found \n\n");

    /* Sensing matrix multiplication*/
    LINALG.multiply_sensing_matrix(&aug_signal, result);

    LOG_INFO("EC Transform complete\n");
}

/**
 * @brief Pretty prints the final output value for a signal
 * @param signal The signal to pprint
 * @param length Length of the signal
 */
#if DEBUG
void pprint(Vector_M *signal)
{
    int i;
    printf("\n[");
    for (i = 0; i < M; i++)
    {
#if FLOAT
        printf("%.2f", FP.fixed_to_float16(signal->data[i]));
#else
        printf("%04x", (uint16_t)signal->data[i]);
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