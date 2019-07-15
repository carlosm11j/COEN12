#include "set.h"

int main() {
  CLASS* application1;
  srand(time(NULL));
  application1 = createDataSet(3000);
  int prevID = 0;
  //Creates 1000 students
  for(int i=0; i<1000; i++) {
    //1-2
    int randomID = (rand()%2)+1;
    //18-30
    int randomAge = (rand()%13)+18;
    prevID += randomID;
    insert(application1, prevID, randomAge);
  }
  int age = (rand()%13) + 18;
  delete(application1, age);
  printf("Max Age Gap: %d\n", maxAgeGap(application1));
  destroyDataSet(application1);
}
