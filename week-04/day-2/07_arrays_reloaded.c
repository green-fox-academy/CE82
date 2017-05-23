#include <stdio.h>

int main() {
    int numbers[] = {5, 6, 7, 8, 9};
    int* number_pointer = &numbers[0];
    //TODO:
    // The "number_pointer" should point to the third element of the array called "numbers",
    number_pointer += 2;
    // than please print its value with it. Solve the problem without reusiong the "&" operator
    printf("%d \n ",*number_pointer);
    // for getting the address of the third element.
    return 0;
}
