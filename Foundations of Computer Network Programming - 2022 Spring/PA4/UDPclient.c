/*
Daniel Koelzer
DLK0138
4/13/2022
CSCE3530 -- Prog. Assignment 4
*/

/* Client Code */
/* Connect to server on cse03 with user defined port from cse04*/
/* Using code provided in assignment as basis.*/
/* Checksum algorithm is adapted from BSD-16 Bit checksum https://en.wikipedia.org/wiki/BSD_checksum */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
 
#define SERVER "129.120.151.96" // cse03
#define BUFLEN 512  //Max length of buffer
 
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
 
int main (int argc, char **argv)
{
	struct UDPSegment udp_segment;
	struct sockaddr_in si_other;
    int sockfd, i=0, slen=sizeof(si_other);
	int userdefport;
    char buf[BUFLEN];
	char filename[BUFLEN];
    char message[BUFLEN];
 
	printf("Port: ");		//Prompt port
	fgets(buf,BUFLEN,stdin);
	userdefport = atoi(buf);
	
	printf("Filename: ");	//Prompt filename
	fgets(filename,BUFLEN,stdin);
	filename[strcspn(filename, "\n")] = 0; //Trim newline
	
	FILE * fp;
	fp = fopen(filename,"r");
	if(fp == NULL) {
		die("File not found.");
	}
	bzero(udp_segment.payload,513);
	fgets(udp_segment.payload,512,fp);	//Load payload from file.
	fclose(fp);
	
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)	//Create UDP socket
    {
        die("socket");
    }
 
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(userdefport);
     
    if (inet_aton(SERVER , &si_other.sin_addr) == 0) 
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }
 
	// ------------------ Format UDP segment ----------------------
	
	udp_segment.in_port = 1234;						//Source port hardcoded to 1234. Instructions unclear whether or not to pull source port from a response from server or not.
	printf("Source Port: %d\n",udp_segment.in_port);
	
	udp_segment.out_port = userdefport;				//Dest port as defined by user.
	printf("Destination Port: %d\n",udp_segment.out_port);
	
	udp_segment.length = 520;						//Length will always be 520 (2b + 2b + 2b + 2b + 512b), ignoring extra byte for null terminator in payload.
	printf("Length: %d\n",udp_segment.length);
	
	udp_segment.checksum = 0;
	udp_segment.checksum = checksum(udp_segment); 	//Calculate checksum with checksum field set to 0.
	printf("Checksum: %d (0x%04x)\n",udp_segment.checksum,udp_segment.checksum);
	
	udp_segment.payload[512] = 0;					//Ensure null terminated string
	printf("Payload: %d\n",sizeof(udp_segment.payload)-1);
	
	// -------------- END Format UDP segment ----------------------
	
	//send the message
    if (sendto(sockfd, &udp_segment, sizeof(struct UDPSegment), 0, (struct sockaddr *) &si_other, slen) == -1)
    {
		die("sendto()");
    }
	
	// -- Create client log --
	fp = fopen("client.log","w");
	if(fp == NULL) {
		die("Error opening file.");
	}
	fprintf(fp,"Port: %d\n",userdefport);
	fprintf(fp,"Filename: %s\n",filename);
	fprintf(fp,"Source Port: %d\n",udp_segment.in_port);
	fprintf(fp,"Destination Port: %d\n",udp_segment.out_port);
	fprintf(fp,"Length: %d\n",udp_segment.length);
	fprintf(fp,"Checksum: %d (0x%04x)\n",udp_segment.checksum,udp_segment.checksum);
	fprintf(fp,"Payload: %d\n",sizeof(udp_segment.payload)-1);
	fclose(fp);
	// -- End client log --
	printf("Client.log written\n");
 
    close(sockfd);
    return 0;
}

