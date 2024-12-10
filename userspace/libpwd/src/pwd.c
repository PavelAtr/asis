#include <pwd.h>

char buf[MAXPWDLINE];
FILE* dbpasswd = NULL;
struct passwd pass;
struct passwd* p;

