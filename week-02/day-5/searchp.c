#include <stdio.h>
#include <string.h>



char* forditva(char*v, int l){
	char c[l];
	int i=0;
	if(l==1){return v;}
	for(i=0; i<l;i++){
		c[i]=v[l-i-1];
	}
	c[i]='\0';
	char *cc=c;
	return cc;
}
char* stringcp(char*s, int honnan, int mennyit, int merre){
	char c[255];	
	int i;
	if(merre==1){
		for(i=honnan; i<honnan+mennyit; i+=merre){	  
			c[merre*(i-honnan)]=s[i];
		}
	}
	if(merre==-1){
		for(i=honnan; i>honnan+merre*mennyit; i+=merre){	  
			c[merre*(i-honnan)]=s[i];
		}
	}
	//printf("i-honnan: %d \n",i-honnan);
	c[i-honnan]='\0';
	
	char* cp = c;
	return cp;
}
void s_pali(char*s,int l){
	if(l<3) return;
	char c1[l], c2[l];
	
	for(int i=0; i<=((l));i++){
		for(int j=1; j<=i;j++){			
			strcpy(c1,stringcp(s,i+1,j, 1));
			strcpy(c2,stringcp(s,i-1,j,-1)); 			
			if (!strcmp (c1,c2)){ 				
				printf("----> %s%c%s",forditva(c2,j),s[i],c1);
				puts("");
			}
		}
		//és párosra, ami hosszabb:
		for(int j=2; j<=i;j++){			
			strcpy(c1,stringcp(s,i+1,j, 1));
			strcpy(c2,stringcp(s,i,j,-1)); 			
			if (!strcmp (c1,c2)){ 				
				printf("-----> %s%s",forditva(c2,j),c1);
				puts("");
			}
		}
	}
	
	return;
}

int main() {
    char b1[255]; 
    puts ("szó:");  
	gets(b1);
	s_pali(b1,strlen(b1));

    return 0;
}
