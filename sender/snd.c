#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
 
#define SERVERPORT 4950 // the port users will be connecting to
 
int main(int argc,char *argv[])
{
int sockfd;
struct sockaddr_in their_addr; // connector's address information
struct hostent *he;
int numbytes;
int broadcast = 1;
FILE *fp1;
int infile[50000]; //filesize
int *mypointer
char c;
int i = 0;
 
mypointer = infile;
 
if (argc != 3) {
fprintf(stderr,"usage: broadcaster hostname message\n");
exit(1);
}
 
if ((he = gethostbyname(argv[1])) == NULL) { // get the host info
herror("gethostbyname");
exit(1);
}
 
if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
perror("socket");
exit(1);
}
 
 
if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast,
sizeof broadcast) == -1) {
perror("setsockopt (SO_BROADCAST)");
exit(1);
}
fp1 = fopen(argv[2],"r");
while(( c = getc(fp1)) != EOF)
{
infile[i] = c;
i = i+1;
};
their_addr.sin_family = AF_INET; // host byte order
their_addr.sin_port = htons(SERVERPORT); // short, network byte order
their_addr.sin_addr = *((struct in_addr *)he->h_addr);
memset(their_addr.sin_zero, '\0', sizeof their_addr.sin_zero);
 
if ((numbytes=sendto(sockfd, mypointer, i, 0,
(struct sockaddr *)&their_addr, sizeof their_addr)) == -1) {
perror("sendto");
exit(1);
}
 
printf("sent %d bytes to %s\n", numbytes, inet_ntoa(their_addr.sin_addr));
 
close(sockfd);
 
return 0;
}