#ifndef LIB_H
#define LIB_H

#include <stdint.h>
#include <stddef.h>

double fabs(double x);

char* itoa(int value, char* str, int base);

char* ftoa(float value, char* str);

char* utoa(unsigned int value, char* str, int base);

#endif