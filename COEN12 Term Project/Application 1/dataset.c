#include "set.h"

//O(1)
//Create struct student with next/prev pointers, age, and id
struct student{
  STUDENT* next;
  STUDENT* prev;
  int age;
  int id;
};

//O(1)
//Create struct list with age count, and head to dummy node
struct list{
  int ageCount;
  STUDENT *head;
};

//O(1)
//Create struct class with an array of LIST, student count, length
struct class{
  LIST **array;
  int studentCount;
  int length;
};

//O(n)
//Create array of linked lists to hold all students
CLASS* createDataSet(int maxElts) {
  CLASS *lp = malloc(sizeof(CLASS));
  assert(lp != NULL);
  lp->studentCount = 0;
  lp->length = maxElts;
  lp->array = malloc(sizeof(LIST*)*13);
  //Create dummy node for each linked list in each array
  for(int i=0; i<13; i++) {
    lp->array[i] = malloc(sizeof(LIST));
    lp->array[i]->head = malloc(sizeof(STUDENT));
    assert(lp->array[i]->head != NULL);
    lp->array[i]->head->next = lp->array[i]->head;
    lp->array[i]->head->prev = lp->array[i]->head;
    lp->array[i]->ageCount = 0;
  }
  return lp;
}

//O(n)
//Delete list and free memory
void destroySet(CLASS* lp){
  assert(lp != NULL);
  //Delete each node, in each linked list, in each array
  for(int i=0; i<13; i++){
    if(lp->array[i]->ageCount > 0) {
      STUDENT* pDel;
      STUDENT* pPrev = lp->array[i]->head->prev;
      do {
        pDel = pPrev;
        pPrev = pDel->prev;
        free(pDel);
      }while(pDel != lp->array[i]->head);
    }
    free(lp->array[i]);
  }
  free(lp);
}

//O(1)
//return 1 if the age is found, 0 if not
int searchAge(CLASS* lp, int age) {
  assert(lp != NULL);
  //Index is 18:0, 19:1, ...
  int index = age - 18;
  printf("***Search for Age: %d***\n", age);
  if(lp->array[index]->ageCount > 0){
    return 1;
  }
  return 0;
}

//O(1)
//insert new student with id and age
void insert(CLASS* lp, int id, int age) {
  assert(lp != NULL && lp->studentCount < lp->length);
  STUDENT* pNew = malloc(sizeof(STUDENT));
  assert(pNew != NULL);
  int index = age - 18;
  pNew->id = id;
  pNew->age = age;
  //Insert new node into the linked list in the right array
  lp->array[index]->head->prev->next = pNew;
  pNew->next = lp->array[index]->head;
  pNew->prev = lp->array[index]->head->prev;
  lp->array[index]->head->prev = pNew;
  lp->array[index]->ageCount++;
  //Print result
  printf("ID: %d Age: %d\n", pNew->id, pNew->age);
  lp->studentCount++;
}

//O(n)
//delete student from list based on age
void delete(CLASS* lp, int age){
  assert(lp != NULL);
  if(searchAge(lp, age) == 1){
    int index = age - 18;
    puts("***Student found***");
    int trials = 0;
    //Find each student with age and delete
    STUDENT *printNode = lp->array[index]->head->next;
    while(trials != lp->array[index]->ageCount) {
      printf("***Deleted ID: %d Age: %d***\n", printNode->id, printNode->age);
      printNode = printNode->next;
      trials++;
    }
    STUDENT* pDel = lp->array[index]->head->next;
    while(pDel != lp->array[index]->head) {
      lp->array[index]->head->next = pDel->next;
      free(pDel);
      pDel = lp->array[index]->head->next;
      lp->studentCount--;
    }
    //Set up linked list for each age group (array)
    lp->array[index]->ageCount = 0;
    lp->array[index]->head->next = lp->array[index]->head;
    lp->array[index]->head->prev = lp->array[index]->head;
  }
}

//O(n)
//returns max age gap from lp
int maxAgeGap(CLASS* lp){
  assert(lp != NULL);
  int minIndex = 0;
  int maxIndex = 12;
  //"Squeeze" the age gap
  while(lp->array[minIndex]->ageCount == 0)
    minIndex++;
  while(lp->array[maxIndex]->ageCount == 0)
    maxIndex--;
  return (maxIndex - minIndex);
}
