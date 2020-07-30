#ifndef FP_H_
#define FP_H_

#include "contiki.h"
#include "sys/log.h"

#define IPART 4
#define FPART 12
#define FPART_32 16

int32_t fp_sqrt(int32_t a,int iterations);
uint16_t fp_sqrt_fast(uint16_t value);


#endif /* FP_H_ */