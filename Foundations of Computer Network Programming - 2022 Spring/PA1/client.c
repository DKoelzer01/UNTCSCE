/*
Daniel Koelzer
DLK0138
2/9/2022
CSCE3530 -- Prog. Assignment 1
*/

/* Client Code */
/* Connect to server listening on cse03 with user defined port from cse04*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
 
int main (int argc, char **argv)
{
	if (argc != 2) {
		printf("Invalid number of arguments. Please use the format ./client <port number>");
		return 1;
	}
	
	int port_number = atoi(argv[1]);
    int sockfd, numRead;
    int len = sizeof(struct sockaddr);
    char recvline[40960];
    struct sockaddr_in servaddr;

    /* AF_INET - IPv4 IP , Type of socket, protocol*/
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr,sizeof(servaddr));
 
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port_number); // Server port number
 
    /* Convert IPv4 and IPv6 addresses from text to binary form */
    inet_pton(AF_INET,"129.120.151.96",&(servaddr.sin_addr));
 
    /* Connect to the server */
    connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
 
	char userInput[40960];
	bool contLoop = 1;
 
	while (contLoop) {
		bzero(userInput, 40960); //Clear user input and recvline buffers
		bzero(recvline, 40960);
		printf("Input: ");
		fgets(userInput,40960,stdin); //Get user input
	
		if(strcmp(userInput,"quit\n")==0) {	//Set flag to wait to close. wait for ack from server.
			contLoop = 0; 
		}
	
		//Write user input to server, await response
		write(sockfd,userInput,strlen(userInput));
		
		numRead = read(sockfd, recvline, sizeof(recvline));
		printf("%s",recvline); // print the received text from server
	}
	close(sockfd); //Close socket from client.
}
