// John Edgar
// Thr 5:15
// 4/26/2022
// This code implements the set operations with hash table in the GENERIC directory

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "setG.h"
# include <stdbool.h>
# include <assert.h>

#define F 1
#define D 2
#define E 3

static int search(SET *sp, void *elt, bool *found);

typedef struct set{
	int count;
	int length;
	int *flags;
	void **data;
	int (*compare)();
	unsigned (*hash)();
}SET;

//BigO(n)
// creates sets
SET *createSet(int maxElts, int (*compare)(), unsigned(*hash)()){
	int i;
	SET *sp;
	sp = (SET*)malloc(sizeof(SET));
	assert(sp != NULL);
	sp->count = 0;
	sp->length = 0;
	sp->data = (void **)malloc(sizeof(char*)*maxElts);
	assert(sp->data != NULL);
	sp->flags = (void*)malloc(sizeof(int*)*maxElts);
	assert(sp->flags != NULL);
	//sp->compare = compare;
	//sp->hash = hash;
	for(i = 0; i < sp->length; i++){
		sp->flags[i] = E;
	}
	sp ->compare = compare;
	sp-> hash = hash;
	return sp;	
	
}

//BigO(1)
// destroys the whole set
void destroySet(SET *sp){
	assert(sp != NULL);
//	int i;
//	for(i = 0; i < sp->count; i++){
//		if(sp->flags[i] == F){
//			free(sp->data[i]);
//	}
	free(sp->flags);
	free(sp->data);
	free(sp);	
}

//BigO(1)
// returns the number of sets
int numElements(SET *sp){
	assert(sp != NULL);
	return(sp-> count); 
}

//BigO(n)
// add a single element to the array
void addElement(SET *sp, void *elt){
	//declare variables
	assert(sp != NULL);
        int i;
        bool found = false;
	int j = search(sp, elt, &found);
        
        if(found == true){
                return;
        }       
        
        if(sp->count == sp->length){
                printf("Array is currently full.\n");
                return;
        }       
        
        for(i = sp->count; i > j; i--){
                sp->data[i] = sp->data[i - 1];
        }       
 //     sp->data[j] = strdup(elt);
        sp->count += 1;
        return;

	
}

//BigO(n)
// finds a specific element and removes it
void removeElement(SET *sp, void *elt){
	assert(sp != NULL && elt != NULL);
	//int i;
	bool found = false;
	int j =	search(sp, elt, &found);
	if(found == true){
//		free(sp->data[j]);
		sp->flags[j] = D;
		sp->count--;
	}			
	return;
}

//BigO(n)
// find element and returns it
void *findElement(SET *sp, void *elt){
	assert(sp != NULL && elt != NULL);
       // int i;
        bool found = false;
        int j = search(sp, elt, &found);
        if(found == true){
                return(sp->data[j]);
        }
	return NULL;
}

// BigO(n)

void *getElements(SET *sp){
	assert(sp != NULL);
        int i;
        int j;
	void ** cp = malloc(sizeof(void*)*sp->count);
	assert(cp!= NULL);
	//bool found = false;
        //int i = search(sp, elt, &found);			
	for(i =0; i < sp->length; i++){
		if(sp->flags[i] == F){
			cp[j]= sp->data[i];
			j++;	
		}	
	}
	return cp;	

}

// BigO(n)
static int search(SET *sp, void *elt, bool *found){
	assert(sp != NULL);
    	assert(elt != NULL);
    	int i; 
	int pos;
    	int first = -1;
    	*found = false;
    	unsigned key = sp->hash(elt);
	// strhash(elt) ->(*sp->hash)(elt);
	// strcmp(sp->data[locn], elt) -> (*sp->compare)(sp->data[locn],elt);
    	for(i = 0; i < sp->length; i++){
        	pos = (key + i) % (sp->length);

       		if(sp->flags[pos] == F){
            		if(strcmp(elt, sp->data[pos]) == 0){
                 		*found = true;
                 		return (pos);
            		}
        	}
        	if(sp->flags[pos] == D){
            		first = pos;
        	}
        	if(sp->flags[pos] == E){
            		if(first > -1){
                		return first;
            		}
            		return pos;
        	}
    	}
    	return -1;
} 
