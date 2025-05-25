#ifndef _MATH_H
#define _MATH_H

double modf(double x, double *iptr);
#define sin(x) 0 /* NOT REALIZED */
#define fabs(x)  (((x) < 0)? -(x): (x))

#endif