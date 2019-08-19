#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

//Create struct set with data, length, count
typedef struct set{
  char** data;
  int length;
  int count;
}SET;
SET *sp;

static int search(SET*, char*);

//return a pointer to a new set with a maximum capacity of maxElts
SET *createSet(int maxElts) {
  SET *sp = malloc(sizeof(SET));
  assert(sp!=NULL);
  sp->length = maxElts;
  sp->count = 0;
  sp->data = malloc(sizeof(char*)*maxElts);
  assert(sp->data!=NULL);
  return sp;
}

//deallocate memory associated with the set pointed to by sp
void destroySet(SET *sp) {
  assert(sp!=NULL);
  for(int i=0; i<sp->count; i++)
    free(sp->data[i]);
  free(sp->data);
  free(sp);
}

//return the number of elements in the set pointed to by sp
int numElements(SET *sp) {
  return sp->count;
}

//add elt to the set pointed to by sp
void addElement(SET *sp, char *elt) {
  if(search(sp, elt)==-1) {
    sp->data[sp->count] = strdup(elt);
    sp->count++;
  }
}

//remove elt from the set pointed to by sp
void removeElement(SET *sp, char *elt) {
  int index = search(sp, elt);
  if(index>=0) {
    free(sp->data[index]);
    sp->data[index] = sp->data[sp->count-1];
    sp->count--;
  }
}

//if elt is present in the set pointed to by sp then return the matching element, otherwise return NULL
char *findElement(SET *sp, char *elt) {
  int index = search(sp, elt);
  if(index>=0)
    return sp->data[index];
  else
    return NULL;
}

//allocate and return an array of elements in the set pointed to by sp
char **getElements(SET *sp) {
  char **elts;
  assert(elts!=NULL);
  elts = malloc(sizeof(char*)*sp->count);
  memcpy(elts, sp->data, sizeof(char*)*sp->count);
  return elts;
}

//search for the element and if it exists, return its position
static int search(SET *sp, char *elt) {
  assert(sp!=NULL);
  for(int i=0; i<sp->count; i++) {
    if(strcmp(sp->data[i], elt) == 0)
      return i;
  }
  return -1;
}

