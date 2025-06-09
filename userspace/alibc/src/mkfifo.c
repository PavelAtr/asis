#include <sys/stat.h>
#include <syscall.h>
#include <unistd.h>

int mkfifo(const char *pathname, mode_t mode)
{
    // Ensure the mode is set correctly
    mode_t adjusted_mode = mode | S_IFIFO;
    char* cwd = get_current_dir_name();
    char* file = fullpath(cwd, pathname);
    // Call the syscall to create a FIFO
    int result = (int)asyscall(SYS_MKFIFO, file,  "rw", 0, 0, 0, 0);
    
    // Check for errors
    if (result == -1) {
        return -1; // Error occurred, errno is set by syscall
    }
    
    return 0; // Success
}