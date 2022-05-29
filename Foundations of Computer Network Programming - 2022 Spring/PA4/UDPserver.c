/*
Daniel Koelzer
DLK0138
4/13/2022
CSCE3530 -- Prog. Assignment 4
*/

/* Server Code */
/* Run on cse03 */
/* Using code provided in assignment as basis.*/
/* Checksum algorithm is adapted from BSD-16 Bit checksum https://en.wikipedia.org/wiki/BSD_checksum */

#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
 
#define BUFLEN 521  //Max length of buffer
 
struct UDPSegment {
	unsigned short int in_port;
	unsigned short int out_port;
	unsigned short int length;
	unsigned short int checksum;
	char payload[513];
};
 
int checksum(struct UDPSegment segment) {
	unsigned int chksum = 0;
	unsigned char *segPointer = (unsigned char *)&segment;	//Get pointer of segment struct
	for(int i = 0; i < sizeof(segment); i++) {
		chksum = (chksum >> 1) + ((chksum & 1) << 15);		//bitwise circular shift right
		chksum += segPointer[i];							//Sum
		chksum &= 0xffff;									//Bitmask with 0xffff
	}
	return chksum;
}
 
void die(char *s)
{
    perror(s);
    exit(1);
}
 
int main(void)
{
	FILE * fp;
	struct sockaddr_in si_me, si_other;
    int sockfd, i, slen = sizeof(si_other) , recv_len;
	struct UDPSegment udp_segment;
	char buf[BUFLEN];
	int userdefport;
	
	printf("Port: ");		//Prompt port
	fgets(buf,BUFLEN,stdin);
	userdefport = atoi(buf);
	
    //create a UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
     
    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));
     
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(userdefport);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
     
    //bind socket to port
    if(bind(sockfd, (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        die("bind");
    }
	//try to receive some data, this is a blocking call
	if ((recv_len = recvfrom(sockfd, &udp_segment, sizeof(struct UDPSegment), 0, (struct sockaddr *) &si_other, &slen)) == -1)
	{
		die("recvfrom()");
	}
	
	printf("Source Port: %d\n",udp_segment.in_port);
	printf("Destination Port: %d\n",udp_segment.out_port);
	printf("Length: %d\n",udp_segment.length);
	printf("Checksum: %d (0x%04x)\n",udp_segment.checksum,udp_segment.checksum);
	printf("Payload: %d\n",sizeof(udp_segment.payload)-1);
	int old_checksum = udp_segment.checksum;	//Store old checksum
	udp_segment.checksum = 0;					//Reset checksum to enable calculation.
	int calc_checksum = checksum(udp_segment);	//Calculate new checksum.
	printf("Calculated Checksum: %d (0x%04x)\n",calc_checksum,calc_checksum);
	if(calc_checksum == old_checksum) {
		printf("Checksum matched!\n");
		
		//Write output.txt
		fp = fopen("output.txt","w");
		if(fp == NULL) {
			die("Error opening output.txt");
		}
		fprintf(fp,"%s",udp_segment.payload);
		fclose(fp);
		printf("output.txt written\n");
		
		//Write server.log
		fp = fopen("server.log","w");
		if(fp == NULL) {
			die("Error opening server.log");
		}
		//Body
		fprintf(fp,"Port: %d\n",userdefport);
		fprintf(fp,"Source Port: %d\n",udp_segment.in_port);
		fprintf(fp,"Destination Port: %d\n",udp_segment.out_port);
		fprintf(fp,"Length: %d\n",udp_segment.length);
		fprintf(fp,"Checksum: %d (0x%04x)\n",old_checksum,old_checksum);
		fprintf(fp,"Payload: %d\n",sizeof(udp_segment.payload)-1);
		fprintf(fp,"Calculated Checksum: %d (0x%04x)\n",calc_checksum,calc_checksum);
		fprintf(fp,"Checksum Matched!\n");
		fprintf(fp,"output.txt written\n");
		fprintf(fp,"server.log written\n");
		//End body
		fclose(fp);
		printf("server.log written\n");
	} else {
		printf("Checksum mismatch!\n");
		printf("output.txt not written\n");
		
		//Write server.log
		fp = fopen("server.log","w");
		if(fp == NULL) {
			die("Error opening server.log");
		}
		//Body
		fprintf(fp,"Port: %d\n",userdefport);
		fprintf(fp,"Source Port: %d\n",udp_segment.in_port);
		fprintf(fp,"Destination Port: %d\n",udp_segment.out_port);
		fprintf(fp,"Length: %d\n",udp_segment.length);
		fprintf(fp,"Checksum: %d (0x%04x)\n",old_checksum,old_checksum);
		fprintf(fp,"Payload: %d\n",sizeof(udp_segment.payload)-1);
		fprintf(fp,"Calculated Checksum: %d (0x%04x)\n",calc_checksum,calc_checksum);
		fprintf(fp,"Checksum Mismatched!\n");
		fprintf(fp,"output.txt not written\n");
		fprintf(fp,"server.log written\n");
		//End body
		fclose(fp);
		
		printf("Server.log written\n");
	}
    close(sockfd);
    return 0;
}