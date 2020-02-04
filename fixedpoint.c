#include "./fixedpoint.h"
#include <inttypes.h>
//Relentlessly stolen from: https://www.eetimes.com/fixed-point-math-in-c-2/#

/**
 * Helper function that prints a 32-bit fractional bits 
 */
static void printBits32(int32_t num)
{
    for (int bit = 0; bit < (sizeof(int32_t) * 8); bit++)
    {
        printf("%i ", num & 0x01);
        num = num >> 1;
    }
}

/**
 * Helper function that prints a 64-bit fractional bits 
 */
static void printBits64(int64_t num)
{
    for (int bit = 0; bit < (sizeof(int64_t) * 8); bit++)
    {
        printf("%li ", num & 0x01);
        num = num >> 1;
    }
}

/**
 * @brief Multiplies two fixed point represented numbers with each other
 * @param a fixed number to be multiplied
 * @param b fixed number to be multiplied
 * @return result of the multiplication
 */
static FIXED11_21 fp_multiply(FIXED11_21 a, FIXED11_21 b)
{
    int64_t tmp, Z;
    FIXED11_21 result;

    //Save result in double size
    tmp = (int64_t)a.full * (int64_t)b.full;

    //Take out midder section of bits
    tmp = tmp + (1 << 20);
    tmp = tmp >> 21;

    //Saturate the result if over or under minimum value.
    if (tmp > INT32_MAX) /* saturate the result before assignment */
        Z = INT32_MAX;
    else if (tmp < INT32_MIN)
        Z = INT32_MIN;
    else
        Z = tmp;

    result.full = Z;

    return result;
}

/**
 * @brief Multiplies two fixed point represented numbers with each other
 * @param a fixed number to be multiplied
 * @param b fixed number to be multiplied
 * @return result of the multiplication
 */
static FIXED11_21 fp_add(FIXED11_21 a, FIXED11_21 b)
{
    FIXED11_21 result;

    result.full = a.full + b.full; /* Has a risk of overflowing */

    return result;
}

/**
 * @brief Converts a fixed point representation number to a double
 * @param input The fixed point value
 * @return float(double) representation of input value
 */
static double fixed_to_float(FIXED11_21 input)
{
    double res = 0;
    res = ((double)input.full / (double)(1 << 21));
    return res;
}

/**
 * @brief Coverts a float(double) to a fixed_point double 
 * @param input The input float
 * @return  fixed point reprensentation of a float
 */
static FIXED11_21 float_to_fixed(double input)
{
    FIXED11_21 res;
    res.full = (int32_t)(input * (1 << 21));
    return res;
}

const struct fixed_point_driver fixed_point_driver = {fp_multiply, fp_add, fixed_to_float, float_to_fixed};