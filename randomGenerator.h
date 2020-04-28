#ifndef RANDOM_H_
#define RANDOM_H_

#include <inttypes.h>

#define RANDOM random_driver
#define L 3

typedef uint8_t FSR8_t;

typedef uint16_t FSR16_t;

typedef union FSR32_t
{
  uint16_t state[2];
  uint32_t state32;
} FSR32_t;

typedef union FSR64_t
{
  uint16_t state[4];
  uint64_t state64;
} FSR64_t;


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