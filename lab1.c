//John Edgar 
// 3-31-2022
//Thursdays 5:15pm
//Lab 1 - Counting the number of words
#define MAX_WORD_LENGTH 30
#include <stdlib.h>
#include <stdio.h>

int main(int argc,char *argv[]){
	int count = 0;
	FILE *fp;
	fp = fopen(argv[1], "r");
	char word[MAX_WORD_LENGTH+1];
	if (fp == NULL){
		printf("File is empty");
	}
	while(fscanf(fp,"%s",word) == 1){
		count++;
	} 
	printf("%d\n", count);
	fclose(fp);
	return;
}

