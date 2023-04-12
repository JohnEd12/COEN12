// John Edgar
// Thr 5:15
// 4/26/2022
// This code implements the set operations with hash table in the STRING directory, it creates multiple sets and uses F,D,or E to determine the status of each data position int he index
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "set.h"
# include <stdbool.h>
# include <assert.h>

#define F 1
#define D 2
#define E 3

static int search(SET *sp, char *elt, bool *found);

//structure of set variables needed
typedef struct set{
	int count;
	int length;
	char *flags;
	char **data;
}SET;

// BigO(n)
// Allocates memory and creates sets
SET *createSet(int maxElts){
	int i;
	SET *sp;
	sp = (SET*)malloc(sizeof(SET));
	assert(sp != NULL);
	sp->count = 0;
	sp->length = 0;
	sp->data = (char **)malloc(sizeof(char*)*maxElts);
	assert(sp->data != NULL);
	sp->flags = (char*)malloc(sizeof(int*)*maxElts);
	assert(sp->flags != NULL);
	for(i = 0; i < sp->length; i++){
		sp->flags[i] = E;
	}
	return sp;	
	
}

//BigO(n)
void destroySet(SET *sp){
	// sees if the set is empty, used thru out the code
	assert(sp != NULL);
	int i;
	// destroys each data one by one
	for(i = 0; i < sp->count; i++){
		if(sp->flags[i] == F){
			free(sp->data[i]);
		}		
	}
	free(sp->flags);
	free(sp->data);
	// frees the set fully once its done destroying each data 
	free(sp);	
}
//BigO(1)
int numElements(SET *sp){
	assert(sp != NULL);
	// returns the number of elements
	return(sp-> count); 
}

//BigO(n)
//add element to the list, it does this by finding the specific place for it
void addElement(SET *sp, char *elt){
	//declare variables
	assert(sp != NULL);
        int i;
        bool found = true;
        int j = search(sp, elt, &found);
        
        if(found == true){
                return;
        }       
        // reaches end of the list
        if(sp->count == sp->length){
                printf("Array is currently full.\n");
                return;
        }       

	
        for(i = sp->count; i > j; i--){
                sp->data[i] = sp->data[i - 1];
        }       
        sp->data[j] = strdup(elt);
        sp->count += 1;
        return;

	
}

//BigO(n)
//searches for specific element to remove it
void removeElement(SET *sp, char *elt){
	assert(sp != NULL && elt != NULL);
	//int i;
	bool found = false;
	int j =	search(sp, elt, &found);
	// if statement is true when the element to remove it found in the list
	if(found == true){
		// free that specific data space then tags it as deleted
		free(sp->data[j]);
		sp->flags[j] = D;
		sp->count--;
	}			
	return;
}

//BigO(n)
// finds element to return, the element thats wanted to find is in the arguement
char *findElement(SET *sp, char *elt){
	assert(sp != NULL && elt != NULL);
       // int i;
        bool found = false;
        int j = search(sp, elt, &found);
        // specific element is found
	if(found == true){
                return(sp->data[j]);
        }
	return NULL;
}

//BigO(n)
char **getElements(SET *sp){
	assert(sp != NULL);
        int i;
        int j;
	char ** cp = malloc(sizeof(char*)*sp->count);
	assert(cp!= NULL);
	//bool found = false;
        //int i = search(sp, elt, &found);			
	for(i =0; i < sp->length; i++){
		if(sp->flags[i] == F){
			memcpy(cp[j], sp->data[i], sizeof(char*)*sp->count);
			j++;	
		}	
	}
	return cp;	

}

//BigO(1)
unsigned strhash(char *s){
	unsigned hash = 0;
	while(*s != '\0'){
		hash = 31 * hash + *s ++;
	}
	return hash;
}

//BigO(n)
//uses the hashing method to search for specific element in the SET 
static int search(SET *sp, char *elt, bool *found){
	assert(sp != NULL);
    	assert(elt != NULL);
    	int i; 
	int pos;
    	int first = -1;
    	*found = false;
    	unsigned key = strhash(elt);

    	for(i = 0; i < sp->length; i++){
		// uses hashing method, the sp->length is the index of the list, this is linear probing 
        	pos = (key + i) % (sp->length);
		
		// if statement if position is already filled with data
       		if(sp->flags[pos] == F){
            		if(strcmp(elt, sp->data[pos]) == 0){
                 		*found = true;
                 		return (pos);
            		}
        	}
		// if statement if data in position was deleted
        	if(sp->flags[pos] == D){
            		first = pos;
        	}
        	// if statement if position is empty
		if(sp->flags[pos] == E){
            		if(first > -1){
                		return first;
            		}
            		return pos;
        	}
    	}
    	return -1;
} 
