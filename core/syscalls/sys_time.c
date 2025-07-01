/******************************************************
*  Author: GitHub Copilot 2025
*  Author: Pavel V Samsonov 2025
*******************************************************/

#include "../../config.h"
#include "sys/types.h"

#ifdef CONFIG_LINUX
#include <sys/time.h>
#include <time.h>
#endif

#ifdef CONFIG_UEFI
#include "../uefi/uefi.h" 
struct timespec {
   time_t     tv_sec;   /* Seconds */
   time_t  tv_nsec;  /* Nanoseconds [0, 999'999'999] */
};
#endif

#ifdef CONFIG_LINUX

errno_t sys_clock_gettime(struct timespec *tp) {
    // На Linux используем системный вызов
    return clock_gettime(CLOCK_REALTIME, tp);
}
#endif

#ifdef CONFIG_UEFI
errno_t sys_clock_gettime(struct timespec *tp) {
    efi_time_t EfiTime;
    efi_status_t Status = ST->RuntimeServices->GetTime(&EfiTime, NULL);
    if (EFI_ERROR(Status))
        return -1;

    // Преобразуем EFI_TIME в timespec (UTC)
    tp->tv_sec =
        (EfiTime.Year - 1970) * 31556952 +
        (EfiTime.Month - 1) * 2629746 +
        (EfiTime.Day - 1) * 86400 +
        EfiTime.Hour * 3600 +
        EfiTime.Minute * 60 +
        EfiTime.Second;
    tp->tv_nsec = EfiTime.Nanosecond;
    return 0;
}
#endif

#ifdef CONFIG_LINUX

errno_t sys_clock_settime(const struct timespec *tp) {
    // На Linux используем системный вызов
    return clock_settime(CLOCK_REALTIME, tp);
}
#endif

#ifdef CONFIG_UEFI
// Проверка високосного года
static int is_leap(int year) {
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

// Количество дней в каждом месяце (невисокосный год)
static const int days_in_month[12] = {
    31,28,31,30,31,30,31,31,30,31,30,31
};

// Преобразование time_t в EFI_TIME (UTC)
static void time_t_to_efi_time(time_t t, long nsec, efi_time_t *efi) {
    int year = 1970;
    int month = 0;
    int day;
    int days;

    // Считаем количество дней с 1970 года
    days = t / 86400;
    t %= 86400;

    // Определяем год
    while (1) {
        int ydays = is_leap(year) ? 366 : 365;
        if (days >= ydays) {
            days -= ydays;
            year++;
        } else {
            break;
        }
    }

    // Определяем месяц
    for (month = 0; month < 12; ++month) {
        int mdays = days_in_month[month];
        if (month == 1 && is_leap(year)) mdays++; // февраль в високосный год
        if (days >= mdays) {
            days -= mdays;
        } else {
            break;
        }
    }

    day = days + 1;

    efi->Year        = year;
    efi->Month       = month + 1;
    efi->Day         = day;
    efi->Hour        = t / 3600;
    efi->Minute      = (t % 3600) / 60;
    efi->Second      = t % 60;
    efi->Nanosecond  = nsec;
    efi->TimeZone    = 0;
    efi->Daylight    = 0;
    efi->Pad1        = 0;
    efi->Pad2        = 0;
}

// clock_settime для UEFI
errno_t sys_clock_settime(const struct timespec *tp) {

    efi_time_t EfiTime;
    time_t_to_efi_time(tp->tv_sec, tp->tv_nsec, &EfiTime);

    efi_status_t Status = ST->RuntimeServices->SetTime(&EfiTime);
    return EFI_ERROR(Status) ? -1 : 0;
}

#endif
