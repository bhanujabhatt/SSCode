/*
=========================================================================================================================================================================================
Name : handsonprog13.c
Author : Bhanuja Bhatt
Description : Write a program to wait for a STDIN for 10 seconds using select. Write a proper print statement to verify whether the data is available within 10 seconds or not.
Date: 25th Aug, 2024
=========================================================================================================================================================================================

=========================================================================================================================================================================================
Sample Output:
lll
Data is available from STDIN within 10 seconds.
You entered: lll
=========================================================================================================================================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/select.h>
#include<sys/time.h>
#include<fcntl.h>

int main(){
    fd_set rfds;
    struct timeval tv;
    int retval;
    char buf[1024];

    FD_ZERO(&rfds);
    FD_SET(0, &rfds); 

    tv.tv_sec = 10; 
    tv.tv_usec = 0; 

    retval = select(1, &rfds, NULL, NULL, &tv);

    if (retval == -1) {
        perror("select()");
    } else if (retval) {
        printf("Data is available from STDIN within 10 seconds.\n");
        int bytes_read = read(0, buf, sizeof(buf) - 1);
        if (bytes_read > 0) {
            buf[bytes_read] = '\0'; 
            printf("You entered: %s", buf);
        } else {
            perror("read()");
        }
    } else {
        printf("No data available from STDIN within 10 seconds.\n");
    }

    return 0;
}
