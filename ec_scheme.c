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

    LOG_INFO("PowerLoop\n\n");
    for (i = 1; i < N_CS; i++)
    {
        hep = FP.fp_pow(signal->data[i], 2);

        c += (int32_t)hep << 8;
    }
    LOG_INFO("\nPowerLoop_done\n\n");
    int32_t e_max;
    e_max = 0x00c80000 << 1;
    // printf("e_maks : %08x \n\n",e_max);
    // FP.fixed_to_float16()

    // e_max = FP.float_to_fixed32(EMAX);
    c = e_max - c;
    c = FP.fp_sqrt(c, 20);
    // printf("%2f\t",FP.fixed_to_float(c));

    // c <<= 1;
    // printf("\nC: %2f\t\n",FP.fixed_to_float32(c));
    // printf("%2f\t",FP.fixed_to_float(c));
    // LOG_INFO("\n %.2f\t",FP.fixed_to_float16((int16_t)(c >> 8)));

    //Add c to the signal
    Vector aug_signal;

    // printf("Actual C value %.2f\n\n",FP.fixed_to_float16((int16_t)(c >> 8)));

    aug_signal.data[0] = (int16_t)(c >> 8);
    // aug_signal.data[0] = FP.float_to_fixed16(9.12);
    for (i = 1; i < N_CS; i++)
    {
        aug_signal.data[i] = signal->data[i - 1];
    }

    // LINALG.print_vector(&aug_signal);

    LOG_INFO("C FOUND! \n\n");
    // for (i = 0; i < N; i++)
    // {
    //      printf("%.2f\t", FP.fixed_to_float16(aug_signal.data[i]));
    // }
    // printf("\n\n");

    // printf("\nOverflows are done\n");

    // Ax = y From compressed sensing
    LINALG.multiply_sensing_matrix(&aug_signal, result);
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
        // if (i != M - 1)
        // {
        //     printf(", ");
        // }
    }
    printf("]\n");
}
#endif

#if DEBUG
const struct energy_concealment_driver energy_concealment_driver = {ec_transform, pprint};
#else 
const struct energy_concealment_driver energy_concealment_driver = {ec_transform};
#endif