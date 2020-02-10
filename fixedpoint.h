#ifndef FP_H_
#define FP_H_

#include "contiki.h"
#include <stdio.h>

#define FP fixed_point_driver
#define IPART 11
#define FPART 21

typedef union FIXED11_21tag {
    int32_t full;
    struct part11_21tag
    {
        int32_t fraction : 21;
        int32_t integer : 11;
    } part;
} FIXED11_21;

struct fixed_point_driver
{
    FIXED11_21(* fp_multiply)(FIXED11_21 a, FIXED11_21 b);
    FIXED11_21(* fp_division)(FIXED11_21 a, FIXED11_21 b);
    FIXED11_21(* fp_add)(FIXED11_21 a, FIXED11_21 b);
    FIXED11_21(* fp_subtract)(FIXED11_21 a, FIXED11_21 b);
    FIXED11_21(* fp_pow)(FIXED11_21 a, int b);
    FIXED11_21(* fp_sqrt)(FIXED11_21 a,int iterations);
    /* Helpers */
    double (* fixed_to_float)(FIXED11_21 input);
    FIXED11_21 (* float_to_fixed)(double input);
};


extern const struct fixed_point_driver FP;

#endif /* FP_H_ */