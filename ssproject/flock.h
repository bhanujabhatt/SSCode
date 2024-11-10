#ifndef FILE_LOCK_H
#define FILE_LOCK_H

#include <sys/types.h>  // For types like off_t, pid_t
#include <fcntl.h>      // For file control options (e.g., F_RDLCK, F_WRLCK, F_UNLCK)

// Define the struct flock for file locking
struct flock {
    short l_type;    // Type of lock: F_RDLCK (read), F_WRLCK (write), or F_UNLCK (unlock)
    short l_whence;  // How to interpret l_start: SEEK_SET, SEEK_CUR, SEEK_END
    off_t l_start;   // Starting offset for the lock
    off_t l_len;     // Number of bytes to lock (0 means to lock until EOF)
    pid_t l_pid;     // PID of the process holding the lock (used with F_GETLK)
};
