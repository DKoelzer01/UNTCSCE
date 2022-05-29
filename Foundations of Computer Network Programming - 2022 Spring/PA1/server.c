/*
Daniel Koelzer
DLK0138
2/9/2022
CSCE3530 -- Prog. Assignment 1
*/

/* Server Code */
/* Run the server on cse03 and the server listens on user defined port */

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
 
int main(int argc, char **argv)
{
	if (argc != 2) {
		printf("Invalid number of arguments. Please use the format ./ctserver <port number>");
		return 1;
	}
	
	int port_number = atoi(argv[1]);
 
    char str[40960];
	char str_out[40960];
    int listen_fd, conn_fd;
    struct sockaddr_in servaddr;
 
    /* AF_INET - IPv4 IP , Type of socket, protocol*/
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
 
    bzero(&servaddr, sizeof(servaddr));
 
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(port_number);
 
    /* Binds the above details to the socket */
	bind(listen_fd,  (struct sockaddr *) &servaddr, sizeof(servaddr));
	
	/* Start listening to incoming connections */
	listen(listen_fd, 10);
	
	/* Accepts an incoming connection */
	conn_fd = accept(listen_fd, (struct sockaddr*)NULL, NULL);
	
	while(1) {
		bzero(str, 40960);
		bzero(str_out, 40960);
		read(conn_fd,str,sizeof(str));
		
		if(strcmp(str,"quit\n")==0) {
			write(conn_fd, "cya!\n\0", strlen("cya!\n\0")); //Acknowledge "quit", send "cya"
			return 0; //Close server process, socket handled on client's end to avoid long SOCK_WAIT status.
		}
		
		//Modify input string according to specs
		char c;
		int i = 0;
		
		int wordCount = 0;
		int alphaCount = 0;
		int punctCount = 0;
		
		bool firstAlpha = 1;
		bool contLoop = 1;
		bool isWord = 0;
		
		while(contLoop) {
			c = str[i];
			if(i == (strlen(str))) { //End of string case
				if(isWord == 1) { //Check if word was ended by end of string.
					wordCount++;
					isWord = 0;
				}
				contLoop = 0;
			} else {
			if(firstAlpha) { //If first alpha not already found
				if((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) { //Check for alpha
					alphaCount++;
					isWord = 1;
					if(c >= 65 && c <= 90) { 	//If already upper, do nothing, set firstAlpha flag to false
						firstAlpha = 0;
					} else {					//Otherwise, char is lowercase alpha, set to upper.
						firstAlpha = 0;
						c-=32;
					}
				}
			} else {
				if((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) { //Count alphabets.
					alphaCount++;
					isWord = 1;
				}
					
				if(c >= 65 && c <= 90) //set all alpha chars to lowercase. Ignore those already lowercase.
					c+=32;
				
				if((c >= 33 && c <= 47) || (c >= 58 && c <= 64) || (c >= 91 && c <= 96) || (c >= 123 && c <= 126)) //Check for punctuation. Defined punctuation as any non alpha / digit character, excluding control characters and whitespace.
					punctCount++;
				
				if((c == ' ' || c == '!' || c == '.' || c == ',' || c == '|' || c == '\n' || c == '\t' || c == '?' || c == '\'' || c == '\"') && isWord ){ //Check for valid word-ending characters, and if the word has already ended.
					isWord = 0;
					wordCount++;
				}
			}
			str[i] = c;
			i++;
			}
		}
		sprintf(str_out,"Output: %sWords: %d\nAlphabets: %d\nPunctuation Marks: %d\n",str,wordCount,alphaCount,punctCount); //Output with formatting. Send to client.
		write(conn_fd, str_out, strlen(str_out)); // write to the client
	}
	close (conn_fd); //close the connection. Should never be reached.
}
