// Andrew Jaocbson - asj0108
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define SIZE 50

pthread_mutex_t lock;
int status;

char sentence[2000];
int ind = 0;

char convertUpperCase(char lower){
	if ((lower > 96) && (lower < 123)){
		return (lower - 32);
	}else{
		return lower;
	}
}

void printChar(){
	
	printf("The new sentence is [%d]: \t%c\n", ind, sentence[ind]);
	ind++;
	
}

void *convertMessage(void *ptr){
	pthread_mutex_lock(&lock);
	if (ind % 2){
		sentence[ind] = convertUpperCase(sentence[ind]);
	}
	printChar();
	pthread_mutex_unlock(&lock);
	return 0;
}

int main(){
	int i;
	char buffer[SIZE];
	char *p;
	pthread_t ts[SIZE];
	status = pthread_mutex_init(&lock, NULL);

	printf("Please enter a phrase (less than 50 characters): ");
	
	if (fgets(buffer, sizeof(buffer), stdin) != NULL){
		if((p = strchr(buffer, '\n')) != NULL){
			*p = '\0';
		}
	}
	strcpy(sentence, buffer);

	printf("The original sentence is: \t %s\n", sentence);

	for (i = 0; i < strlen(buffer) + 1; ++i){
		pthread_create(&ts[i], NULL, convertMessage, NULL);
	}

	for (i = 0; i < strlen(buffer); i++){
		pthread_join(ts[i], NULL);
	}
	status = pthread_mutex_destroy(&lock);

	printf("\n");
	return 0;
}
