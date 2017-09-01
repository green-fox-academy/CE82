#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <termios.h>
typedef struct {
	char name[255];
	unsigned long addr;
	unsigned short port;
}user;
user users[50];
int8_t last = 0;
uint16_t own_port = 16231; //for msg
uint16_t disc_port = 16232; //for disc rec port
uint16_t br_port = 12345;
char start_get_br = 0;
char own_addr[] = "255.255.255.255";
static struct termios old, new;
/* Initialize new terminal i/o settings */
void f()
{
	fflush(stdout);
}
void initTermios(int echo)
{
	tcgetattr(0, &old); /* grab old terminal i/o settings */
	new = old; /* make new settings same as old settings */
	new.c_lflag &= ~ICANON; /* disable buffered i/o */
	new.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
	tcsetattr(0, TCSANOW, &new); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void)
{
	tcsetattr(0, TCSANOW, &old);
}
char getch_(int echo)
{
	char ch;
	initTermios(echo);
	ch = getchar();
	resetTermios();
	return ch;
}

/* Read 1 character without echo */
char getch(void)
{
	return getch_(0);
}
void get_own_ip () //felesleges, de maradhat
{
    struct ifaddrs *ifap, *ifa;
    struct sockaddr_in *sa;
    char *addr;

    getifaddrs (&ifap);
    for (ifa = ifap; ifa; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr->sa_family==AF_INET) {
            sa = (struct sockaddr_in *) ifa->ifa_addr;
            addr = inet_ntoa(sa->sin_addr);
            if (strcmp(ifa->ifa_name, "wlan0" ) == 0) {
            	//printf("Interface: %s\tAddress: %s\n", ifa->ifa_name, addr);
            	strcpy(own_addr, addr);
            	printf("own ip: %s\n", own_addr);
            }
        }
    }

    freeifaddrs(ifap);
    return;
}
//---------------------------------------------------------------------------
void get_port(char *buf, uint32_t *n1, uint32_t *n1)
{
	char szam1[20];
	char szam2[20];
	memset(szam1,'\0', strlen(port));
	memset(szam2,'\0', strlen(port));
	int i=0;
	int j = 0;
    while(i < strlen(buf) && buf[i] != ' ') {
		szam2[j] = buf[i];
        i++;
		j++;
    }
    szam2[j]='\0';
    j = 0;
    i = i + 1;
    while(i < strlen(buf)) {
    	szam1[j] = buf[i];
    	j++;
    	i++;
    }
     szam1[j]='\0';
    
    char * pEnd;    
    n1 = strtol(szam1,&pEnd,10);
	n2 = strtol(szam2,&pEnd,10);
	
    return p;
}
//-------------------------------------------------------------------------

//---------------------------------------------------------------------------
void *br_listen()
{
//listens for incoming broadcast messages 
//these messages are discovery requests (azmilyen)
//if a message arrives the program will send the user name and the port of the message listener
    //user_name message_listener_port
	int sock, sock_TCP;
	size_t length;
	struct sockaddr_in name, asker;
	bzero(&asker, sizeof asker);
	
	int slen = sizeof(name);
	char buf[1000], buf2[1000];
	int buflen = 1000;
	
	
	sock = socket( AF_INET, SOCK_DGRAM, 0 );
	if( sock == -1 ) {
		printf("error opening datagram socket\n");
		exit(1);
	}
	
	asker.sin_family = AF_INET;
	asker.sin_addr.s_addr = INADDR_ANY;
	asker.sin_port = htons(16232);
	
	name.sin_family = AF_INET;
	name.sin_addr.s_addr = INADDR_ANY;
  	name.sin_port = htons(12345);
	if( bind(sock,(struct sockaddr *) &name, sizeof name ) == -1 ) {
		printf("error binding datagram socket\n");
		exit(2);
	}
	//printf(" binding done \n");
	while (1) {
		//printf(" recvfrom-ra vár\n");
		f();
		bzero( buf, buflen);
		if ((recvfrom(sock, buf, sizeof buf,0,(struct sockaddr *) &asker, &slen)) == -1){
		    printf( "error recv \n" );
		    f();
			exit(2);  
		} else {
			bzero( users, 50);
			last = 0;
			if (strstr(buf, "TOTORO ") != NULL ) {
			    printf("brmsg in: <%s>\n",buf);
				fflush(stdout);
				int port = get_port(buf);
				if (port != 8888) {
					printf("getport: <%d>\n", port);
					asker.sin_port = htons(port); 
					printf("asker discport: %d\n", htons(asker.sin_port));
					printf("asker ip: %s\n", inet_ntoa(asker.sin_addr));
					bzero( buf2, buflen);
					snprintf(buf2,buflen,"%s %d","andrea", own_port);
					sock_TCP = socket( AF_INET, SOCK_STREAM, 0 );
					
					if( sock_TCP == -1 ) {
						printf("error opening tcp socket\n");
						exit(1);
					}
					puts("tcp socket created");
					fflush(stdout);
					if (connect(sock_TCP , (struct sockaddr *)&asker , sizeof(asker)) < 0){
		    			perror("connect failed. Error");
		    			exit(1);
					}
					printf("connected \n");
					fflush(stdout);
					if (send(sock_TCP, buf2, strlen(buf2) , 0 ) == -1){
						printf("error sending disc msg\n");
					} else {
						printf("to disc req: <%s> sent to port: %d\n",
						buf2, htons (asker.sin_port));
					}
					f();
					close(sock_TCP);
				}
		    } else {
		    	//printf("got broadcast msg, but no TOTORO: %s\n",buf);
		    	f();
		    }
		}
    }
}

//---------------------------------------------------------------------------
void *disc_listen()
{
//listens for incoming discovery responses 
//other applications will send their user name and message listener port
//if a message arrives the program will save the data as a new user into the user storage 
	printf("disc listen server start\n");
	fflush(stdout);
	char buf[1000];
	int buflen = 1000;
    int listen_sock, from_sock;
    struct sockaddr_in servaddr;    
    listen_sock = socket(AF_INET, SOCK_STREAM, 0);    
    bzero( &servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(own_port+1);//ezen hallgatózik
   
    bind(listen_sock, (struct sockaddr *) &servaddr, sizeof(servaddr));
    listen(listen_sock, 100);
    while(1) {
    	from_sock = accept(listen_sock, (struct sockaddr*) NULL, NULL);
        bzero( buf, buflen);
        recv(from_sock, buf, buflen, 0);    
        printf("jött: <%s>\n",buf);
        fflush(stdout);  
        /*
        printf(inet_ntoa(servaddr.sin_addr));
        char port[20];
		memset(port,'\0', strlen(port));
		int i=0;
		while(i < strlen(buf) && buf[i] != ' ') {
		    
		    users[last].name[i] = buf[i];
		    i = i + 1;
		}
		users[last].name[i] = '\0';
		int j = 0;
		i = i + 1;
		while(i < strlen(buf)) {
			port[j] = buf[i];
			j++;
			i++;
		}
	  
		
		char * pEnd;    
		int p = strtol(port,&pEnd,10);
		printf ("getport port: <%d>\n", p);  
        users[last].port = p;
        //addr = inet_ntoa(sa->sin_addr);
        users[last].addr = servaddr.sin_addr.s_addr;
        
        printf("stored: <%s><%d><%ld>\n", users[last].name, users[last].port, users[last].addr);
        last++;
        */
    }
	return NULL;
}

//---------------------------------------------------------------------------
//send a discovery request as a broadcast UDP message
//the messages is TOTORO port_where_the_program_waits_for_response
void send_req() 
{
	char buf[512];
	bzero(&buf, sizeof(buf));
	int clientToServer_socket;
	struct sockaddr_in Remote_Address, Server_Address;
	int broadcast = 1;
	char *broadcastMessage;
	broadcastMessage = "TOTORO 16232";
	int broadcastMessageLen = strlen(broadcastMessage);
	clientToServer_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (clientToServer_socket == -1)
		perror("Error: client socket not created");
	bzero(&Remote_Address, sizeof(Remote_Address));
	Remote_Address.sin_family = AF_INET;
	Remote_Address.sin_port = htons(12345);
	inet_pton(AF_INET,"255.255.255.255",&(Remote_Address.sin_addr));
	if(setsockopt(clientToServer_socket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast) == -1) {
		printf("Error: br setsockopt call failed");
	}	  
	if(sendto(clientToServer_socket, broadcastMessage, broadcastMessageLen+1, 0, (struct sockaddr *) &Remote_Address, sizeof(Remote_Address)) == -1) {
		printf("Error: broadcast sending failed");
	}
	printf("send req done\n");
	f();
	close(clientToServer_socket);
}

//---------------------------------------------------------------------------

int main()
{
	printf("start\n");
	get_own_ip();
	
	pthread_t brlisten_thread, disclisten_thread;
	if(pthread_create(&disclisten_thread, NULL, disc_listen, NULL)) {
		printf("Error creating thread\n");
		return 1;
	}
	
	if(pthread_create(&brlisten_thread, NULL, br_listen, NULL)) {
		printf("Error creating thread2\n");
		return 1;
	}
	//sleep(1);
	printf("start2\n");
	fflush(stdout);
	send_req() ;
	printf("disc req sent\n");
	f();
	char choice;

	while (1) {
		printf("Please enter what you want to do \n");
		choice = getch();		
		if (choice == 'd') {
			send_req() ;
			printf("disc req sent\n");
			f();
			break;
		} else {
			printf("Please choose from the given options\n");
		}
	}
	if(pthread_join(brlisten_thread, NULL)) {
		printf("Error joining thread serv\n");
		return 2;
	}
	if(pthread_join(disclisten_thread, NULL)) {
		printf("Error joining thread serv2\n");
		return 2;
	}
	
	return 0;
}
