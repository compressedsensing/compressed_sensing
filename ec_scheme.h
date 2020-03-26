#ifndef EC_H_
#define EC_H_

#include "contiki.h"
#include <stdio.h>
#include "sys/log.h"

#include "./fixedpoint.h"
#include "./linalg.h"
#include "./cs_config.h"

#define EC energy_concealment_driver

struct energy_concealment_driver
{
    void (* ec_transform)(int16_t* signal);
    #if DEBUG
    void (* pprint)(int16_t* signal);
    #endif
};

extern const struct energy_concealment_driver EC;

#endif /* EC_H_ */