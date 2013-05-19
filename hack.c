#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>

#define NUMIPS 24024
//#define TIMEOUT 100000

int comb(char** combos, int[], int);

int main(int argc, char **argv) 
{
	int ips[] = {0,1,8, 16, 46, 74, 96, 106, 109, 126, 127, 186, 192, 255};
	int ipsLen = sizeof(ips)/sizeof(int);
	int sendSocket;
	int numCombos;
	struct	sockaddr_in serverAddr;
	char **combos = malloc(NUMIPS * sizeof(char*));  //Setting up the memory to hold all of the ips.
	char sendRequest[2000];
	FILE *sockFile;
	char line[1000];
	int httpCode;
	char postdata[] = "name=Vanshil";
	FILE *outfile;
	char *outfileName = "magic";
	struct timeval timeout;

	//Setting the memory for the char*'s that hold the ips.
	int a; 
	for(a=0; a<NUMIPS; a++) 
	{
		combos[a] = malloc(16);
		memset(combos[a], 0, 16);
	}
	
	//Generate the combinations
	numCombos = comb(combos, ips, ipsLen);
		
	//Getting the socket
	if((sendSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP))<0)
		printf("socket() failed");

	//Wrap the socket as a file stream
	if((sockFile = fdopen(sendSocket, "r"))==NULL)
		printf("File couldn't be opened");
	
	//Opening the writing file
	if((outfile = fopen(outfileName, "w"))==NULL)
		printf("Magic file couldn't be opened");
	fseek(outfile, 0L, SEEK_END);


	//setting the values in the timeout struct
	timeout.tv_sec = 1;
	timeout.tv_usec = 0; 
	
	//Changing socket settings to add a timeout. 
	if(setsockopt(sendSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
		printf("setsockopt failed\n");
	
	if(setsockopt(sendSocket, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
		printf("setsockopt failed\n");
	
	//Main for loop that does the networking shit. 	
	for(a = 0; a<NUMIPS; a++) 
	{		

		//memsetting the server struct to 0
		memset(&serverAddr, 0, sizeof(serverAddr));
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_addr.s_addr = inet_addr(combos[a]);	//Temporarily setting the first ip to connect localhost for flask testing 
		serverAddr.sin_port = htons(80);

		//Setting up the buffer that will send the request
		memset((void*)sendRequest, 0, sizeof(sendRequest));

		//The post request to send to the server. Currently sending the ip to localhost 
		sprintf(sendRequest, "POST /hackerolympics.json HTTP/1.1\r\nAccept: */*\r\nReferrer: %s\r\nAccept-Language: en-us\r\nContent-Type: application/x-www-form-urlencoded\r\nAccept-Encoding: gzip,deflate\r\nUser-Agent: Mozilla/4.0\r\nContent-Length: %d\r\nPragma: no-cache\r\nConnection: keep-alive\r\n\r\n%s", combos[a], strlen(postdata), postdata); 
	
		//Connecting to the IP
		if(connect(sendSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr))<0)  
		{
//			printf("Connect with IP: %s failed.\n", combos[a]);
			continue;
		}		
		else
			printf("Connection established with IP: %s.\n", combos[a]);
		
		//Sending the request to the ip
		if(send(sendSocket, sendRequest, strlen(sendRequest), 0) != strlen(sendRequest)) 
			printf("Send to IP: %s failed\n", combos[a]);
		
		//The following few lines of code check the http status code.
	//	fgets(line, sizeof(line), sockFile);
	//	char *temp = strchr(line, ' ')+1;
	//	httpCode = atoi(temp);	
	//	
	//	if(httpCode==200) 
	//	{
	//		//Read through the headers
	//		while(strcmp(fgets(line, sizeof(line), sockFile), "\r\n")!=0) {}
	//		
	//		//Read the rest of the html page and write it to stdout
	//		while(fgets(line, sizeof(line), sockFile)!=NULL)
	//			fprintf(stdout, "%s", line);
	//	}
	//	else
	//		printf("%s\n", line);
		
		while(fgets(line, sizeof(line), sockFile)!=NULL)
			fprintf(outfile, "%s", line);
		


	}
	fclose(outfile);
	fclose(sockFile);
	close(sendSocket);
	for(a = 0; a<24024; a++) 
		free(combos[a]);
	free(combos);
}

/*
 * Function to generate the various combinations of ip addresses and 
 * store them in the combos structure.
 */
int comb(char** combos, int *ip, int len)
{
	int a, b, c, d;
	int count=0;
	for(a=0; a<len; a++) {
		for(b=0; b<len; b++) {
			for(c=0; c<len; c++) {
				for(d=0; d<len; d++) {
					if(!(a==b) && !(a==c) && !(a==c) && !(a==d) && !(b==c) && !(b==d) && !(c==d))  
						sprintf(combos[count++], "%d.%d.%d.%d\0", ip[a], ip[b], ip[c], ip[d]);	
				} 
			}
		}
	}
	return count;
}
