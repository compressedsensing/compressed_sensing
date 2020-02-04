#ifndef RANDOM_H_
#define RANDOM_H_

#include <inttypes.h>

#define RANDOM random_driver

struct random_driver {
  
  /**
   * \brief Provides a psuedo-random number generator interface
   */
  int32_t (* get_random_number)();

};

extern const struct random_driver RANDOM;

#endif /* RANDOM_H_ */