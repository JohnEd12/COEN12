// John Edgar
// 4/17/2022
// sorted.c

#include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "set.h"
# include <stdbool.h>
# include <assert.h>

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

void destroySet(SET *sp)
{
	int i;
	assert(sp != NULL);
    	for(i = 0; i < sp->c;i++)
        	free(sp-> p[i]);
    	free(sp->p);
    	free(sp);
	return;
}

int numElements(SET *sp){	
	assert(sp != NULL);
	return (sp->c); 
}

void addElement(SET *sp, char *elt){
    	assert(sp != NULL);
    	int i;
    	bool found = true;
    	int index = search(sp, elt, &found);

    	if(found == true){
		return;
	} 

    	if(sp->c == sp->len){
        	printf("Array is currently full.\n");
        	return;
    	}
   
    	for(i = sp->c; i > index; i--){
        	sp->p[i] = sp->p[i - 1];
    	}
    	sp->p[index] = strdup(elt);
    	sp->c += 1;
    	return;
}

void removeElement(SET *sp, char *elt){
    	assert(sp != NULL);
    	bool found = false;
    	int i;
    	int index = search(sp, elt, &found);

    	if(found == true){
        	free(sp->p[index]);
        	for(i = index + 1; i < sp->c; i++){
             		sp->p[i - 1] = sp->p[i];
        	}
        	sp->c -= 1;
    	}
    	return; 
}

char *findElement(SET *sp, char *elt){
	assert(sp != NULL);
    	bool found = true;
    	int temp = search(sp, elt, &found);
    	if(found == true){
        	return sp->p[temp];
	} 
   	return NULL;
}
char **getElements(SET *sp){
	assert(sp != NULL);
    	int i;
    	char **copy = malloc(sizeof(char *)* sp->c);
    	for(i = 0; i < sp->c; i++)
        	copy[i] = sp->p[i];
    	return copy;
} 
static int search(SET *sp, char *elt, bool *found)
{
	assert(sp != NULL);
	int mid;
	int low = 0;
	int high = sp->c - 1;
	while(low <= high)
    	{
        	mid = ((high + low) / 2);
        
        	if(strcmp(sp->p[mid], elt) < 0)
            		high = mid - 1;
        	if(strcmp(sp->p[mid], elt) > 0)
            		low = mid + 1;
        	if(strcmp(elt, sp->p[mid]) == 0)
		{
            		*found = true;
            		return mid;
		}
    	}
    	*found = false; 
    	return low; 
}
