
/*
======================================================================================================================================================================
Name :1a.c
Author : BHANUJA BHATT
Description : Write a separate program (for each time domain) to set a interval timer in 10sec and
10micro second
a. ITIMER_REAL
b. ITIMER_VIRTUAL
c. ITIMER_PROF
Date: 7th sep, 2024.
======================================================================================================================================================================

======================================================================================================================================================================
Sample Output:
Real timer expired!
======================================================================================================================================================================
*/
#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

void real_timer_handler(int signum) {
    printf("Real timer expired!\n");
}

int main() {
    struct itimerval timer;

    signal(SIGALRM, real_timer_handler);

    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("Error setting timer");
        return 1;
    }
    while (1);
    
    return 0;
}

