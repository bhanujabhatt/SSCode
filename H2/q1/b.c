
/*
======================================================================================================================================================================
Name :1b.c
Author : BHANUJA BHATT
Description : Write a separate program (for each time domain) to set a interval timer in 10sec and
10micro second
a. ITIMER_REAL
b. ITIMER_VIRTUAL
c. ITIMER_PROF
Date: 8sep, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
Virtual timer expired!
======================================================================================================================================================================
#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

void virtual_timer_handler(int signum) {
    printf("Virtual timer expired!\n");
}

int main() {
    struct itimerval timer;
    
    signal(SIGVTALRM, virtual_timer_handler);

    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;
    
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    
    if (setitimer(ITIMER_VIRTUAL, &timer, NULL) == -1) {
        perror("Error setting timer");
        return 1;
    }
   
    while (1);
    
    return 0;
}

