#include "ec_scheme.h"

/**
 * @brief Does compressed sensing with a energy concealment scheme. 
 * @param signal The signal to compress. Should be length N-1
 * @param result The result vector. Should be length M
 * @param length The length of the signal, with the c variable.
 */
void ec_transform(Vector *signal, Vector_M *result)
{

    // Find energy concealment variable 'c'
    FIXED11_21 c, hep;
    c.full = 0;

    uint16_t i;
    for (i = 1; i < N; i++)
    {
        hep.full = FP.fp_pow(signal->data[i], 2).full >> 2;

        c = FP.fp_add(c, hep);
    }

    FIXED11_21 e_max;
    e_max.full = FP.float_to_fixed(EMAX).full;

    c = FP.fp_subtract(e_max, c);
    // printf("%2f\t",FP.fixed_to_float(c));
    c = FP.fp_sqrt(c, 20);
    // printf("%2f\t",FP.fixed_to_float(c));

    c.full = c.full << 1;
    // printf("%2f\t",FP.fixed_to_float(c));

    //Add c to the signal
    Vector aug_signal;

    aug_signal.data[0] = c;
    for (i = 1; i < N; i++)
    {
        aug_signal.data[i] = signal->data[i - 1];
    }
    printf("here!!\n");

    // Ax = y From compressed sensing
    LINALG.multiply_sensing_matrix(&aug_signal, result);
}

/**
 * @brief Pretty prints the final output value for a signal
 * @param signal The signal to pprint
 * @param length Length of the signal
 */
void pprint(Vector_M *signal)
{
    int i;
    printf("\n[");
    for (i = 0; i < M; i++)
    {
        printf("%02x \t", signal->data[i]);
        // printf("%.2f", FP.fixed_to_float(signal->data[i]));
        if (i != M - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
}

const struct energy_concealment_driver energy_concealment_driver = {ec_transform, pprint};
