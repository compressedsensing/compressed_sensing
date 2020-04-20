#include "./linalg.h"

/* For printf() */
// #include <stddef.h>
#include <stdio.h>

static void multiply_sensing_matrix(int16_t *signal)
{
    int16_t i, j;

    int16_t result[M] = {0};

    // Generate first column and base random matrix on that
    int8_t basis[N_CS] = {0};
    for (i = 0; i < N_CS; i++) {
        basis[i] = RANDOM.get_random_number();
    }

    for (i = 0; i < M; i++) {
        // watchdog_periodic();
        for (j = 0; j < N_CS; j++)
        {
            result[i] += basis[(i + j + i*j + i*3*j) % N_CS] * (signal[j] >> 2);
        }
    }
    /* Copy result into signal */
    memset(signal, 0, N_CS * sizeof(int16_t));
    memcpy(signal, result, M * sizeof(int16_t));
}

/**
 * Helper function for printing a vector
 */
static void print_vector(int16_t *vec)
{
    int i;
    printf("\n");
    for (i = 0; i < N_CS; i++)
    {
#if FLOAT
        printf("%.2f\t", FP.fixed_to_float16(vec[i]));
#else
        printf("%08x\t", vec[i]);
#endif
    }
    printf("\n");
}

const struct linalg_driver linalg_driver = {multiply_sensing_matrix, print_vector};