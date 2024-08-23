#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main () {
	int child_pid;
	child_pid = fork();
	if (child_pid > 0) {
		sleep (20);
	}
	else {
		exit (0);
	}
	return 0;
}