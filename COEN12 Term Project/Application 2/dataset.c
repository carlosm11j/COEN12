#include "set.h"

//O(1)
//Create student node with id and age
struct node {
  int id;
  int age;
};

//O(1)
//Create class struct with array of student nodes, count, and length
struct class {
  NODE **student;
  int count;
  int length;
};

//O(n)
//Create array of linked lists to hold all students
CLASS* createDataSet(int maxElts){
  CLASS *lp = malloc(sizeof(CLASS));
  assert(lp != NULL);
  lp->count = 0;
  lp->length = maxElts;
  lp->student = malloc(sizeof(NODE*)*maxElts);
  assert(lp->student != NULL);
  for(int i=0; i<maxElts; i++) {
    lp->student[i] = malloc(sizeof(NODE));
    assert(lp->student[i] != NULL);
  }
  return lp;
}

//O(n)
//Delete list and free memory
void destroyDataSet(CLASS* lp){
  assert(lp != NULL);
  //Free each student in each array
  for(int i = 0; i < lp->length; i++){
    if(lp->student[i] == NULL){
      free(lp->student[i]);//free each student's info
    }
  }
  free(lp->student);
  free(lp);
}

//O(1)
//return ID if the ID is found, -1 if not
int searchID(CLASS* lp, int id){
  assert(lp != NULL);
  printf("***Search for ID: %d***\n", id);
  if(lp->student[id]->id == id)
    return id;
  return -1;
}

//O(1)
//insert new student with id and age
void insert(CLASS* lp, int id, int age){
  assert(lp != NULL && lp->count < lp->length);
  lp->student[id]->id = id;
  lp->student[id]->age = age;
  printf("ID: %d Age: %d\n", lp->student[id]->id, lp->student[id]->age);
  lp->count++;
}

//O(1)
//delete student from list based on id
void delete(CLASS* lp, int id){
  assert(lp != NULL);
  int index = searchID(lp, id);
  if(index > 0) {
    printf("***Student found***\n");
    printf("***ID: %d Age: %d***\n", lp->student[index]->id, lp->student[index]->age);
    free(lp->student[index]);
    lp->count--;
  }
  else
    printf("***Student not found***\n");
}
