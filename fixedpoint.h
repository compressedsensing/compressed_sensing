#ifndef FP_H_
#define FP_H_

#include "contiki.h"
#include "sys/log.h"

#define IPART 5
#define FPART 11

int32_t fp_sqrt(int32_t a,int iterations);
uint16_t fp_sqrt_fast(uint16_t value);


#endif /* FP_H_ */