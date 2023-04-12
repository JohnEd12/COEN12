//John Edgar
//COEN 12
//Lab 2 Th 5:15pm
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include <stdbool.h>
#include <assert.h>


static int search(SET *sp, char *elt, bool *found);

typedef struct set{
	int len; 
	int c;
    	char ** p;
} SET;
 
SET *createSet(int maxElts){
	SET *sp;
    	sp = malloc(sizeof(SET));
    	assert(sp != NULL);
    	sp -> c = 0;
    	sp -> len = maxElts;
    	sp -> p = malloc(sizeof(char *)*maxElts);
    	assert(sp->p != NULL);
    	return sp;
}

void destroySet(SET *sp){
	int i;
    	assert(sp != NULL);
    	for(i = 0; i < sp->c;i++){
        	free(sp-> p[i]);
	}
    	free(sp->p);
    	free(sp);
}
void removeElement(SET *sp, char *elt){
        assert(sp != NULL);
        assert(elt != NULL);
        bool found = NULL;
        int index = search(sp, elt, &found);
        if(index == -1)
                return;
        sp->p[index] = sp->p[sp->c-1];
        sp->p[sp->c-1] = NULL;
        sp->c -= 1;
        return;
}

int numElements(SET *sp){
	return (sp->c); 
}

char **getElements(SET *sp){
        int i;
        char **copy = malloc(sizeof(char *)* sp->c);
        for(i = 0; i < sp->c; i++)
                copy[i] = sp->p[i];
        return copy;
}
void addElement(SET *sp, char *elt){
	bool *found = NULL;
    	if(search(sp, elt, found) == -1){
        	if(sp->c== sp->len){
            		printf("Array is currently full.");
            		return;
        	}
        	sp->p[sp->c] = strdup(elt);
        	sp->c += 1;
    	}
    	return;
}

char *findElement(SET *sp, char *elt){
	bool *found = NULL;
    	int temp = search(sp, elt, found);
    	if(temp != -1){
        	return sp->p[temp];
	}
    	return NULL;
}


static int search(SET *sp, char *elt, bool *found){
	int i;
    	found = false;
    	for(i = 0; i < sp->c; i++)
    	{
        	if(strcmp(elt, sp->p[i]) == 0)
            	return i;
    	}
    	return -1;
}
