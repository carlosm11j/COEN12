#ifndef SET_H
#define SET_H

#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

typedef struct class CLASS;
typedef struct list LIST;
typedef struct student STUDENT;

CLASS* createDataSet(int);
void destroyDataSet(CLASS*);
int search(CLASS*, int);
void insert(CLASS*, int, int);
void delete(CLASS*, int);
int maxAgeGap(CLASS*);

#endif
