#include <stdio.h>
#include <stdlib.h>

// TODO:
// Create a function that takes a double array as a parameter, and the length of the array.
// This function should calculate the avarage of the elements.

// TODO:
// Create an other function that takes a double array as a parameter, and the length of the array.
// It calculates how much elements are under the avarage, and returns with that.

// TODO:
// Create an other function that takes a double array as a parameter, and the length of the array.
// It allocates a new array, and loads into it the elements which are under the average.
// It returns a pointer to the new array.
double* under_average(double *a, int l)
{
	double *arr1, *arr2, *arr3;
	arr1 = a;
	double avg = 0;
	//kiszámolom az átlagot
	for (int i=0; i < l;i++) {
		avg += *arr1;
		arr1++;
	}
	avg/=l;
	printf("avg: %.3f \n", avg);
	//létrehozok megfelelő méretű új tömböt és feltöltöm
	arr1 = a;
	arr2 = calloc(l, sizeof (double)); 
	arr3 = arr2;
	for (int i=0; i<l;i++) {
		if (*arr1 < avg) {
			*arr3 = *arr1;
			arr3++;
		}
		arr1++;
	}
	return arr2;
}

int main()
{
	double arr[] = {1, 3, 2, 0.5};
	double *arr2, *arr1;
	arr1 = &arr;
	int l = 4;
	arr2 = under_average(arr1, l);
	for (int i = 0; i < l;  i++) {
		printf("%.3f \n", *arr2);
		arr2++;
	}
    return 0;
}
