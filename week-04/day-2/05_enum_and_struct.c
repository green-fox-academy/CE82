#include <stdio.h>

enum CarType {VOLVO, TOYOTA, LAND_ROVER, TESLA};

struct Car {
  enum CarType type;
  double km;
  double gas;
}car;
void f(struct Car c) 
{
	if(c.type != TESLA){
		printf("gas: %.2f\n", c.gas);
	}
	printf("km: %.2f\n", c.km);
}
// TODO:
// Write a function that takes a Car as an argument and prints all it's stats
// If the car is a Tesla it should not print it's gas level

int main() {
	car.type = VOLVO;
	car.km = 46;
	car.gas = 56;
	f(car);
	return 0;
}
