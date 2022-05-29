/*
Daniel Koelzer
DLK0138
2/22/2022
CSCE3530 -- Prog. Assignment 2
*/

/* Client Code */
/* Connect to user defined URL with user defined port from cse04*/

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

char userInput[40960];
char url[40960];
int port;

FILE *fp;
FILE *cache;

int sockfd;
int len = sizeof(struct sockaddr);
char recvline[40960];
char writeline[40960];
struct sockaddr_in servaddr;
struct hostent *targethostname;
int responseCode;

char cachedSites[5][4096];
bool isCached = 0;
char pageFileName[255];

int main (int argc, char **argv)
{		
	while(1) { 	//Loop until user enters "quit"
		port = 0;
		bzero(url,40960);
		bzero(recvline,40960);
		bzero(writeline,40960);
		bzero(&servaddr,sizeof(servaddr));
		
		printf("URL: "); 	//Get URL and Port
		scanf("%s",url);
		if(strcmp(url,"quit")==0) {			//Detect user entering "quit", break loop and exit.
			printf("cya!\n");
			return 0; 
		}
		printf("Port: ");
		scanf("%s",userInput);
		if(strcmp(userInput,"quit")==0) {	//Detect user entering "quit", break loop and exit.
			printf("cya!\n");
			return 0;
		}
		port = atoi(userInput);
 
		cache = fopen("list.txt","a+");		//Open file, get current list.txt.
		for (int i = 0; i < 5; i++) {
			fgets(cachedSites[i],4096,cache);
			//printf("DEBUG %d: %s\n",i,cachedSites[i]);
		}
		fclose(cache);
		isCached = 0;
		for (int i = 0; i < 5; i++) {		//Check for URL in cache, if found, set isCached to true and break
			if(strstr(cachedSites[i],url)) {
				isCached = 1;
				strncpy(pageFileName,strstr(cachedSites[i],url)+strlen(url)+1,strlen(cachedSites[i])-strlen(url));
				break;
			}
		}
		
		if(isCached) {
			printf("Response: 200\n"); //All pages cached will have a response of 200.
			printf("Action: Page found in cache, filename - %s\n",pageFileName);
		} else {
			//Get IP of URL, set up server address
			targethostname = gethostbyname(url);
			if(targethostname == NULL) {
				printf("Host name not found.\n");
				continue;
			}
			servaddr.sin_family = AF_INET;
			servaddr.sin_addr.s_addr = *((unsigned long *)targethostname->h_addr);
			servaddr.sin_port = htons(port);

			//Set up socket
			sockfd = socket(AF_INET, SOCK_STREAM, 0);
		
			/* Connect to server */
			connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
		
			sprintf(writeline,"GET / HTTP/1.1\r\nHost: %s\r\nConnection: Close\r\n\r\n",targethostname->h_name);
			write(sockfd,writeline,strlen(writeline));
			sleep(1);
			read(sockfd, recvline, sizeof(recvline));
			
			char tokenized[40960];
			strcpy(tokenized,recvline);
			strtok(tokenized," "); //Ignore first word; Should be HTTP/1.1
			responseCode = atoi(strtok(NULL," "));
			printf("Response: %d\n",responseCode);
			if(responseCode != 200) {
				printf("Action: Not cached\n");
				continue;
			} else {
				//Cache landing page. Only storing 40960 characters.
				time_t rawtime;
				struct tm * timeinfo;
	
				time(&rawtime);
				timeinfo = localtime(&rawtime);
				
				sprintf(pageFileName,"%4d%02d%02d%02d%02d%02d",timeinfo->tm_year+1900,timeinfo->tm_mon+1,timeinfo->tm_mday,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
				printf("Action: Page cached as filename - %s\n",pageFileName);
				
				char temp[4096];
				cache = fopen("list.txt","a+");	
				sprintf(temp,"%s %s\n",url,pageFileName); //Add url and filename to list.txt
				fputs(temp, cache);
				fclose(cache);
				
				fp = fopen(pageFileName,"w"); //Create cached file.
				fputs(recvline,fp);
				fclose(fp);
				
				//Ensure cache is only 5 entries long.
				char tempArr[6][4096];
				cache = fopen("list.txt","a+");
				for(int i = 0; i < 6; i++) {
					fgets(tempArr[i],4096,cache);
					//printf("DEBUG %d:%s\n",i,tempArr[i]);
				}
				if(strlen(tempArr[5])!= 0) {
					//printf("DEBUG: Over 5 elements.\n");
					remove("list.txt");			//Close and delete cache, all values are stored in array.
					cache = fopen("list.txt","a+");
					strtok(tempArr[0]," ");
					char * match;
					match = strtok(NULL," ");
					match[strcspn(match,"\n")]=0;
					remove(match);  //Delete first entry in the cache
					for(int i = 0; i < 5; i++) {
						memcpy(tempArr[i],tempArr[i+1],sizeof(tempArr[i+1]));
						fputs(tempArr[i],cache);
					}
				}
				fclose(cache);
			}
		}
	}
}