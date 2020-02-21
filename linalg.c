#include "./linalg.h"

/* For printf() */
#include <stddef.h>
#include <stdio.h>

static void multiply_sensing_matrix(Vector *signal, Vector_M *result)
{

    int i, j;

    int16_t rand, sum;
    rand = 0;

    // printf("here!!\n");
    for (j = 0; j < M; j++)
    {
        // printf("%d\n",10);
        sum = 0;
        for (i = 0; i < N; i++)
        {
            rand = (RANDOM.get_random_number() << FPART);
            sum += FP.fp_multiply(rand, signal->data[i]);
        }
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
    for (i = 0; i < N; i++)
    {
        printf("%.2f\t", FP.fixed_to_float16(vec->data[i]));
    }
    printf("\n");
}

const struct linalg_driver linalg_driver = {multiply_sensing_matrix, print_vector};