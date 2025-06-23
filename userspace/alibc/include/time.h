#ifndef _TIME_H
#define _TIME_H

#include <sys/types.h>
#include <sys/time.h>
#include <sys/times.h>

struct timespec {
   time_t     tv_sec;   /* Seconds */
   time_t  tv_nsec;  /* Nanoseconds [0, 999'999'999] */
};

struct itimerspec {
        struct timespec it_interval;/* timer period */
        struct timespec it_value;       /* timer expiration */
};

struct itimerval {
        struct timeval it_interval;/* timer interval */
        struct timeval it_value;        /* current value */
};

int nanosleep(const struct timespec *req, struct timespec* rem);
int clock_gettime(clockid_t clockid, struct timespec *tp);
/*
 * Names of the interval timers, and structure
 * defining a timer setting:
 */
#define ITIMER_REAL             0
#define ITIMER_VIRTUAL          1
#define ITIMER_PROF             2

/*
 * The IDs of the various system clocks (for POSIX.1b interval timers):
 */
#define CLOCK_REALTIME                  0
#define CLOCK_MONOTONIC                 1
#define CLOCK_PROCESS_CPUTIME_ID        2
#define CLOCK_THREAD_CPUTIME_ID         3
#define CLOCK_MONOTONIC_RAW             4
#define CLOCK_REALTIME_COARSE           5
#define CLOCK_MONOTONIC_COARSE          6
#define CLOCK_BOOTTIME                  7
#define CLOCK_REALTIME_ALARM            8
#define CLOCK_BOOTTIME_ALARM            9

struct tm {
  int         tm_sec;    /* Seconds          [0, 60] */
  int         tm_min;    /* Minutes          [0, 59] */
  int         tm_hour;   /* Hour             [0, 23] */
  int         tm_mday;   /* Day of the month [1, 31] */
  int         tm_mon;    /* Month            [0, 11]  (January = 0) */
  int         tm_year;   /* Year minus 1900 */
  int         tm_wday;   /* Day of the week  [0, 6]   (Sunday = 0) */
  int         tm_yday;   /* Day of the year  [0, 365] (Jan/01 = 0) */
  int         tm_isdst;  /* Daylight savings flag */
  long        tm_gmtoff; /* Seconds East of UTC */
  const char *tm_zone;   /* Timezone abbreviation */
};

typedef long timezone_t; /* UNREALIZED */

time_t time(time_t* tloc);
time_t mktime(struct tm *tm);
time_t mktime_z(timezone_t tz, struct tm* tm);
size_t strftime(char* s, size_t max, const char* format, const struct tm* tm);
struct tm *localtime(const time_t *timep);
struct tm *localtime_r(const time_t* timep, struct tm* result);
struct tm* localtime_rz(timezone_t tz, const time_t* timep, struct tm* tm);
char *strptime(const char* s, const char* format,  struct tm* tm);

void tzset(void);
extern char *tzname[2];
extern long timezone;
extern int daylight;

char *asctime(const struct tm *tm);
char *asctime_r(const struct tm * tm, char buf[]);
char *ctime(const time_t *timep);
char *ctime_r(const time_t * timep,char buf[]);
struct tm *gmtime(const time_t *timep);
struct tm *gmtime_r(const time_t * timep, struct tm * result);
int timespec_get(struct timespec* ts, int base);

clock_t clock(void);

timezone_t tzalloc(const char* id);
void tzfree(timezone_t tz);
timezone_t set_tz(timezone_t tz);
#define CLOCKS_PER_SEC 8000000
int clock_nanosleep(clockid_t clockid, int flags,
                           const struct timespec *request,
                           struct timespec * remain);

#endif
