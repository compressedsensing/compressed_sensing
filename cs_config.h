#ifndef CS_CONF_H_
#define CS_CONF_H_

#define BLOCK_LEN M*2
#define N_CS 1024
#define N_PRIME 256 // N should be greater than or equal 256
#define M 512
#define M_PRIME (M/(N_CS/N_PRIME))
// #define EMAX 0x13000000 /* */
// #define EMAX 0x79365106 // EMAX Q.8.24 for N=1024 >> 2
// #define EMAX 0x3931DA80// EMAX Q.8.24 for N=768 >> 2
// #define EMAX 0x2DF2B440 // EMAX Q.8.24 for N=512 >> 2
// #define EMAX 0x1BF499C0 // EMAX Q.8.24 for N=256 >> 2
#define EMAX 23488102 // EMAX Q.8.24 and Q.3.13 for N=256 >> 1
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