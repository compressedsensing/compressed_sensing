#ifndef RANDOM_H_
#define RANDOM_H_

#include <inttypes.h>

#define RANDOM random_driver

struct random_driver
{

  /**
   * @brief Method to generate a random number, from a pseudorandom generator
   * @return Returns a random number drawn from an LFSR sequence
   */
  int8_t (*get_random_number)();
};

extern const struct random_driver RANDOM;

#endif /* RANDOM_H_ */