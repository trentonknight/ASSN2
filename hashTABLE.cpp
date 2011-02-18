#include <iostream>

using namespace std;

struct TABLE{
  int key;
  TABLE* next;
};
const int MAX_KEYS = 5000;

int randNUMS(int rand[]);
int hashTableSize();
int HASH(int key,int tbSIZE);
int doubleHASH(int key,int tbSIZE);
void threeHashMethods(int rand[MAX_KEYS],int tbSIZE);
int openAddressing_QP(int rand[MAX_KEYS],int tbSIZE);
int openAddressing_DH();
int seperateCHAINING();
int quadraticPROBE(int address,int rand[MAX_KEYS],int hashTABLE[]);
int averageHashTable();

int main(){
  int tbSIZE = 0;
  int rand[MAX_KEYS] = {0};
  
  ///create random array of 5,000 unique int
  ///they will be of values between 1-30000
  randNUMS(rand);
  ///get hash table size from user
  ///table must be larger than 6500 int
  tbSIZE = hashTableSize();
  ///driver function for all three
  ///collision resolution techniques
  threeHashMethods(rand,tbSIZE);

  return 0;
}
int HASH(int key,int tbSIZE){
  int address = 0;
  address = key % tbSIZE;
  return address;
}
int doubleHASH(int key,int tbSIZE){
  int address = 0;
  address = (key % (tbSIZE - 2)) + 1;
  return address;
}
int hashTableSize(){
  int userCHOOSE = 0;
  ///user must choose a hash table size above 6500
  userCHOOSE = 7000; 
  return userCHOOSE;
}
int randNUMS(int rand[]){
  ///temporary fix for rand array of numbers till hash is running
  for(int a = 0; a < 10; a++){
    rand[a] = a;
  }
  return *rand;
}
void threeHashMethods(int rand[],int tbSIZE){
  ///this menu will allow user to select collision method
  openAddressing_QP(rand,tbSIZE);
  
}
int openAddressing_QP(int rand[],int tbSIZE){
  int key = 0,
      address = 0,
      hashTABLE[tbSIZE];

  while(rand[key] != 0){
    ///get a purposed address
    ///and move through indexes
    ///in array of random int till
    ///empty index is found
    address = HASH(rand[key++],tbSIZE);
    ///if address is available 
    ///grab the key
    if(hashTABLE[address] == 0){
       hashTABLE[address] = rand[key];
    }
    ///if a collision is the result run
    ///a quadratic probe until available address is found 
    else{
      address= quadraticPROBE(address,rand,hashTABLE);
      hashTABLE[address] = rand[key];
    }
    }
  return *hashTABLE;
}
int quadraticPROBE(int address,int rand[],int hashTABLE[]){
  while(hashTABLE[address] != 0){
    address = (address^2) + address;
  }
  return address;
}
