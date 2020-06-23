#include "./fixedpoint.h"
#include <inttypes.h>

/**
 * @brief Multiplies two fixed point represented numbers with each other
 * @param a fixed number to be multiplied
 * @param b fixed number to be multiplied
 * @return result of the multiplication
 */
static int16_t fp_multiply(int16_t a, int16_t b)
{
    int16_t result;

    result = (((int32_t)a * (int32_t)b) + (1 << (FPART - 1))) >> FPART;

    #if DEBUG
    if(result > INT16_MAX){
        printf("a : %d, b : %d\n\n", a,b);
        // printf();
        printf("Possible Overflow Error");
    }
    #endif

    return result;
}

static int32_t fp_multiply32(int32_t a, int32_t b)
{
    int32_t result;

    // Compute multiply
    result = (((int64_t)a * (int64_t)b) + (1 << (16 - 1))) >> 16;

    // Saturate the result if over or under minimum value.
    #if DEBUG
    if(result > INT32_MAX){
        printf("POSSIBLE OVERFLOW");
        // tmp = tmp % 0x00010000;
    }
    #endif

    return result;
}
/**
 * @brief Division of FP numbers
 * @param a numinator
 * @param b denominator
 * @return a/b
 */
static int32_t fp_division32(int32_t a, int32_t b)
{
    int64_t result = 0;

    result = (((int64_t)a << 16) + (b >> 1)) / b;
    return (int32_t)result;
}

#if DEBUG && FLOAT
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
 * @brief Coverts a float(double) to a fixed_point double 
 * @param input The input float
 * @return  fixed point reprensentation of a float
 */
static double fixed_to_float32(int32_t input)
{
    double res = 0;
    res = ((double)input / (double)(1 << 16));
    return res;
}

static int32_t float_to_fixed32(double input)
{
    int32_t res;
    res = (int32_t)(input * (1 << 16));
    return res;
}
#endif


/**
 * @brief Newton algorithm implementation of sqrt
 * @param a the number to find the sqrt from
 * @param iterations The number of iterations the newton method runs
 * @result sqrt of a
 */
static int32_t fp_sqrt(int32_t a, int iterations)
{
    #if DEBUG
    LOG_INFO("SQRT called\n");
    #endif
    int32_t result, inter;

    // Initial guess set to 10 
    result = 0xa0000;

    int i;

    for (i = 0; i < iterations; i++)
    {
        inter = result << 1; /* *2 */
        // LOG_INFO("\nresult: %.2f, inter: %.2f", fixed_to_float32(result), fixed_to_float32(inter));
        result -= fp_division32((fp_multiply32(result, result)- a), inter);
    }
    #if DEBUG
    LOG_INFO("\nSQRT completed\n");
    #endif

    return result;
}

#if DEBUG && FLOAT
const struct fixed_point_driver fixed_point_driver = {fp_multiply, fp_sqrt, fixed_to_float16,float_to_fixed16, fixed_to_float32,float_to_fixed32};
#else
const struct fixed_point_driver fixed_point_driver = {fp_multiply, fp_sqrt};
#endif