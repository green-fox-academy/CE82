#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
//#include <unistd.h>
 
#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which to listen for incoming data
 
void die(char *s){
    perror(s);
    exit(1);
}
 
int main(void){
    struct sockaddr_in si_me, si_seeder, si_leecher;
     
    int s, i, slen = sizeof(si_seeder) , recv_len;
    char buf[BUFLEN], buf2[BUFLEN];
     
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
        die("socket");
    }
    memset((char *) &si_me, 0, sizeof(si_me)); 
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1){
        die("bind");
    }
    memset(buf,'\0', BUFLEN);
    //először várja a seedert
    printf("Seederre várok... ");
    fflush(stdout);  
    printf(" ... "); fflush(stdout);  
    if ((recv_len=recvfrom(s, buf, BUFLEN,0,(struct sockaddr *) &si_seeder, &slen))==-1){
            die("recvfrom()");
        }
    
    memset(buf,'\0', BUFLEN);
    printf("seeder címe %s:%d\n",inet_ntoa(si_seeder.sin_addr), ntohs(si_seeder.sin_port));
    printf("Leecherre várok... ");fflush(stdout); 
    if ((recv_len=recvfrom(s, buf, BUFLEN,0,(struct sockaddr *) &si_leecher, &slen))==-1){
            die("recvfrom()");
    }
    
    snprintf(buf,512,"%s:%d",inet_ntoa(si_seeder.sin_addr), ntohs(si_seeder.sin_port));
    printf("leecher bejelentkezett, küldöm seeder címét neki\n");
    if (sendto(s, buf, strlen(buf) , 0 , (struct sockaddr *) &si_leecher, slen)==-1){
        die("sendto()");
    }
    printf(" cím küldése sikeres");

    close(s);
    return 0;
}
