#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[]){
	system("clear; stty raw");
	int i;
	for (i = 0; i < 10; i++){
		fprintf(stdout, "x");
	}
	fprintf(stdout, "\n");
	fprintf(stdout, "this is a message");
	system("sleep 3");
	fprintf(stdout, "\033[F");
	for (i = 0; i < strlen("this is a message"); i++){
		fprintf(stdout, "\b");
	}
	system("sleep 3");
	//fprintf(stdout,"\r");
	for (i = 0; i <= 10; i++){
		fprintf(stdout, "\b");
	}
	for (i = 0; i < 10; i++){
		fprintf(stdout, "+");
	}
	system("sleep 3");
	system("stty cooked");
	return 0;
}
