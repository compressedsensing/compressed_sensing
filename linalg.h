#ifndef LINALG_H_
#define LINALG_H_

#include "./fixedpoint.h"
#include "./randomGenerator.h"
#include "./cs_config.h"

#define LINALG linalg_driver

struct Vector
{
  FIXED11_21 data[N];
};

struct Vector_M
{
  FIXED11_21 data[M];
};

typedef struct Vector Vector;
typedef struct Vector_M Vector_M;


struct linalg_driver
{
  /**
   * \brief Defines the inner product of a matrix with a Vector
   */
  void (*multiply_sensing_matrix)(Vector *signal, Vector_M *result);

  /* Helper functions*/
  void (*print_vector)(Vector *vec);
};

extern const struct linalg_driver LINALG;

#endif /* LINALG_H_ */