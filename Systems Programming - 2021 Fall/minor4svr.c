/*
Daniel Koelzer
dlk0138
11/22/2021
Minor Assignment 4
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	srand(time(0));																			//Random time
	if(argc != 2) {																			//Check for args
		printf("Incorrect usage. Please execute using ./minor4srv <port>\n");
		return 1;
	}
	
	int sockfd = 0, portno;																	
	socklen_t cli_size;
	struct sockaddr_in serv_addr, cli_addr;
	char buff[1025];  
	
	if((sockfd = socket(AF_INET,SOCK_DGRAM,0))<0) {											//Initialize socket
		perror("socket");
		exit(EXIT_FAILURE);
	}
																							//Clear addresses and buffer
	memset(&serv_addr, '0', sizeof(serv_addr));
	memset(&cli_addr,'0',sizeof(cli_addr));
	memset(buff, '0', sizeof(buff));
																							//Initialize Server address
	serv_addr.sin_family = AF_INET;    
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
	portno = atoi(argv[1]);
	serv_addr.sin_port = htons(portno);    

	int on = 1; 
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)); 							//Reuse address upon different instances
	fcntl(sockfd,F_SETFD,1);																//Set socket to block
	
	if (bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) == -1)					//Bind socket
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}

	while (1)																				//Loop inifinitely
	{
		int n;
		cli_size = sizeof(cli_addr);
		printf("[server]: ready to accept data...\n");										//Server ready to accept data.
		while(1) {
			memset(buff, '0', sizeof(buff));															//Clear buffer
			n = recvfrom(sockfd,buff,1025,MSG_WAITALL,(struct sockaddr *)&cli_addr,&cli_size); 			//Recieve data. Block until data recieved
			if(n != 0) {																				//If valid
				buff[n] = '\0';																			//End of string set to null terminated
				if(rand()%10 >= 3) {																	//30% packet loss sim
					printf("[client]: %s\n",buff);														//Output
					memset(buff, '0', sizeof(buff));
					strcpy(buff,"PONG");
					sendto(sockfd, buff, strlen(buff),MSG_CONFIRM,(struct sockaddr *)&cli_addr,cli_size);	//Send "PONG" to client
				} else {
					printf("[server]: dropped packet\n");												//Packet dropped
				}
			}
		}
		close(sockfd);    
		sleep(1);
		break;
	} 
 
	return 0;
}