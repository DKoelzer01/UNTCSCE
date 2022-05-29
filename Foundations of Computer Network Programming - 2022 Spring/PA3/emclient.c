/*
Daniel Koelzer
dlk0138
3/30/2022
CSCE 3530 -- PA 3 -- SMTP Email Client

Using snippets of code from previous assignments (Programming Assignment 2)
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <time.h>

#define BUFFER_SIZE 40960

void quit_connection(int sock, char * buff){
	sprintf(buff,"quit\n");
	write(sock,buff,strlen(buff));
	bzero(buff,BUFFER_SIZE);
	
	read(sock,buff,BUFFER_SIZE-1);				//Read response
	printf("Response: %s\n",buff);				//Print response
	bzero(buff,BUFFER_SIZE);
	
	exit(0);
}

void networkEvent(int sockfd,char * buffer, int doSleep, int doRead) {	//Container function for sending data to server and reading response
	write(sockfd,buffer,strlen(buffer));				//Write data
	bzero(buffer,BUFFER_SIZE);							//Clear buffer
	if(doSleep) {
		sleep(1);										//Client sleeps
	}
	if(doRead) {
		read(sockfd,buffer,BUFFER_SIZE-1);				//Read response
		printf("Response: %s",buffer);					//Print response
		bzero(buffer,BUFFER_SIZE);						//Clear buffer
	}
}

int main() {
	char servername[128];			//User input server name
	char buffer[BUFFER_SIZE];		//Buffer for text handling / broadcasting
	char message[1024];				//Buffer for message body.
	int port;						//Server port
	int sockfd;						//Socket file descriptor
	struct sockaddr_in servaddr;	//Server address
	struct hostent * server;		//
	char senderemail[1024];			//Email of sender
	char recvemail[1024];			//Email of recipient

	bzero(servername,128);
	bzero(buffer,BUFFER_SIZE);
	
	printf("SMTP Server: ");											//Prompt user input
	fgets(servername,128,stdin);
	servername[strcspn(servername, "\n")] = 0; 							//Trim newline
	printf("Port: ");
	fgets(buffer,BUFFER_SIZE,stdin);
	port = atoi(buffer);
	
	bzero(buffer,BUFFER_SIZE);
	
	server = gethostbyname(servername);									//Get server address from hostname
	if(server == NULL) {
		printf("Cannot find specified hostname\n");
		return 1;
	}
	
	servaddr.sin_family = AF_INET;										//Set up socket
	servaddr.sin_addr.s_addr = *((unsigned long *)server->h_addr);
	servaddr.sin_port = htons(port);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		printf("Socket opening error\n");
		return 1;
	}
	
	connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));		//Connect to SMTP server
	
	read(sockfd,buffer,BUFFER_SIZE-1);				//Read response from connect
	printf("Response: %s",buffer);					//Print response
	
	//------------  EHLO  ------------
	bzero(buffer,BUFFER_SIZE);						//Clear buffer
	sprintf(buffer,"ehlo %s\n",servername);			//Format EHLO
	networkEvent(sockfd,buffer,1,1);				//Send data, Sleep 1 second, read response
	
	//------------  AUTH LOGIN  ------------
	bzero(buffer,BUFFER_SIZE);						//Clear buffer
	sprintf(buffer,"AUTH LOGIN\n");					//Format AUTH LOGIN
	networkEvent(sockfd,buffer,0,1);				//Send data, dont sleep, read response

	char tempBuffer[1024];
	
	//------------  AUTH USERNAME  ------------
	bzero(tempBuffer,1024);
	printf("Username: ");							//Prompt USERNAME
	fgets(tempBuffer,1024,stdin);
	if(strcmp(tempBuffer,"quit\n")==0)
		quit_connection(sockfd,buffer);				//Detect user entering "quit", exit.
	
	bzero(buffer,BUFFER_SIZE);						//Clear buffer
	sprintf(buffer,"%s",tempBuffer);				//Format Username
	networkEvent(sockfd,buffer,1,1);				//Send data, Sleep 1 second, read response
	
	//------------  AUTH PASSWORD  ------------
	bzero(tempBuffer,1024);
	printf("Password: ");							//Prompt PASSWORD
	fgets(tempBuffer,1024,stdin);
	if(strcmp(tempBuffer,"quit\n")==0)
		quit_connection(sockfd,buffer);				//Detect user entering "quit", exit.
	
	bzero(buffer,BUFFER_SIZE);						//Clear buffer
	sprintf(buffer,"%s",tempBuffer);				//Format Password
	networkEvent(sockfd,buffer,1,1);				//Send data, Sleep 1 second, read response
	
	//------------  Post-authentication loop  ------------
	while(1) {
	bzero(buffer,sizeof(buffer));
	bzero(message,sizeof(message));
	bzero(senderemail,sizeof(senderemail));
	bzero(recvemail,sizeof(recvemail));
	bzero(tempBuffer,sizeof(tempBuffer));
	
	//------------  MAIL FROM  ------------
	printf("Sender's email address: ");				//Prompt sender email
	fgets(senderemail,1024,stdin);
	if(strcmp(senderemail,"quit\n")==0)
		quit_connection(sockfd,buffer);				//Detect user entering "quit", exit.
	
	bzero(buffer,BUFFER_SIZE);						//Clear buffer
	sprintf(buffer,"MAIL FROM: %s",senderemail);	//format email
	networkEvent(sockfd,buffer,0,1);				//Send data, dont sleep, read response
	
	//------------  RCPT TO  ------------
	printf("Recipient's email address: ");			//Prompt recpt email
	fgets(recvemail,1024,stdin);
	if(strcmp(recvemail,"quit\n")==0)
		quit_connection(sockfd,buffer);				//Detect user entering "quit", exit.
	
	bzero(buffer,BUFFER_SIZE);						//Clear buffer
	sprintf(buffer,"RCPT TO: %s",recvemail);		//format email
	networkEvent(sockfd,buffer,0,1);				//Send data, dont sleep, read response
	
	//------------  DATA  ------------
	bzero(buffer,BUFFER_SIZE);						//Clear buffer
	sprintf(buffer,"DATA\n");
	networkEvent(sockfd,buffer,0,1);				//Send data, dont sleep, read response
	
	//------------  FROM  ------------
	bzero(tempBuffer,1024);
	printf("Sender's name: ");									//Prompt sender name
	fgets(tempBuffer,1024,stdin);
	if(strcmp(tempBuffer,"quit\n")==0)
		quit_connection(sockfd,buffer);							//Detect user entering "quit", exit.
	
	bzero(buffer,BUFFER_SIZE);						//Clear buffer
	sprintf(buffer,"FROM: \"%s\" %s",tempBuffer,senderemail);	//format FROM
	networkEvent(sockfd,buffer,0,0);				//Send data, dont sleep, dont read response
	
	//------------  TO  ------------
	bzero(tempBuffer,1024);
	printf("Recipient's name: ");								//Prompt recpt name
	fgets(tempBuffer,1024,stdin);
	if(strcmp(tempBuffer,"quit\n")==0)
		quit_connection(sockfd,buffer);							//Detect user entering "quit", exit.
	
	bzero(buffer,BUFFER_SIZE);						//Clear buffer
	sprintf(buffer,"TO: \"%s\" %s",tempBuffer,recvemail);		//format TO
	networkEvent(sockfd,buffer,0,0);				//Send data, dont sleep, dont read response
	
	//------------  SUBJECT  ------------
	bzero(tempBuffer,1024);
	printf("Subject: ");							//Prompt recpt name
	fgets(tempBuffer,1024,stdin);
	if(strcmp(tempBuffer,"quit\n")==0)
		quit_connection(sockfd,buffer); 			//Detect user entering "quit", exit.
	
	bzero(buffer,BUFFER_SIZE);						//Clear buffer
	sprintf(buffer,"SUBJECT: %s",tempBuffer);		//format SUBJECT
	networkEvent(sockfd,buffer,0,0);				//Send data, dont sleep, dont read response
	
	//------------  Message  ------------
	bzero(tempBuffer,1024);
	printf("Message: ");							//Prompt recpt name
	fgets(message,1024,stdin);
	if(strcmp(message,"quit\n")==0)
		quit_connection(sockfd,buffer);				//Detect user entering "quit", exit.
	
	bzero(buffer,BUFFER_SIZE);						//Clear buffer
	sprintf(buffer,"%s.\n",message);				//format MESSAGE, capped at 1024 characters.
	networkEvent(sockfd,buffer,0,1);				//Send data, dont sleep, read response
	}
	
	return 0;
}