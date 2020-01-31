#include "./fixedpoint.h"
#include <inttypes.h>
//Relentlessly stolen from: https://www.eetimes.com/fixed-point-math-in-c-2/#

static void fp_print(FIXED11_21 fp)
{
    printf("%d.%d\n", fp.part.integer, fp.part.fraction);
}

void printBits(int32_t num)
{
    for (int bit = 0; bit < (sizeof(int32_t) * 8); bit++)
    {
        printf("%i ", num & 0x01);
        num = num >> 1;
    }
}

void printBits64(int64_t num)
{
    for (int bit = 0; bit < (sizeof(int64_t) * 8); bit++)
    {
        printf("%i ", num & 0x01);
        num = num >> 1;
    }
}

static FIXED11_21 fp_multiply(FIXED11_21 a, FIXED11_21 b)
{

    int64_t tmp;
    FIXED11_21 result;

    tmp = (int64_t)a.full * (int64_t)b.full;

    // printf("%" PRId64 "\n", tmp);
    // printBits64((int64_t)a.full);
    // printBits(a.full);
    // printf("\n");
    // printBits(b.full);
    // printf("\n");

    // printBits(a.full);
    tmp = tmp + (1 << 20);
    tmp = tmp >> 21;
    // printf("%" PRId64 "\n", tmp);

    // if (tmp > INT8_MAX) /* saturate the result before assignment */
    //     Z = INT8_MAX;
    // else if (temp < INT8_MIN)
    //     Z = INT8_MIN;
    // else
    //     Z = temp;

    result.full = tmp;

    fp_print(result);

    return result;
}

const struct fixed_point_driver fixed_point_driver = {fp_multiply, fp_print};