#include "./linalg.h"

/* For printf() */
#include <stddef.h>
#include <stdio.h>

// /**
//  * @brief Create matrix with gaussian distribution from psudorandom generator
//  * @param mat pointer to the matrix
//  * @param gen pointer to the random number generator.
//  */
// static void make_sensing_matrix(Matrix *mat)
// {
//     int i, j;

//     for (i = 0; i < M; i++)
//     {
//         for (j = 0; j < N; j++)
//         {
//             int32_t rand = RANDOM.get_random_number();
//             mat->data[i][j].part.integer = rand;
//             mat->data[i][j].part.fraction = 0;
//         }
//     }
// }

// /**
//  * @brief Calculates the inner product of a Matrix and a vector (Matrix multiplication)
//  * @param mat pointer to the matrix
//  * @param vec pointer to the vector
//  * @param ret pointer to the vector that has the return value
//  */
// static void inner_product(Matrix *mat, Vector *vec, Vector_M *ret)
// {
//     int j, i;
//     FIXED11_21 sum;

//     // printf("\n");
//     for (i = 0; i < M; i++)
//     {
//         sum.full = 0;
//         for (j = 0; j < N; j++)
//         {
//             sum = FP.fp_add(sum, FP.fp_multiply(mat->data[i][j], vec->data[j]));
//             // printf("%.2f\t", FP.fixed_to_float(sum));
//         }
//         // printf("\n");
//         ret->data[i] = sum;
//     }
// }

static void multiply_sensing_matrix(Vector *signal, Vector_M *result)
{

    int i, j;

    FIXED11_21 rand, sum;
    rand.full = 0;

    for (j = 0; j < M; j++)
    {
        sum.full = 0;
        for (i = 0; i < N; i++)
        {
            rand.part.integer = RANDOM.get_random_number();
            sum = FP.fp_add(sum, FP.fp_multiply(rand, signal->data[i]));
        }
        printf("%d\n", j);
        result->data[j] = sum;
    }

    return result;
}

// /**
//  * Helper function for printing sensing matrices
//  */
// static void print_sensing_matrix(Matrix *mat)
// {
//     int i, j;

//     printf("\n");
//     for (i = 0; i < M; i++)
//     {
//         for (j = 0; j < N; j++)
//         {
//             printf("%.2f\t", FP.fixed_to_float(mat->data[i][j]));
//         }
//         printf("\n");
//     }
// }

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

const struct linalg_driver linalg_driver = { multiply_sensing_matrix,print_vector};