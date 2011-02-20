#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

using namespace std;

struct TABLE{
  int key;
  TABLE* next;
};
const int MAX_KEYS = 5000;
const int RANDOM = 30000;

int randNUMS(int *rand);
int hashTableSize();
int HASH(int key,int listSIZE);
void threeHashMethods(int *randARRAY,int tbSIZE);
int* openAddressing(int *randARRAY,int tbSIZE);
int seperateCHAINING();
int quadraticPROBE(int address,int *HASH,int probeTHIS,int loadFACTOR);
int doubleHASH(int key,int tbSIZE);
void searchELEMENTS(int *randARRAY,int *HT,int tbSIZE);

int main(){
  int tbSIZE = 0;
  int randARRAY[MAX_KEYS] = {0};
  
  ///create random array of 5,000 unique int
  ///they will be of values between 1-30000
  randNUMS(randARRAY);
  ///get hash table size from user
  ///table must be larger than 6500 int
  tbSIZE = hashTableSize();
  ///driver function for all three
  ///collision resolution techniques
  threeHashMethods(randARRAY,tbSIZE);

  return 0;
}
int HASH(int key,int listSIZE){
  int address = 0;
  address = key % listSIZE;
  return address;
}
int doubleHASH(int key,int tbSIZE){
  int address = 0;
  address = (key % (tbSIZE - 2)) + 1;
  return address;
}
int hashTableSize(){
  int userCHOOSE = 0;
 
  cout << "Enter desired hash table size." << endl;
  cout << "NOTE: hash table size must exceed 6500: " << endl;
  cin >> userCHOOSE;
  if(userCHOOSE < 6500){
    cout << "Whoops " << userCHOOSE << " is to small!" << endl;
    hashTableSize();
  }
  return userCHOOSE;
}
int randNUMS(int *randARRAY){
  ///temporary fix for randARRAY array of numbers till hash is running
  int check = 0;
  int index = 0;
  int loop = 0;

  srand (time(NULL));
  for(index = 0; index < MAX_KEYS; index++){
   check = rand() % RANDOM + 1;
   while(randARRAY[loop] != 0){
   if(check == randARRAY[index]){
     check = rand() % RANDOM + 1;
     loop = 0;
   }
    loop++;
   }
   randARRAY[index] = check;
  }
  
  return *randARRAY;
}
void threeHashMethods(int *randARRAY,int tbSIZE){
  int *HT;

  ///this menu will allow user to select collision method
  HT = openAddressing(randARRAY,tbSIZE);
 
}
int* openAddressing(int *randARRAY,int tbSIZE){
  int key = 0,
      address = 0,
      hashTABLE[tbSIZE],
      *HT = hashTABLE;
  int loadFACTOR = 0.75 * tbSIZE;
 
  for(int a = 0; a < tbSIZE * tbSIZE; a++){
  hashTABLE[a] = 0;
  }

  while(randARRAY[key] != 0 && address < loadFACTOR){
    ///get a purposed address
    ///and move through indexes
    ///in array of random int till
    ///empty index is found
    address = HASH(randARRAY[key],MAX_KEYS);
    ///if address is available 
    ///grab the key
    if(hashTABLE[address] == 0){
       hashTABLE[address] = randARRAY[key];
    }
    ///if a collision is the result run
    ///a linear probe until available address is found 
    else{
      address = quadraticPROBE(address,hashTABLE,0,loadFACTOR);
      hashTABLE[address] = randARRAY[key];
      cout << address << endl;
      }
    key++;
    }
  return HT;
}
int quadraticPROBE(int address,int *HASH,int probeTHIS,int loadFACTOR){
  ///look for empty index but also make sure address does not
  ///exceed the table size.
 while(HASH[address] != probeTHIS && address < loadFACTOR){
   address = (address^2) + address;
   ///address = address + 1;
  }
  return address;
}
