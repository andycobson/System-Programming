/*
Programmer: Andrew Jacobson
EUID: asj0108
*/
#include <stdio.h>
#pragma warning(disable: 4996)

int main() {
	unsigned char inputChar;
	int bin;
	int temp;

	printf("Enter an ASCII character: ");
	scanf(" %c", &inputChar);
	printf("You entered: %c\n", inputChar);
	int inputInt = inputChar;
	printf("   dec --  %u\n", inputChar);
	printf("   hex --  %x\n", inputChar);
	printf("   bin --  ");
	for (int i = 7; i >= 0; --i) {
		temp = inputInt >> i;
		if ((temp & 1) == 1) {
			printf("1");
		}else {
			printf("0");
		}
	}
	printf("\n");
	return 0;
}