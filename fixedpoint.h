#ifndef FP_H_
#define FP_H_

#include "contiki.h"

#define FP fixed_point_driver

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
    void (* fp_print)(FIXED11_21 fp);
};

extern const struct fixed_point_driver FP;

#endif /* FP_H_ */