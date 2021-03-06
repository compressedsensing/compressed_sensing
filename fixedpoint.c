#include "./fixedpoint.h"
#include <inttypes.h>

/**
 * @brief Multiplies two fixed point represented numbers with each other
 * @param a fixed number to be multiplied
 * @param b fixed number to be multiplied
 * @return result of the multiplication
 */
int16_t fp_multiply(int16_t a, int16_t b)
{
    int32_t result;
    int16_t out;

    result = (int32_t) a * b;
    result = result >> FPART;
    out = result;
    return out;
}

int32_t fp_multiply32(int32_t a, int32_t b)
{
    int64_t result;
    int32_t out;
    result = (int64_t)a * (int64_t)b;
    result += 1L << (FPART_32 - 1);
    result = result >> FPART_32;
    out = result;

    return out;
}
/**
 * @brief Division of FP numbers
 * @param a numinator
 * @param b denominator
 * @return a/b
 */
int32_t fp_division32(int32_t a, int32_t b)
{
    int64_t result = 0;

    result = (((int64_t)a << FPART_32) + (b >> 1)) / b;
    return (int32_t)result;
}


/**
 * @brief Newton algorithm implementation of sqrt
 * @param a the number to find the sqrt from
 * @param iterations The number of iterations the newton method runs
 * @result sqrt of a
 */
int32_t fp_sqrt(int32_t a, int iterations)
{
    int32_t result = 0xa0000, inter;
    uint8_t i;

    for (i = 0; i < iterations; i++) {
        inter = result << 1; /* *2 */
        result -= fp_division32((fp_multiply32(result, result)- a), inter);
    }
    return result;
}

uint16_t fp_sqrt_fast(uint16_t value)
{
    uint16_t root = 0;
    uint16_t bit;
    for ( bit = 0x4000; bit > 0; bit >>= 2 ) {
        uint16_t trial = root + bit;
        root >>= 1;
        if (trial <= value ) {
            root += bit;
            value -= trial;
        }
    }
    return root;
}