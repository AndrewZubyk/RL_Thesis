/* tmwtypes.h - Fixed */
#ifndef TMWTYPES_H
#define TMWTYPES_H

#include <limits.h>

/* Basic Types */
typedef int             int_T;
typedef unsigned int    uint_T;
typedef unsigned long   ulong_T;
typedef unsigned char   boolean_T;
typedef char            char_T;
typedef signed char     int8_T;
typedef unsigned char   uint8_T;
typedef short           int16_T;
typedef unsigned short  uint16_T;
typedef int             int32_T;
typedef unsigned int    uint32_T;
typedef float           real32_T;
typedef double          real_T;
typedef double          time_T;
typedef unsigned char   uchar_T;
typedef unsigned char   byte_T;

/* Complex Types */
typedef struct {
  real32_T re;
  real32_T im;
} creal32_T;

typedef struct {
  real_T re;
  real_T im;
} creal_T;

#endif /* TMWTYPES_H */