#include <iostream>

using namespace std;

struct TABLE{
  int key;
  TABLE* next;
};
const int MAX_KEYS = 5000;

int randNUMS(int rand[MAX_KEYS]);
int hashTableSize();
void threeHashMethods(int rand[MAX_KEYS],int listSIZE);
int openAddressing_LP();
int openAddressing_DH();
int seperateCHAINING();
int averageHashTable();

int main(){
  int tableSIZE = 0;
  int rand[MAX_KEYS] = {0};

  randNUMS(rand);
  tableSIZE = hashTableSize();
  threeHashMethods(rand,tableSIZE);

  return 0;
}
int hashTableSize(){
  int userCHOOSE = 0;
  ///user must choose above 6500
  userCHOOSE = 7000; 
  return userCHOOSE;
}
int randNUMS(int rand[MAX_KEYS]){
  ///temporary fix till hash is running
  for(int a = 0; a < 10; a++){
    rand[a] = a;
  }
  return *rand;
}
void threeHashMethods(int rand[MAX_KEYS],int listSIZE){
  int address = 0;

  
}


