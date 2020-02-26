#ifndef FP_H_
#define FP_H_

#include "contiki.h"
#include <stdio.h>
#include "./cs_config.h"
#include "sys/log.h"

#define FP fixed_point_driver
#define IPART 8
#define FPART 8

struct fixed_point_driver
{
    int16_t(* fp_multiply)(int16_t a, int16_t b);
    int16_t(* fp_division)(int16_t a, int16_t b);
    // FIXED11_21(* fp_add)(FIXED11_21 a, FIXED11_21 b);
    // FIXED11_21(* fp_subtract)(FIXED11_21 a, FIXED11_21 b);
    int16_t(* fp_pow)(int16_t a, int b);
    int32_t(* fp_sqrt)(int32_t a,int iterations);
    /* Helpers */
    #if DEBUG && FLOAT
    double (*fixed_to_float16)(int16_t input);
    int16_t (*float_to_fixed16)(double input);
    double (*fixed_to_float32)(int32_t input);
    int32_t (*float_to_fixed32)(double input);
    #endif
};


extern const struct fixed_point_driver FP;

#endif /* FP_H_ */