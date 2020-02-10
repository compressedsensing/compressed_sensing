#include "ec_scheme.h"

/**
 * @brief Does compressed sensing with a energy concealment scheme. 
 * @param signal The signal to compress. Should be length N-1
 * @param result The result vector. Should be length M
 * @param length The length of the signal, with the c variable.
 */
void ec_transform(Vector *signal, Vector *result, unsigned int length)
{
    // Create Matrix
    Matrix mat;
    LINALG.make_sensing_matrix(&mat);

    // Find energy concealment variable 'c'
    FIXED11_21 c;

    int i;
    for (i = 0; i < length - 1; i++)
    {
        c = FP.fp_add(c, FP.fp_pow(signal->data[i], 2));
    }

    FIXED11_21 e_max = FP.float_to_fixed(EMAX);

    c = FP.fp_sqrt(FP.fp_subtract(e_max, c),10);

    //Add c to the signal
    Vector aug_signal;

    aug_signal.data[0] = c;
    for (i = 1; i < length; i++)
    {
        aug_signal.data[i] = signal->data[i - 1];
    }

    // Ax = y From compressed sensing
    LINALG.inner_product(&mat, &aug_signal, result);
}

const struct energy_concealment_driver energy_concealment_driver = {ec_transform};