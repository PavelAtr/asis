#ifndef _MATH_H
#define _MATH_H

double sin(double x);
double sqrt(double x);
int isnan(double x);
double log10(double x);
double floor(double x);
double ceil(double x);
double pow(double a, double b);
double fmod(double a, double b);
#define fabs(x) ((x < 0)? -x: x)
double modf(double x, double *iptr);
#endif
