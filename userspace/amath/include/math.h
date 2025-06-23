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



double modf(double x, double *iptr);
float modff(float x, float *iptr);
long double modfl(long double x, long double *iptr);

double round(double x);
float roundf(float x);
long double roundl(long double x);

double fabs(double x);
float fabsf(float x);
long double fabsl(long double x);

float powf(float x, float y);
long double powl(long double x, long double y);

float sqrtf(float x);
long double sqrtl(long double x);

int signbit(x);

double rint(double x);
float rintf(float x);
long double rintl(long double x);


#define HUGE_VALF (__builtin_huge_valf ())
#define HUGE_VALL (__builtin_huge_vall ())
#define INFINITY HUGE_VALF
#define NAN (__builtin_nanf (""))


#endif
