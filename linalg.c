
#include "./linalg.h"
#include "./randomGenerator.h"

/* For printf() */
#include <stddef.h>
#include <stdio.h> 

/**
 * @brief Create matrix with gaussian distribution from psudorandom generator
 * @param mat pointer to the matrix
 * @param gen pointer to the random number generator.
 */
static void make_sensing_matrix(Matrix *mat)
{
    int i, j;

    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            mat->data[i][j] = RANDOM.get_random_number();
        }
    }
}

/**
 * @brief Calculates the inner product of a Matrix and a vector (Matrix multiplication)
 * @param mat pointer to the matrix
 * @param vec pointer to the vector
 * @param ret pointer to the vector that has the return value
 */
static void inner_product(Matrix *mat, Vector *vec, Vector *ret)
{
    float result[M];
    int j, i;
    float sum;

    for (i = 0; i < M; i++)
    {
        sum = 0;
        for (j = 0; j < N; j++)
        {
            sum += mat->data[i][j] + vec->data[j];
        }
        result[i] = sum;
        ret->data[i] = sum;
    }
}

/**
 * Helper function for printing sensing matrices
 */
static void print_sensing_matrix(Matrix *mat)
{
    int i, j;

    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%016u\t", mat->data[i][j]);
        }
        printf("\n");
    }
}

/**
 * Helper function for printing a vector
 */
static void print_vector(float *vec)
{
    int i;
    for (i = 0; i < M; i++)
    {
        printf("%.2f\t", vec[i]);
    }
}

const struct linalg_driver linalg_driver = {make_sensing_matrix, inner_product, print_sensing_matrix, print_vector};