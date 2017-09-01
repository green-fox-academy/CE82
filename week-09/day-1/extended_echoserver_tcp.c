#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>


#include <time.h>

int main()
{ 

	time_t rawtime;
	struct tm *info;
	char buffer[80];
	char timestamp[200];
	char * pch;
  	
  	
    char str[100];
    int listen_fd, comm_fd; 
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
 
    listen_fd = socket(AF_INET, SOCK_STREAM, 0); 
    /*ipv4 protocol
    sock_stream: Provides sequenced, reliable, two-way, connection-based byte streams.
    An out-of-band data transmission mechanism may be supported. 
    tcp-nek ez kell
   protocol 0: The protocol specifies a particular protocol to be used with the socket. Normally only a single protocol exists to support a particular socket type within a given protocol family, in which case protocol can be specified as 0. 
    */
    bzero( &servaddr, sizeof(servaddr)); 
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);//finds all interfaces, and binds to each one of them. 
    servaddr.sin_port = htons(22000); 
   	if ( (bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr))) == -1) {
   		printf("error with binding\n");
    	return -1;
   	}
   	
   	
    if ((listen(listen_fd, 10)) == -1) {
    	printf("error with listening\n");
    	return -1;
    }
    if((comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL)) == -1) {
    	printf("error with accepting\n");
    	return -1;
    }
    /*On success, these system calls return a nonnegative integer that is a
       file descriptor for the accepted socket.  On error, -1 is returned,
       and errno is set appropriately.
     */
    
 
    while(1)
    { 
        bzero( str, 100);
 
        if ((read(comm_fd,str,100)) == -1) {
        	printf("error with reading\n");
    		return -1;
        }
        
        time( &rawtime );
        info = localtime( &rawtime );
        strcpy(timestamp, asctime(info));
        pch=strchr(timestamp,'\n');
  		timestamp[pch - timestamp] = ' '; //sortörés kivesz
        printf("%s-Echoing back - %s",timestamp, str);
        
        FILE *fp;
		fp = fopen("log.txt", "a");
		if (fp == NULL) {
			printf("error with opening file\n");
			return -1;
		}
		if (strcmp(str, "") != 0)
			fprintf(fp,"%s %s",timestamp,str);
		fclose(fp);
        if (write(comm_fd, str, strlen(str)+1) == -1) {
        	printf("error with writing\n");
    		return -1;
        }
 
    }
}
