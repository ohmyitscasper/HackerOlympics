#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>



//Functional prototype for the function that will take in an array of ips and 
//return an array of char*'s which hold the ip combinations properly formatted.  
char** combinations(int ip[], int);

int main(int argc, char **argv) 
{
	int ips[] = {0,1,8, 16, 46, 74, 96, 106, 109, 126, 127, 186, 192, 255};
	int ipsLen = sizeof(ips)/sizeof(int);
	int sendSocket;
	struct	sockaddr_in serverAddr;

	if((sendSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP))<0)
	{
		printf("socket() failed");
	}
	printf("The socket is %d", sendSocket);
	
	int* asd = malloc(1000);
	
	//memsetting the server struct to 0
	memset(&serverAddr, 0, sizeof(serverAddr));


}


char** combinations(int ip[], int len) 
{
	


}

