#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>



void combinations(int, int, int, int);

int main(int argc, char **argv) 
{
	int ips[] = {0,1,8, 16, 46, 74, 96, 106, 109, 126, 127, 186, 192, 255};
	int ipsLen = sizeof(ips)/sizeof(int);
	int sendSocket;
	struct	sockaddr_in serverAddr;
	char** combinations = malloc();
	if((sendSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP))<0)
	{
		printf("socket() failed");
	}
	printf("The socket is %d", sendSocket);
	

	
	//memsetting the server struct to 0
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(servIP);


}


/* This function returns the combinations of four numbers given to it. 
 *	So when given 4 numbers, it returns a list of 4*3*2*1 valid
 *	IP addressed which is 24
 */
void combinations(char** combos, int a, int b, int c, int d) 
{
	char *temp = malloc(sizeof(char)*15);
       	sprintf(temp, "%d.%d.%d.%d", a, b, c, d);
		t
}

