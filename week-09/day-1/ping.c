
#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <string.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
//#include <linux/ip.h>
//#include <linux/icmp.h>
 

char dst_addr[20];
char src_addr[20];
 
unsigned short in_cksum(unsigned short *, int);
void parse_argvs(char**, char*, char* );
void usage();
char* getip();
char* toip(char*);
 
int main(int argc, char* argv[])
{
    struct iphdr* ip;
    struct iphdr* ip_reply;
    struct icmphdr* icmp;
    struct sockaddr_in connection;
    char* packet;
    char* buffer;
    int sockfd;
    int optval;
    int addrlen;
    int siz; 
     
    if (getuid() != 0) {
    	fprintf(stderr, "%s: root privelidges needed\n", *(argv + 0));
    	exit(EXIT_FAILURE);
    }
 
    parse_argvs(argv, dst_addr, src_addr);
    strncpy(dst_addr, toip(dst_addr), 20);
    strncpy(src_addr, toip(src_addr), 20);
    printf("Source address: %s\n", src_addr);
    printf("Destination address: %s\n", dst_addr);
    
    packet = malloc(sizeof(struct iphdr) + sizeof(struct icmphdr));
    buffer = malloc(sizeof(struct iphdr) + sizeof(struct icmphdr));
    /****************************************************************/
     
    ip = (struct iphdr*) packet;
    icmp = (struct icmphdr*) (packet + sizeof(struct iphdr));
 
    // ip packet
	ip->ihl          = 5; //Internet Header Length 
	//The minimum value for this field is 5
    ip->version      = 4; //For IPv4, this is always equal to 4
    ip->tos          = 0; //Type of service
    ip->tot_len      = sizeof(struct iphdr) + sizeof(struct icmphdr);
    ip->id           = htons(0);
    ip->frag_off     = 0;//fragment offset
    ip->ttl          = 64;//time to live
    ip->protocol     = IPPROTO_ICMP;
    ip->saddr        = inet_addr(src_addr);
    ip->daddr        = inet_addr(dst_addr);
    ip->check        = in_cksum((unsigned short *)ip, sizeof(struct iphdr));
     
    if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1) {
    	perror("socket");
    	exit(EXIT_FAILURE);
    }
     
    /* 
     *  IP_HDRINCL must be set on the socket so that
     *  the kernel does not attempt to automatically add
     *  a default ip header to the packet
     */
     
    setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &optval, sizeof(int));
     
    // icmp packet, checksum
    icmp->type           = ICMP_ECHO;
    icmp->code           = 0;
    icmp->un.echo.id     = random();
    icmp->un.echo.sequence   = 0;
    icmp-> checksum      = in_cksum((unsigned short *)icmp, sizeof(struct icmphdr));
     
     
    connection.sin_family = AF_INET;
    connection.sin_addr.s_addr = inet_addr(dst_addr);
    //packet sent:     
    sendto(sockfd, packet, ip->tot_len, 0, (struct sockaddr *)&connection, sizeof(struct sockaddr));
    printf("Sent %d byte packet to %s\n", ip->tot_len, dst_addr);
     
    /*
     *  now we listen for responses
     */
    addrlen = sizeof(connection);
    if (( siz = recvfrom(sockfd, buffer, sizeof(struct iphdr) + sizeof(struct icmphdr), 0, (struct sockaddr *)&connection, &addrlen)) == -1) {
    	perror("recv");
    }
    else {
		printf("Received %d byte reply from %s:\n", siz , dst_addr);
		    ip_reply = (struct iphdr*) buffer;
		printf("ID: %d\n", ntohs(ip_reply->id));
		printf("TTL: %d\n", ip_reply->ttl);
	}
    free(packet);
    free(buffer);
    close(sockfd);
    return 0;
}
void parse_argvs(char** argv, char* dst, char* src) //az eredeti argv egy pointer, ami egy char tömbre mutat, átadva egy erre mutató pointer
{
//**(argv + 1) a beütött cím első betűje
	//printf("<%c>",**(argv+2));
    int i;
    if(!(*(argv + 1))) { 
    /* there are no options on the command line */  
     //(*(argv + 1)) NULL
   		fprintf(stderr, "\nUsage: ./p [destination] \n");
		exit(EXIT_FAILURE); 
    }
    if (*(argv + 1) && (!(*(argv + 2)))) {
    	strncpy(dst, *(argv + 1), 15);
    	strncpy(src, getip(), 15); //localhost
    	return;
    }
}
char* getip()
{
    char buffer[256];
    struct hostent* h;
     
    gethostname(buffer, 256);
    h = gethostbyname(buffer);
     
    return inet_ntoa(*(struct in_addr *)h->h_addr);     
}
 
/*
 * return the ip address if host provided by DNS name
 */
char* toip(char* address)
{
    struct hostent* h;
    h = gethostbyname(address);
    return inet_ntoa(*(struct in_addr *)h->h_addr);
}
 

unsigned short in_cksum(unsigned short *addr, int len) 
{
    register int sum = 0;
    u_short answer = 0;
    register u_short *w = addr;
    register int nleft = len;
    /*
     * Our algorithm is simple, using a 32 bit accumulator (sum), we add
     * sequential 16 bit words to it, and at the end, fold back all the
     * carry bits from the top 16 bits into the lower 16 bits.
     */
     //végigmegy a csomagon, egyszerre két bájtnyi adat, összeadja sum-ba
    while (nleft > 1) {
    	sum += *w++;
    	nleft -= 2; //azért -2 mert u_short két bájtos
    }
    /* mop up an odd byte, if necessary */
    if (nleft == 1) { //páratlan számú bájt a csomag
		*(u_char *) (&answer) = *(u_char *) w;
		sum += answer;
    }
    /* add back carry outs from top 16 bits to low 16 bits */
    sum = (sum >> 16) + (sum & 0xffff);       /* add hi 16 to low 16 */
    sum += (sum >> 16);               /* add carry */
    answer = ~sum;              /* truncate to 16 bits */
    return (answer);
}
