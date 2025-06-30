/******************************************************
*  Author: Pavel V Samsonov 2025
*******************************************************/

#ifndef _MATH_H
#define _MATH_H

#define HUGE_VALF (__builtin_huge_valf ())
#define HUGE_VALL (__builtin_huge_vall ())
#define INFINITY HUGE_VALF
#define NAN (__builtin_nanf (""))

# define M_PI           3.14159265358979323846
# define M_PI_2         1.57079632679489661923
# define M_PI_4         0.78539816339744830962
# define M_1_PI         0.31830988618379067154  /* 1/pi */
# define M_2_PI         0.63661977236758134308  /* 2/pi */
# define M_2_SQRTPI     1.12837916709551257390  /* 2/sqrt(pi) */
# define M_SQRT2        1.41421356237309504880  /* sqrt(2) */
# define M_SQRT1_2      0.70710678118654752440  /* 1/sqrt(2) */


double sin(double x);
#define sinf (float)sin((double) x)
#define sinl (long double)sin((double) x)

#define cos(x) sin(x + M_PI_2)
#define cosf(x) (float) cos((double) x)
#define cosl(x) (long double) cos((double) x)

double sqrt(double x);
#define sqrtf(x) (float) sqrt((double) x)
#define sqrtl(x) (long double) sqrt((double) x)

double pow(double a, double b);
#define powf(a, b) (float) pow((double) x, (double) y)
#define powl(a, b) (long double) pow((double) x, (double) y)

double fmod(double a, double b);
#define fmodf(x, y) (float) fmod((double) x, (double) y)
#define fmodl(x, y) (long double) fmod((double) x, (double) y)

double modf(double x, double *iptr);
#define modff(x, iptr) (float) modf((double) x, (double *) iptr)
#define modfl(x, iptr) (long double) modf((double) x, (double *) iptr)

double round(double x);
#define roundf(x) (float) round((double) x)
#define roundl(x) (long double) round((double) x)

double fabs(double x);
#define fabsf(x) (double) fabs((double) x)
#define fabsl(x) (long double) fabs((double) x)

double rint(double x);
#define runtf(x) (float) rint((double) x)
#define rintl(x) (double) rint((double) x)

double hypot(double x, double y);
#define hypotf(x, y) (float) hypot((double) x, (double) y)
#define hypotl(x, y) (long double) hypot((double) x, (double) y)

double atan2(double y, double x);
#define atan2f (float) atan2((double) y, (double) x)
#define atan2l (long double) atan2((double) y, (double) x)

double log10(double x);
double floor(double x);
double ceil(double x);

int isnan(double x);
int signbit(x);
int fpclassify(x);
int isfinite(x);
int isnormal(x);
int isinf(x);


#endif
