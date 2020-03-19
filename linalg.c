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
            sum += RANDOM.get_random_number() * (signal->data[i] >> 2);
            // sum += FP.fp_multiply(RANDOM.get_random_number(),signal->data[i]);
            // printf("%04x, sum");
        }
        // if(sum > INT16_MAX)
        // {
        // printf("\n\n");
        //    printf("WE HAVE A PROBLEM!");    
        // printf("\n\n");
        // }
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