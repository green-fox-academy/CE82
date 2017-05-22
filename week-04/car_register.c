#include <string.h>
#include <stdio.h>
int size=0;
typedef enum transmission {manual, automatic, CVT, semiauto, dualc};
struct car {
	char mname[255];
    float price;
    int year;
    enum transmission tr;
};

int get_older_cars_than(struct car* array, int age){
	int num=0;
	for(int i=0;i<size;i++){
		if((array->year) < age){
			num++;
		}
		array++;
	}
	return num;
}

int get_transmission_count(struct car* array, enum transmission trnsm){
	int num=0;
	for(int i=0;i<size;i++){
		if((array->tr) ==trnsm){
			num++;
		}
		array++;
	}
	return num;
}
int main() {
    struct car cars[] = {
        {"mname1", 100, 1982, manual},
        {"mname2", 200, 1984, automatic},
        {"mname3", 100, 1991, CVT},
        {"mname2", 220, 1988, automatic},
    };
    struct car* p=cars;
    size=4;
    
    printf("%d\n",get_older_cars_than(p,1990));
    printf("%d\n",get_transmission_count(p,manual));
    return 0;
}
/* Write a car register!
 * You should store the following data in a structure, called "car":
 *  - the manufacturer's name (which is shorter than 256 characters)
 *  - the price of the car (in euros, stored as a floating point number)
 *  - the year of manufacture
 *  - the type of the transmission (as a custom type, see below)
 *
 * You should store the transmission type in an enumeration ("transmission"),
 * the valid types are:
 *  - manual
 *  - automatic
 *  - CVT
 *  - semi-automatic
 *  - dual-clutch
 *
 * The "car"-s are stored in an array.
 *
 * Write the following functions:
 *  - get_older_cars_than(struct car* array, int age)
 *      - it returns the count of the older cars than "age"
 *  - get_transmission_count(struct car* array, enum transmission trnsm)
 *      - it returns the count of cars which has "trnsm" transmission
 */


