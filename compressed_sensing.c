
#include "contiki.h"
#include "math.h"
#include <stddef.h>
#include <stdio.h> /* For printf() */

#define L 5
#define M 3
#define N 3

struct Matrix
{
    int rows;
    int columns;
    float data[M][N];
};

struct Vector
{
    int rows;
    float data[N];
};

struct LFSR
{
    unsigned char state;
    unsigned char polynomiel;
};

struct Generator
{
    struct LFSR registers[L];
};

typedef struct Matrix Matrix;
typedef struct Vector Vector;
typedef struct Generator Generator;
typedef struct LFSR LFSR;

struct LFSR gen[3] =
    {{0b01001100, 0b00000011},
     {0b10001000, 0b01010001},
     {0b10001101, 0b10010011}};

unsigned char getLFSR_bit(struct LFSR *reg);

unsigned char getLFSR_bit(struct LFSR *reg)
{
    unsigned char cs, cp, nbit;
    int i = 0;

    cs = reg->state;

    cp = nbit = cs & reg->polynomiel;

    for (i = 1; i < 8; i++)
    { /* xor all bits together */
        nbit ^= (cp >> i);
    }
    reg->state = (cs >> 1) | (nbit << 7); /*  rotate in new bit */

    // printf("%0.1x", cs & 0x01);
    return cs & 0x01;
}

signed char converter(unsigned char input)
{
    if (input)
    {
        return (-1);
    }
    return 1;
}

float get_random_number(LFSR *gen)
{
    int j;
    signed char sum;

    do
    {
        sum = 0;
        for (j = 0; j < L; j++)
        {
            sum += converter(getLFSR_bit(&gen[j]));
        }
    } while (sum == L);

    return (float)sum;
}

// TODO matrix multiplication

void make_sensing_matrix(Matrix *mat, LFSR *gen)
{
    int i, j;

    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            mat->data[i][j] = get_random_number(gen);
        }
    }
}

// void print_sensing_matrix(Matrix *mat)
// {
//     int i, j;

//     for (i = 0; i < M; i++)
//     {
//         for (j = 0; j < N; j++)
//         {
//             printf("%.2f\t", mat->data[i][j]);
//         }
//         printf("\n");
//     }
// }

void print_vector(float* vec){
    size_t i;
    for (i = 0; i < M; i++)
    {
        printf("%.2f\t", vec[i]);
    }
}

float* inner_product(Matrix *mat, Vector *x, float* ret)
{
    float result[M];
    int j, i;
    float sum;

    for (i = 0; i < M; i++)
    {
        sum = 0;
        for (j = 0; j < N; j++)
        {
            sum += mat->data[i][j] + x->data[j];
        }
        result[i] = sum;
        ret[i] = sum;
        printf("%.2f\t", result[i]);
    }
}

PROCESS(comp_sensing, "compressed");
AUTOSTART_PROCESSES(&comp_sensing);

PROCESS_THREAD(comp_sensing, ev, data)
{
    /* Declare variables required */
    PROCESS_BEGIN();

    // float ans = get_random_number(gen);

    // printf("%.2f\t", ans);

    Matrix mat;

    int i;
    // for (i = 0; i < 5; i++)
    // {
        make_sensing_matrix(&mat, gen);
        // print_sensing_matrix(&mat);
        printf("\n\n");
    // }
    Vector vec = {5.2, 4.2, 6.4};

    float y[M];

    inner_product(&mat,&vec,y);
    print_vector(y);

    /* Process End */
    PROCESS_END();
}