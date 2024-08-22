#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
	int ticketno;
	int fm = open("tickett.txt", O_WRONLY);
	printf("Enter the ticket number to  stored:\n");
	scanf("%d", &ticketno);
	write(fm, &ticketno, sizeof(ticketno));
	printf("Ticket number stored succesfully\n");
	close(fm);
	return 0;
}
