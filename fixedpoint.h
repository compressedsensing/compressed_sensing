#ifndef FP_H_
#define FP_H_

#include "contiki.h"
#include "sys/log.h"

#define FP fixed_point_driver
#define IPART 8
#define FPART 8

struct fixed_point_driver
{
    int16_t(* fp_multiply)(int16_t a, int16_t b);
    int32_t(* fp_sqrt)(int32_t a,int iterations);
    uint16_t(* fp_sqrt_fast)(uint16_t value);
};


extern const struct fixed_point_driver FP;

#endif /* FP_H_ */