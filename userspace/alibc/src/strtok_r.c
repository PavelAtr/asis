/******************************************************
*  Author: GitHub Copilot 2025
*******************************************************/
#include <string.h>


char *strtok_r(char* str, const char* delim, char** saveptr) {
    char *token;
    if (str == NULL)
        str = *saveptr;

    // Пропустить начальные разделители
    str += strspn(str, delim);
    if (*str == '\0') {
        *saveptr = str;
        return NULL;
    }

    // Найти конец токена
    token = str;
    str = strpbrk(token, delim);
    if (str) {
        *str = '\0';
        *saveptr = str + 1;
    } else {
        *saveptr = token + strlen(token);
    }
    return token;
}
