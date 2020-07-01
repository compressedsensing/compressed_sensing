#include "./linalg.h"

/* For printf() */
// #include <stddef.h>
#include <stdio.h>

static void multiply_sensing_matrix(int16_t *signal)
{
    uint16_t i, j;
    int16_t result[M] = {0};
    // int8_t basis[N_CS] = {0};
    // uint16_t start = 0;

    #if DEBUG
    uint16_t time = clock_time();
    #endif

    // Generate first two column and base random matrix on that
    for (j = 0; j < M; j++)
    {
        watchdog_periodic();
        result[j] = 0;

        for (i = 0; i < N_CS; i++)
        {
            result[j] += RANDOM.get_random_number() * (signal[i] >> 2);
        }
    }

    #if DEBUG
    time = clock_time() - time;
    LOG_INFO("Sensing matrix generation time: %u\n", time);
    #endif

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