#include "ec_scheme.h"

/**
 * @brief Does compressed sensing with a energy concealment scheme. 
 * @param signal The signal to compress. Should be length N-1
 * @param result The result vector. Should be length M
 * @param length The length of the signal, with the c variable.
 */
void ec_transform(Vector *signal, Vector_M *result)
{
    // Create Matrix
    // Matrix mat;
    // LINALG.make_sensing_matrix(&mat);

    // Find energy concealment variable 'c'

    FIXED11_21 c;
    c.full = 0;

    uint16_t i;
    for (i = 1; i < N; i++)
    {
        c = FP.fp_add(c, FP.fp_pow(signal->data[i], 2));
    }

    FIXED11_21 e_max = FP.float_to_fixed(EMAX);
    // printf("%.2f\t", FP.fixed_to_float(c));

    c = FP.fp_sqrt(FP.fp_subtract(e_max, c), 10);
    // printf("%.2f\n", FP.fixed_to_float(c));

    //Add c to the signal
    Vector aug_signal;

    aug_signal.data[0] = c;
    for (i = 1; i < N; i++)
    {
        aug_signal.data[i] = signal->data[i - 1];
    }

    // LINALG.print_sensing_matrix(&mat);
    // LINALG.print_vector(&aug_signal);
    // Ax = y From compressed sensing
    LINALG.multiply_sensing_matrix(&aug_signal, result);
   

    // LINALG.inner_product(&mat, &aug_signal, &result);
}

// /**
//  * @brief Pretty prints the final output value for a signal
//  * @param signal The signal to pprint
//  * @param length Length of the signal
//  */
// void pprint(Vector_M *signal)
// {
//     int i;
//     printf("\n[");
//     for (i = 0; i < M; i++)
//     {
//         printf("%.2f", FP.fixed_to_float(signal->data[i]));
//         if(i != M-1){
//             printf(", ");
//         }
//     }
//     printf("]\n");
// }

const struct energy_concealment_driver energy_concealment_driver = {ec_transform};
