#include "./linalg.h"

/* For printf() */
#include <stddef.h>
#include <stdio.h>

static void multiply_sensing_matrix(Vector *signal, Vector_M *result)
{

    int i, j;

    FIXED11_21 rand, sum;
    rand.full = 0;

    // printf("here!!\n");
    for (j = 0; j < M; j++)
    {
        // printf("%d\n",10);
        sum.full = 0;
        for (i = 0; i < N; i++)
        {
            rand.part.integer = RANDOM.get_random_number();
            rand.part.fraction = 0;
            sum = FP.fp_add(sum, FP.fp_multiply(rand, signal->data[i]));
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
        printf("%.2f\t", FP.fixed_to_float(vec->data[i]));
    }
    printf("\n");
}

const struct linalg_driver linalg_driver = {multiply_sensing_matrix, print_vector};