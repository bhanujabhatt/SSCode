# include<stdio.h>
#include<unistd.h>
#include<sys/select.h>
#include<sys/time.h>
#include<fcntl.h>

int main(){
	fd_set rfds;
	struct timeval tv;
    	int reval;
	FD_ZERO(&rfds);
    	FD_SET(0, &rfds);
        tv.tv_sec = 10;
    	tv.tv_usec = 0;
    	reval = select(1, &rfds, NULL, NULL, &tv);
    
    	if (reval == -1)
		perror("select()");
    	else if (reval)
        	printf("Data is available from STDIN within 10 seconds.\n");
        else
       		printf("No data available from STDIN within 10 seconds.\n");
    return 0;
}
