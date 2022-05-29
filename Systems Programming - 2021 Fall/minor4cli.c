/*
Daniel Koelzer
dlk0138
11/22/2021
Minor Assignment 4
*/

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <time.h>

int main(int argc, char *argv[])
{
	if(argc != 3) {	//Argument Checking
		printf("Incorrect usage. Please execute using ./client <hostname> <port>\n");
		return 1;
	}
	
	int sockfd = 0;										//Socket
	socklen_t serv_size;								//Size of socket
	char buff[1025];									//Character buffer
	struct serv_addr;									//Server_address struct
	memset(buff, '0', sizeof(buff));					//Clear buffer
	
	if ((sockfd = socket(AF_INET,SOCK_DGRAM,0)) < 0)	//Initialize socket
	{
		printf("socket error\n");
		exit(EXIT_FAILURE);
	}
	
	struct hostent *he;									//Hostname
	if((he = gethostbyname(argv[1]))==NULL){
		perror("hostname");
		exit(EXIT_FAILURE);
	}
	
	memcpy(&serv_addr.sin_addr,he->h_addr_list[0],he->h_length);	//Copy address found for hostname
	serv_addr.sin_family = AF_INET;									
	serv_addr.sin_port = htons(atoi(argv[2]));						//Set port
	inet_pton(AF_INET,argv[1], &serv_addr.sin_addr);
	
	struct timeval tv;												//Socket timeout 500ms
	tv.tv_sec = 0;
	tv.tv_usec = 500000;
	if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0) {
		perror("timeout");
	}
	int n;
	double sumtimes = 0.0f;
	double numPackets = 10;
	double numRcvd = 0;
	double minTime = -1;
	double maxTime = -1;
	for(int i = 0; i < numPackets; i++) {							//Loop to send multiple packets (10)
		serv_size = sizeof(serv_addr);
		memset(buff, '0', sizeof(buff));
		strcpy(buff,"PING");
		clock_t t = clock();										//Start timing
		sendto(sockfd,buff,sizeof(buff),MSG_CONFIRM,(struct sockaddr *)&serv_addr,serv_size);	//Send packet
		printf("Sent... ");																		//Confirm sent
		n = recvfrom(sockfd,buff,sizeof("PING"),MSG_CONFIRM,(struct sockaddr *)&serv_addr,&serv_size);	//Try to recieve
		t = clock()-t;																					//Stop timing
		double timeMilSec = ((double)t / CLOCKS_PER_SEC)*1000;											//Calculate elapsed time in ms
		if(n > 0) {																						//If recieve successful
			if(maxTime == -1) {										//Evalulate max/min/avg times
			minTime = timeMilSec;
			maxTime = timeMilSec;
			}
			if(timeMilSec > maxTime) {
				maxTime = timeMilSec;
			}
			if(timeMilSec < minTime) {
				minTime = timeMilSec;
			}
			sumtimes += timeMilSec;
			numRcvd++;
			buff[n] = '\0';
			printf("RTT=%1.6f ms\n",timeMilSec);					//Print current run's time
		} else {
			printf("Timed Out\n");									//Recieve failed, timed out
		}
	}
	sumtimes /= numRcvd;											//Average time
	printf("%.0f pkts xmited, %.0f pkts rcvd, %2.2f%% pkt loss\n",numPackets,numRcvd,(1-(numRcvd/numPackets))*100);	//Output formatted
	printf("min: %1.6f ms, max: %1.6f ms, avg: %1.6f ms\n",minTime,maxTime,sumtimes);							
	return 0;
}

