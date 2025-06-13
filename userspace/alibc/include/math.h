#ifndef _MATH_H
#define _MATH_H

double modf(double x, double *iptr);
#define sin(x) __builtin_sin(x)
#define sqrt(x) __builtin_sqrt(x)
#define isnan(x) __builtin_isnan(x)
#define fabs(x)  (((x) < 0)? -(x): (x))

#endif