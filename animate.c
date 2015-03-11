#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, const char *argv[]){
	system("clear;stty raw");
	int i;
	for (i = 0; i < 100; i++){
		fprintf(stderr, "x");
	}
	fprintf(stderr, "this is a message");
	//for (i = 0; i < strlen("this is a message"); i++){
	//	fprintf(stderr, "\b");
	//}
	system("sleep 3");
	fprintf(stderr,"\r");
	//for (i = 0; i < 100; i++){
	//fprintf(stderr, "\b");
	//}
	for (i = 0; i < 100; i++){
		fprintf(stderr, "+");
	}
	system("sleep 3");
	system("stty cooked");
	return 0;
}
