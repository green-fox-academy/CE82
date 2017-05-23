#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x;
    int y;
} point_t;

point_t *construct(int x, int y)
{
	point_t *p= malloc(sizeof (point_t));
	p->x=x;
	p->y=y;
	return p;
}
double distance (point_t *p1, point_t *p2)
{
	int distx = p1->x - p2->x;
	if(distx < 0)
		distx* = -1;
	int disty = p1->y - p2->y;
	if(disty < 0)
		disty* = -1;
	
	return sqrt((double)distx * distx + disty * disty);
}
// TODO:
// Create a function the constructs a Point (returns a pointer to a new point)
// It should take it's x and y coordinate as parameter

// TODO:
// Create a function that takes 2 Points as a pointer and returns the distance between them

int main()
{
	point_t *p1 = construct(10, 20);
	point_t *p2 = construct(11, 19);
	printf("%.3f \n", distance(p1, p2));
    return 0;
}
