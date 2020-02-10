#ifndef EC_H_
#define EC_H_

#include "contiki.h"
#include <stdio.h>

#include "./fixedpoint.h"
#include "./linalg.h"
#include "./cs_config.h"

#define EC energy_concealment_driver

struct energy_concealment_driver
{
    void (* ec_transform)(Vector* signal, Vector* result, unsigned int length);
};

extern const struct energy_concealment_driver EC;

#endif /* EC_H_ */