#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
# define EMPTY 0
# define FILLED 1
# define DELETED 2

//Create struct set with data, length, count
typedef struct set{
  char** data;
  int length;
  int count;
  char *flags;
}SET;
SET *sp;

static int search(SET *sp,char *elt, bool *found);

//return a pointer to a new set with a maximum capacity of maxElts
SET *createSet(int maxElts) {
  SET *sp = malloc(sizeof(SET));
  assert(sp!=NULL);
  sp->count=0;
  sp->length=maxElts;
  sp->data=malloc(sizeof(char*) * maxElts);
  assert(sp->data!= NULL);
  sp->flags=malloc(sizeof(char)*maxElts);
  for(int i=0;i<maxElts;i++)
    sp->flags[i]=EMPTY;
  return sp;
}

//hash function
unsigned strhash(char *s){
  unsigned hash = 0;
  while(*s != '\0')
	hash = 31 * hash + *s ++;
  return hash;
}

//deallocate memory associated with the set pointed to by sp
void destroySet(SET *sp) {
  for(int i=0; i<sp->length; i++){
    if(sp->flags[i]==FILLED)
      free(sp->data[i]);
  }
  free(sp->flags);
  free(sp->data);
  free(sp);
}

//return the number of elements in the set pointed to by sp
int numElements(SET *sp) {
  return sp->count;
}

//add elt to the set pointed to by sp
void addElement(SET *sp, char *elt) {
  assert(sp!=NULL || elt!=NULL);    //asserts if sp is NULL or element does not exist
  bool found;
  int index = search(sp, elt, &found);
  if(found)
    return;
  sp->flags[index]=FILLED;
  sp->data[index]=strdup(elt);
  sp->count++;
}

//remove elt from the set pointed to by sp
void removeElement(SET *sp, char *elt) {
  bool found;
  int index = search(sp, elt, &found);
  if(found) {
    free(sp->data[index]);
    sp->flags[index]=DELETED;
    sp->count--;
  }
}

//if elt is present in the set pointed to by sp then return the matching element, otherwise return NULL
char *findElement(SET *sp, char *elt) {
  assert(sp!=NULL);
  bool found;
  int index = search(sp, elt, &found);
  if(found)
    return sp->data[index];
  return NULL;
}

//allocate and return an array of elements in the set pointed to by sp
char **getElements(SET *sp) {
  char **elts;
  elts = malloc(sizeof(char*)*sp->count);
  int j=0;
  for(int i=0; i<sp->length; i++) {
    if(sp->flags[i]==FILLED) {
	  elts[j]=sp->data[i];
	  j++;
	}
  }
  return elts;
}

//search for the element and if it exists, return its position
static int search(SET *sp, char *elt, bool *found) {
  assert(sp!=NULL);
  unsigned index = strhash(elt)%sp->length;
  bool firstDelete=true;
  int indexFirstDelete;
  if(sp->flags[index]==EMPTY){
    *found=false;
    return index;
  }
  else while(sp->flags[index]==FILLED||sp->flags[index]==DELETED){
    if(sp->flags[index]==DELETED){
      if(firstDelete){
        firstDelete=false;
        indexFirstDelete=index;
      }
    }
    else {
      if(strcmp(elt,sp->data[index])==0){
        *found=true;
        return index;
      }
    }
    index=(index+1)%sp->length;
  }
  *found=false;
  if(!firstDelete)
    return indexFirstDelete;
  return index;
}

