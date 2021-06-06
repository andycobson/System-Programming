/*
Andrew Jacobson - asj0108
Minor Assignment 3
3/17/2021

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	char args[20][10]; 	// String array for parsing the buffer
	char buffer[50];   	// Char array to hold user input
	char *p;		// Pointer to be used for inputting null value in buffer
	int i, index, size;	// i and index are used for indexing; size for initializing const argv string array
	const char s[2] = " ";	// char array to hold the deliminator for strtok
	char *token;		// String variable to hold strtok return

	// Main while loop for the program
	while (1){
		index = 0;	     // indexing variable set to 0 for every pass
		printf("minor3> ");  // Command prompt output
		
		// Use fgets to set buffer as user input, remove escape sequence. 
		if (fgets(buffer, sizeof(buffer), stdin) != NULL){
			if((p = strchr(buffer, '\n')) != NULL){
				*p = '\0';
			}
		}
		token = strtok(buffer, s);          // Set token variable as strtok return value

		// This loop will use strtok to parse our input buffer array and copy it to a string array
		while( token != NULL ){
			strcpy(args[index], token);
			token = strtok(NULL, s);
			index++;
		}

		size = (index * 4) + 4;     	// Finding the needed array size for the const char array
		char *argv[size]; 				// Declare const char for execvp
		
		// Loop to set buffer array to final const array for execvp arguments 
		for ( i = 0; i < index; i++){
			argv[i] = args[i];
		}
		
		argv[index] = ((char *)0); 		// Set the last element of array to null.

		// Compare strings to see if input is equal to quit,, if so then exit main.
		if (strcmp(argv[0], "quit") == 0){
			return -1;
		}

		// Fork to create child process that will handle the execution.
		if(fork() == 0){
			execvp( argv[0], argv); 	// Takes in the command and an array of argumenta.
			printf("%s: command not found\n", argv[0]); // If execvp fails, it is probably a command from system library
			exit(1);
		}
		else {
			wait( (int *)0 ); 			// Parent process will wait for child to be finished

			// Clear memory from all arrays
			memset(args, 0, sizeof(args));
			memset(argv, 0, sizeof(argv));
			memset(buffer, 0, sizeof(buffer));
		}

	}

	return 0;
}
