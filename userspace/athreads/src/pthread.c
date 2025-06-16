#include <pthread.h>
#include <stddef.h>
#include <unistd.h>
#include <syscall.h>

__thread pthread_t* self;
 pthread_t* pthread_self()
 {
    return self;
 }

int pthread_create(pthread_t* thread,
         const pthread_attr_t* attr,
         void *(*start_routine)(void *),
         void *restrict arg)
{
    if (thread == NULL || start_routine == NULL) {
        return -1; // Invalid arguments
    }
    // Initialize the thread structure
    if (attr) {
        thread->attr = *attr; // Copy attributes if provided
    } else {
        thread->attr = 0; // Default attributes if none provided    
    }
    thread->state = 0; // Initialize state to 0 (not terminated)
    pid_t pid = fork(); // Create a new process for the thread
    if (thread->pid < 0) {
        return -1; // Fork failed
    }
    if (pid == 0) {
        // In child process, execute the thread function
        self = thread;
        thread->ret = start_routine(arg);
        thread->state |= THREAD_TERMINATED; // Set thread state to terminated
        asyscall(SYS_THREADEND, NULL, NULL, NULL, NULL, NULL, NULL); // Notify thread end
    } else {
        // In parent process, set the thread's PID
        thread->pid = pid;
    }
    return 0; // Success
}

int apthread_join(pthread_t* thread, void **retval)
{
    while (!(thread->state & THREAD_TERMINATED)) {
        // Wait for the thread to terminate
        switchtask;
    }
    if (retval) {
        *retval = thread->ret; // Get the return value of the thread
    }
    // Clean up the thread structure
    return 0; // Success
}