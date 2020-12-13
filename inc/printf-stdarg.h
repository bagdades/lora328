#ifndef  PRINTFSTDARG_INC
#define  PRINTFSTDARG_INC

#include "printf-stdarg.h"
#include "hal.h"
//Prototype functions

int printf(const char *format, ...);
int snprintf( char *buf, unsigned int count, const char *format, ... );
int sprintf(char *out, const char *format, ...);
#endif   /* ----- #ifndef PRINTF-STDARG_INC  ----- */
