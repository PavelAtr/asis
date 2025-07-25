#ifndef _MATH_H
#define _MATH_H

#define HUGE_VALF (__builtin_huge_valf ())
#define HUGE_VALL (__builtin_huge_vall ())
#define INFINITY HUGE_VALF
#define NAN (__builtin_nanf (""))
# define M_PI           3.14159265358979323846
# define M_PI_2         1.57079632679489661923
# define M_PI_4         0.78539816339744830962


double sin(double x);
#define sinf (float)sin((float) x)
#define sinl (long double)sin((long double) x)

#define cos(x) sin(x + M_PI_2)
#define cosf(x) (float) cos((float) x)
#define cosl(x) (long double) cos((long double) x)

double sqrt(double x);
#define sqrtf(x) (float) sqrt((float) x)
#define sqrtl(x) (long double) sqrt((long double) x)

double pow(double a, double b);
#define powf(a, b) (float) pow((float) x, (float) y)
#define powl(a, b) (long double) pow((long double) x, (long double) y)

double fmod(double a, double b);
#define fmodf(x, y) (float) fmod((float) x, (float) y)
#define fmodl(x, y) (long double) fmod((long double) x, (long double) y)

double log10(double x);
double floor(double x);
double ceil(double x);


int isnan(double x);









double modf(double x, double *iptr);
#define modff(x, iptr) (float) modf((float) x, (float *) iptr)
#define modfl(x, iptr) (long double) modf((long double) x, (long double *) iptr)

double round(double x);
#define roundf(x) (float) round((float) x)
#define roundl(x) (long double) round((long double) x)

double fabs(double x);
#define fabsf(x) (float) fabs((float) x)
#define fabsl(x) (long double) fabs((long double) x)

double rint(double x);
float rintf(float x);
long double rintl(long double x);


int signbit(x);
int fpclassify(x);
int isfinite(x);
int isnormal(x);
int isinf(x);


#endif
