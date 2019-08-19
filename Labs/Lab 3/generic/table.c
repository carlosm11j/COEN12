#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"
#define EMPTY 0
#define FILLED 1
#define DELETED 2

//Create struct set with data, length, count
typedef struct set{
  void **data;
  int length;
  int count;
  char *flags;
  int (*compare)();
  unsigned (*hash)();
}SET;
SET *sp;

static int search(SET*, void*, bool*);

//return a pointer to a new set with a maximum capacity of maxElts
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()) {
  assert(compare != NULL && hash != NULL);
  
  sp = malloc(sizeof(SET));
  assert(sp!=NULL);
  sp->data = malloc(sizeof(char*)*maxElts);
  assert(sp->data!=NULL);
  sp->flags = malloc(sizeof(char) * maxElts);
  assert(sp->flags != NULL);

  sp->compare = compare;
  sp->hash = hash;
  sp->length = maxElts;
  sp->count = 0;

  for (int i=0; i<maxElts; i++)
    sp->flags[i] = EMPTY;

  return sp;
}

//deallocate memory associated with the set pointed to by sp
//O(1)
void destroySet(SET *sp) {
  assert(sp != NULL);
  free(sp->flags);
  free(sp->data);
  free(sp);
}

//return the number of elements in the set pointed to by sp
//O(1)
int numElements(SET *sp) {
  assert(sp != NULL);
  return sp->count;
}

//add elt to the set pointed to by sp
//O(n)
void addElement(SET *sp, void *elt) {
  assert(sp != NULL && elt != NULL);
  bool found;
  int index = search(sp, elt, &found);
  if(!found) {
    assert(sp->count < sp->length);
    sp->data[index] = elt;
    sp->flags[index] = FILLED;
    sp->count++;
  }
}

//remove elt from the set pointed to by sp
//O(1)
void removeElement(SET *sp, void *elt) {
  bool found;
  int index = search(sp, elt, &found);
  assert(sp != NULL && elt != NULL);
  if(found) {
    sp->flags[index] = DELETED;
    sp->count--;
  }
}

//if elt is present in the set pointed to by sp then return the matching element, otherwise return NULL
//O(n)
void *findElement(SET *sp, void *elt) {
  bool found;
  assert(sp != NULL && elt != NULL);
  int index = search(sp, elt, &found);
  if(found)
    return sp->data[index];
  else
    return NULL;
}

//allocate and return an array of elements in the set pointed to by sp
//O(1)
void *getElements(SET *sp) {
  void **elts;
  elts = malloc(sizeof(void*)*sp->count);
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
static int search(SET *sp, void *elt, bool *found) {
  assert(sp!=NULL);
  int available, index;
  available = -1;
  int start = (*sp->hash)(elt) % sp->length;
  for(int i=0; i<sp->length; i++) {
    index = (start + i) % sp->length;
    if(sp->flags[index] == EMPTY) {
      *found = false;
      return available != -1 ? available : index;
    }
    else if (sp->flags[index] == DELETED) {
      if(available == -1)
        available = index;
    }
    else if ((*sp->compare)(sp->data[index], elt) == 0) {
      *found = true;
      return index;
    }
  }
  *found = false;
  return available;
}

