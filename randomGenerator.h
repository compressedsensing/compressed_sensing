#ifndef RANDOM_H_
#define RANDOM_H_

#define RANDOM random_driver

struct random_driver {
  
  /**
   * \brief Provides a psuedo-random number generator interface
   */
  float (* get_random_number)();

};

extern const struct random_driver RANDOM;

#endif /* RANDOM_H_ */