#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include<string.h>
#include<string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
 
int main(int argc,char **argv)
{
    int sockfd,n;
    char sendline[100];
    char recvline[100];
    struct sockaddr_in servaddr;
    /*
    #include <netinet/in.h>
	struct sockaddr_in {
    	short            sin_family;   // e.g. AF_INET
    	unsigned short   sin_port;     // e.g. htons(3490)
    	struct in_addr   sin_addr;     // see struct in_addr, below
    	char             sin_zero[8];  // zero this if you want to
	};
	struct in_addr {
    	unsigned long s_addr;  // load with inet_aton()
	};
    */
 
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr, sizeof servaddr);
    /*void bzero(void *s, size_t n);
    	erases the data in the n bytes of the memory
       tarting at the location pointed to by s, by writing zeroes (bytes
       containing '\0') to that area.
    */

 
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(22000);
 
    inet_pton(AF_INET,"127.0.0.1",&(servaddr.sin_addr)); //localhost
    //inet_pton - convert IPv4 and IPv6 addresses from text to binary form
    //int inet_pton(int af, const char *src, void *dst);
    /*converts the character string src into a network address structure 
    in the af address family, then copies the network address structure to dst.  
    The af argument must be either AF_INET or AF_INET6.  dst is written in network byte order.
    */
 
    if (connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) == -1) {
    	printf("error with connecting\n");
    	return -1;
    }
 
    while(1) {
        bzero( sendline, 100);
        bzero( recvline, 100);
        fgets(sendline,100,stdin); /*stdin = 0 , for standard input */ //ha ő mondja...
        if (write(sockfd,sendline,strlen(sendline)) == -1) {
        	printf("error with writing\n");
    		return -1;
        }
        if (read(sockfd,recvline,100) == -1) {
        	printf("error with reading\n");
    		return -1;
        }
        printf("%s",recvline);
    }
 
}

