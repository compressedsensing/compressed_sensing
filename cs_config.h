#ifndef CS_CONF_H_
#define CS_CONF_H_

#define BLOCK_LEN M*2
#define N_CS 1024
#define N_PRIME 256 // N should be greater than or equal 256
#define M 360
#define M_PRIME (M/(N_CS/N_PRIME))
#define EMAX 0x13000000 /* */
#ifndef LOG_MODULE
#define LOG_MODULE "compressed_sensing"
#define LOG_LEVEL LOG_LEVEL_INFO
// #define LOG_LEVEL LOG_LEVEL_NONE
#endif

// Utility macros
#define CEIL_DIVIDE(x,y) ((x+y-1)/y) /* x -Input, y - Divisor*/

#ifndef DEBUG
#define DEBUG 1
#endif

#endif /* CS_CONF_H_ */