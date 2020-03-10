#include "./linalg.h"

/* For printf() */
#include <stddef.h>
#include <stdio.h>

static void multiply_sensing_matrix(const Vector *signal, Vector_M *result)
{

    int i, j;

    int16_t sum;

    // printf("here!!\n");
    for (j = 0; j < M; j++)
    {
        // printf("%d\n",j);
        sum = 0;
        for (i = 0; i < N_CS; i++)
        {
            // sum += FP.fp_multiply((RANDOM.get_random_number() << FPART), signal->data[i]);
            // sum += (RANDOM.get_random_number() < 0) ? -signal->data[i] : signal->data[i];
                sum += RANDOM.get_random_number();
            // printf("sum : %.2f \t", FP.fixed_to_float16(rand));
        }
        // printf("\n\n");
        result->data[j] = sum;
    }
}

/**
 * Helper function for printing a vector
 */
static void print_vector(Vector *vec)
{
    int i;
    printf("\n");
    for (i = 0; i < N_CS; i++)
    {
        #if FLOAT
        printf("%.2f\t", FP.fixed_to_float16(vec->data[i]));
        #else
        printf("%08x\t", vec->data[i]);
        #endif
    }
    printf("\n");
}

const struct linalg_driver linalg_driver = {multiply_sensing_matrix, print_vector};