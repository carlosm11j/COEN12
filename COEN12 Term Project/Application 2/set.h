#ifndef SET_H
#define SET_H

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>

typedef struct class CLASS;
typedef struct node NODE;

CLASS* createDataSet(int);
void destroyDataSet(CLASS*);
int searchID(CLASS*, int);
void insert(CLASS*, int, int);
void delete(CLASS*, int);

#endif
