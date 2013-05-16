#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

#define NUMIPS 24024

void combinations(char**, int, int, int, int);
int comb(int[], int);

int main(int argc, char **argv) 
{
	int ips[] = {0,1,8, 16, 46, 74, 96, 106, 109, 126, 127, 186, 192, 255};
	int ipsLen = sizeof(ips)/sizeof(int);
	int sendSocket;
	struct	sockaddr_in serverAddr;
	char **combos = malloc(NUMIPS * sizeof(char*));  //Setting up the memory to hold all of the ips.

	//Setting the memory for the char*'s that hold the ips.
	int a; 
	for(a=0; a<24024; a++) {
		combos[a] = malloc(16);
		memset(combos[a], 0, 16);
	}
	
	printf("NUM of combinations: %d\n", comb(ips, ipsLen));

	//Getting the socket
	if((sendSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP))<0)
	{
		printf("socket() failed");
	}
	printf("The socket is %d\n", sendSocket);
	
	combinations(combos, ips[0], ips[1], ips[2], ips[3]);
	printf("Combos[0] %s\nCombos[1] %s\n",combos[0], combos[1]); 
		
	//memsetting the server struct to 0
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(combos[0]);	//Temporarily setting the first ip to connect to. 

	for(a = 0; a<24024; a++) 
		free(combos[a]);
	free(combos);
}


/* This function returns the combinations of four numbers given to it. 
 *	So when given 4 numbers, it returns a list of 4*3*2*1 valid
 *	IP addressed which is 24
 */
void combinations(char** combos, int a, int b, int c, int d) 
{
	sprintf(combos[0], "%d.%d.%d.%d\0", a, b, c, d);
	sprintf(combos[1], "%d.%d.%d.%d\0", a, b, d, c);

	printf("In combos:\nCombos[0] %s\nCombos[1] %s\n",combos[0], combos[1]); 
}

int comb(int *ip, int len)
{
	int a, b, c, d;
	int count=0;
	for(a=0; a<len; a++) {
		for(b=0; b<len; b++) {
			for(c=0; c<len; c++) {
				for(d=0; d<len; d++) {
					if(!(a==b) && !(a==c) && !(a==c) && !(a==d) && !(b==c) && !(b==d) && !(c==d))
						count++;
				} 
			}
		}
	}
	return count;
}
