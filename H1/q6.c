#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
	char bufferr[300];
	int j;
	while(1){
		int j = read(0, bufferr, sizeof(bufferr));
		if(j>1)
			write(1, bufferr, j);
		else
			break;
	}

	return 0;
}
