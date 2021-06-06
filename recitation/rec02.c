/*
Programmer: Andrew Jacobson
EUID: asj0108
*/
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

int main() {
	//int* ary;
	int * int_ptr = (int*)malloc(8);
	if (int_ptr == NULL) {
		printf("Memory allocation failed.");
		return 1;
	}
	printf("Enter first integer: ");
	scanf("%d", &int_ptr[0]);
	printf("Enter second integer: ");
	scanf("%d", &int_ptr[1]);
	printf("Original values: 1st=   %i     2nd=   %i\n", int_ptr[0], int_ptr[1]);
	int_ptr[0] = int_ptr[0] ^ int_ptr[1];
	int_ptr[1] = int_ptr[0] ^ int_ptr[1];
	int_ptr[0] = int_ptr[0] ^ int_ptr[1];
	printf("Swapped values: 1st=   %i     2nd=   %i\n", int_ptr[0], int_ptr[1]);
	free(int_ptr);

	return 0;
}