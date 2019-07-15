#include "set.h"

int main() {
  CLASS* application2;
  srand(time(NULL));
  application2 = createDataSet(3000);
  int prevID = 0;
  //Creates 1000 students
  for(int i=0; i<1000; i++) {
    //1-2
    int randomID = (rand()%2)+1;
    //18-30
    int randomAge = (rand()%13)+18;
    prevID += randomID;
    insert(application2, prevID, randomAge);
  }
  int age = (rand()%13) + 18;
  delete(application2, age);
  destroyDataSet(application2);
}
