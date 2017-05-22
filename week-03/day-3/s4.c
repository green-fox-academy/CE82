#include <stdio.h>

struct Pirate {
    char name[256];
    int has_wooden_leg;
    short int gold_count;
};

// TODO:
// Create a function that takes an array of pirates (and it's length) then returns the sum of the golds of all pirates
int sum(struct Pirate *p, int len){
	int Sum=0;
	struct Pirate*pptr=p;
	for (int i=0;i<len;i++){
		Sum+=pptr->gold_count;
		pptr++;
	}
	return Sum;
}

// TODO:
// Create a function that takes an array of pirates (and it's length) then returns the average of the gold / pirate

float avg(struct Pirate *p, int len){
	
	return (float)sum(p,len)/len;
}
// TODO:
// Create a function that takes an array of pirates (and it's length) then returns the name of the
// richest that has wooden leg
char* akarmi(struct Pirate *p, int len){
	struct Pirate*pptr=p;
	int max=0, maxgold=0;
	char*nev=" ";
	for (int i=0;i<len;i++){
		if(pptr->has_wooden_leg){
			if(maxgold<pptr->gold_count) {
				maxgold=pptr->gold_count;
				max=i;
				nev=pptr->name;
			}
		}
		pptr++;
	}
	
	return nev;
	
}

int main() {
    struct Pirate pirates[] = {
        {"Jack", 0, 18},
        {"Uwe", 1, 8},
        {"Hook", 1, 12},
        {"Halloween kid", 0, 0},
        {"Sea Wolf", 1, 14},
        {"Morgan", 0, 1}
    };
    struct Pirate* p=pirates;
	printf("%s\n",akarmi(p,6));
    return 0;
}
