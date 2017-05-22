#include <stdio.h>


struct RectangularCuboid {
    double a;
    double b;
    double c;
}x;

double GetSurface(struct RectangularCuboid rc){	
	return rc.a*rc.b*2+rc.a*rc.c*2+rc.c*rc.b*2;
}
double GetVolume(struct RectangularCuboid rc){	
	return rc.a*rc.b*rc.c;
}
// TODO:
// Write a function called "GetSurface" that takes a RectangularCuboid
// and returns it's surface

// TODO:
// Write a function called "GetVolume" that takes a RectangularCuboid
// and returns it's volume

int main() {
	x.a=2;
	x.b=3;
	x.c=5;
	printf("%.2f\n",GetVolume(x));
	printf("%.2f\n",GetSurface(x));
    return 0;
}
