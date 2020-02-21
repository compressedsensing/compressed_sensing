#include "./fixedpoint.h"
#include <inttypes.h>
//Relentlessly stolen from: https://www.eetimes.com/fixed-point-math-in-c-2/#

// /**
//  * Helper function that prints a 32-bit fractional bits 
//  */
// static void printBits32(int32_t num)
// {
//     for (int bit = 0; bit < (sizeof(int32_t) * 8); bit++)
//     {
//         printf("%i ", num & 0x01);
//         num = num >> 1;
//     }
// }

// /**
//  * Helper function that prints a 64-bit fractional bits 
//  */
// static void printBits64(int64_t num)
// {
//     for (int bit = 0; bit < (sizeof(int64_t) * 8); bit++)
//     {
//         printf("%li ", num & 0x01);
//         num = num >> 1;
//     }
// }

/**
 * @brief Multiplies two fixed point represented numbers with each other
 * @param a fixed number to be multiplied
 * @param b fixed number to be multiplied
 * @return result of the multiplication
 */
static int16_t fp_multiply(int16_t a, int16_t b)
{
    int32_t tmp;
    int32_t IL;

    int16_t result;

    // Save result in double size
    tmp = (int32_t)a * (int32_t)b;

    // Take out midder section of bits
    tmp = tmp + (1 << (FPART - 1));
    tmp = tmp >> FPART;

    // // Saturate the result if over or under minimum value.
    // if (tmp > INT32_MAX) /* saturate the result before assignment */
    //     Z = INT32_MAX;
    // else if (tmp < INT32_MIN)
    //     Z = INT32_MIN;
    // else

    IL = tmp;

    result = IL;

    return result;
}



/**
 * @brief Converts a fixed point representation number to a double
 * @param input The fixed point value
 * @return float(double) representation of input value
 */


/**
 * @brief Coverts a float(double) to a fixed_point double 
 * @param input The input float
 * @return  fixed point reprensentation of a float
 */
static double fixed_to_float16(int16_t input)
{
    double res = 0;
    res = ((double)input / (double)(1 << FPART));
    return res;
}

static int16_t float_to_fixed16(double input)
{
    int16_t res;
    res = (int16_t)(input * (1 << FPART));
    return res;
}


/**
 * @brief Division of FP numbers
 * @param a numinator
 * @param b denominator
 * @return a/b
 */
static int16_t fp_division(int16_t a, int16_t b)
{

    int32_t tmp = 0;
    int16_t result;

    tmp = (int32_t)a << FPART;
    tmp = tmp + (b >> 1);
    tmp = tmp / b;

    result = (int16_t)tmp;
    return result;
}


/**
 * @brief Newton algorithm implementation of sqrt
 * @param a the number to find the sqrt from
 * @param iterations The number of iterations the newton method runs
 * @result sqrt of a
 */
static int16_t fp_sqrt(int16_t a, int iterations)
{

    int16_t result, inter;

    // Initial guess set to 1
    result = (50 << FPART);
    int i;

    for (i = 0; i < iterations; i++)
    {
        inter = result << 1; /* *2*/
        result -= fp_division((fp_multiply(result, result)- a), inter);
    }

    return result;
}

/**
 * @brief Provides the b'th power of number a
 * @param a Number to get power from
 * @param b The power qoutient
 * @return result of the power
 */
static int16_t fp_pow(int16_t a, int b)
{
    int i;
    int16_t result = a;

    if (b == 0)
    {
        result = (1 << FPART);
        return result;
    }

    for (i = 0; i < b - 1; i++)
    {
        result = fp_multiply(result, a);
    }

    return result;
}

const struct fixed_point_driver fixed_point_driver = {fp_multiply, fp_division, fp_pow, fp_sqrt, fixed_to_float16, float_to_fixed16};