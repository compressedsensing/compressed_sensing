#ifndef CS_CONF_H_
#define CS_CONF_H_

#define M 260
#define N_CS 512
#define EMAX 400
#ifndef LOG_MODULE
#define LOG_MODULE "compressed_sensing"
#define LOG_LEVEL LOG_LEVEL_INFO
// #define LOG_LEVEL LOG_LEVEL_NONE
#endif

#ifndef FLOAT
#define FLOAT 0
#endif

#ifndef DEBUG
#define DEBUG 1
#endif

#ifndef NATIVE
#define NATIVE 0
#endif

#endif /* CS_CONF_H_ */