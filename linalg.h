#ifndef LINALG_H_
#define LINALG_H_

#include "./fixedpoint.h"
#include "./randomGenerator.h"
#include "./cs_config.h"

#define LINALG linalg_driver

// struct Matrix
// {
//   FIXED11_21 data[M][N];
// };

struct Vector
{
  FIXED11_21 data[N];
};

struct Vector_M
{
  FIXED11_21 data[M];
};

// typedef struct Matrix Matrix;
typedef struct Vector Vector;
typedef struct Vector_M Vector_M;


struct linalg_driver
{
  /**
   * \brief Provides a Matrix with psuedo-random values, of size MxN.
   */
  // void (*make_sensing_matrix)(Matrix *mat);

  /**
   * \brief Defines the inner product of a matrix with a Vector
   */
  // void (*inner_product)(Matrix *mat, Vector *vec, Vector_M *ret);
  void (*multiply_sensing_matrix)(Vector *signal, Vector_M *result);

  /* Helper functions*/
  // void (*print_sensing_matrix)(Matrix *mat);
  void (*print_vector)(Vector *vec);
};

extern const struct linalg_driver LINALG;

#endif /* LINALG_H_ */