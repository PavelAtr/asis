#ifndef _STDIO_H
#define _STDIO_H

#include <stddef.h>
#include <stdarg.h>
#include <sys/types.h>

#define MAXPIPE 512

typedef struct {
   char buf[MAXPIPE];
   unsigned short nlink;
   unsigned short writepos;
   unsigned short readpos;
} pipebuf;

typedef struct {
   char* file;
   size_t size;
   size_t pos;
   const char* mode;
   int flags;
   int fd;
   pid_t pgrp;
   char* strbuf;
   pipebuf* pipbuf;
   int fdflags;
} FILE;

typedef FILE AFILE;

extern FILE*** core_fds;
#define fds (*core_fds)
#define stdin (*core_fds)[0]
#define stdout (*core_fds)[1]
#define stderr (*core_fds)[2]
#define INIT_FDS
void initfile(FILE* src);
void copyfile(FILE* dst, FILE* src);
void freefile(FILE* dst);

#define FILE_ERROR 0x01
#define FILE_INFINITY 0x02

#define MAXSTRING ((unsigned short)-1)

FILE* fopen(const char* pathname, const char* mode);
FILE *freopen(const char* pathname, const char* mode,
     FILE* stream);
FILE *fdopen(int fd, const char *mode);
size_t fread(void* ptr, size_t size, size_t nmemb, FILE* stream);
size_t fwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream);
size_t freadall(void* ptr, size_t size, size_t nmemb, FILE* stream);
size_t fwriteall(const void* ptr, size_t size, size_t nmemb, FILE* stream);
int fclose(FILE *stream);
int fseek(FILE* stream, long offset, int whence);
long ftell(FILE* stream);
int fseeko(FILE *stream, off_t offset, int whence);
off_t ftello(FILE *stream);
void rewind(FILE* stream);
int fgetc(FILE* stream);
int getchar(void);
#define getc(f) fgetc(f)
int fputs(const char* s, FILE* stream);
int puts(const char* s);
int putchar(int c);
int fputc(int c, FILE *stream);
#define putc(c, s) fputc(c, s)
int putchar(int c);
int vsnprintf(char* str, size_t size,  const char* format, va_list ap);
int snprintf(char* str, size_t size, const char* format, ...);
int fprintf(FILE* stream, const char* format, ...);
void clearerr(FILE *stream);
int feof(FILE *stream);
int ferror(FILE *stream);
int vfprintf(FILE* stream, const char* format, va_list ap);
#define vprintf(format, ap) vfprintf(stdout, format, ap)
int vsprintf(char* str, const char* format, va_list ap);
char *fgets(char* s, int size, FILE* stream);
int vsscanf(const char* str, const char* format, va_list ap);
int sscanf(const char* str, const char* format, ...);
int fscanf(FILE* stream, const char* format, ...);
int ungetc(int c, FILE *stream);
size_t fstrread(void* ptr, size_t size, size_t nmemb, FILE* stream);
size_t fstrwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream);
void flockfile(FILE *filehandle);
int ftrylockfile(FILE *filehandle);
void funlockfile(FILE *filehandle);
#define MAXGETLINE 4096
char * fgetln (FILE *stream, size_t *len);
ssize_t getline(char** lineptr, size_t* n, FILE* stream);
ssize_t getdelim(char** lineptr, size_t* n, int delim, FILE* stream);
int printf(const char* format, ...);
int sprintf(char* str, const char* format, ...);
int dprintf(int fd, const char* format, ...);
int fflush(FILE *stream);
int fileno(FILE *stream);
int rename(const char *oldpath, const char *newpath);

#define EOF -1

#define _IOFBF 0                /* Fully buffered.  */
#define _IOLBF 1                /* Line buffered.  */
#define _IONBF 2                /* No buffering.  */

int setvbuf(FILE* stream, char* buf, int mode, size_t size);
void setbuf(FILE* stream, char* buf);
void setbuffer(FILE* stream, char* buf, size_t size);
void setlinebuf(FILE *stream);

FILE *fmemopen(void* buf, size_t size, const char *mode);

#define perror(s) fputs(s, stderr)

#define BUFSIZ 8192

#endif
