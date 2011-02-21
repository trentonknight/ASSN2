#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

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
int linearPROBE(int address,int *HASH,int probeTHIS,int load,int& probe);
int doubleHASH(int key,int tbSIZE);
void listSEARCH(int *randARRAY,int *HT,int tbSIZE);

int main(){
  int tbSIZE = 0;
  int randARRAY[MAX_KEYS];
  for(int a = 0; a < MAX_KEYS + 1; a++){
    randARRAY[a] = 0; 
   
  }
  
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
  listSEARCH(randARRAY,HT,tbSIZE);
}
int* openAddressing(int *randARRAY,int tbSIZE){
  int key = 0,
    address = 0,
    prb = 0,
    *hashTABLE;
  int percent = (5000.00 / tbSIZE) * 100;
  int load = (5000.00 / tbSIZE) * 10;
  int loadFACTOR = (tbSIZE * load)/10;
  randARRAY[MAX_KEYS + 1] = 0;
  hashTABLE = new(nothrow) int[tbSIZE];
  for(int a = 0; a < tbSIZE + 1; a++){
    hashTABLE[a] = 0;
  }
     
  while(randARRAY[key] != 0 && key < MAX_KEYS){
    ///get a purposed address
    ///and move through indexes
    ///in array of random int till
    ///empty index is found
    if(randARRAY[key] > tbSIZE){
    address = HASH(randARRAY[key],loadFACTOR);
    }
    ///if address is available 
    ///grab the key
    if(hashTABLE[address] == 0){
      hashTABLE[address] = randARRAY[key];
    }
    ///if a collision is the result run
    ///a linear probe until available address is found 
    else{
      address = linearPROBE(address,hashTABLE,0,tbSIZE,prb);
      hashTABLE[address] = randARRAY[key];
    }
    if(hashTABLE[address] == randARRAY[key]){
    key++;
    }
  }
  cout << key << " items loaded into a " << tbSIZE << " element hash table." << endl;
  cout << "Load Factor = " << percent << endl;
  cout << "Results from searching for 2500 items." << endl;

  return hashTABLE;
}
int linearPROBE(int address,int *HASH,int probeTHIS,int load,int& probe){
  while(HASH[address] != probeTHIS){
    address = (address + 1);
    probe++;
    if(address >= load){
      address = 0;
    }
  }
  return address;
}
void listSEARCH(int *randARRAY,int *HT,int tbSIZE){
  int key = 0,
    address = 0,
    probe = 0,
    found = 0,
    attempts = 0;
  randARRAY[MAX_KEYS + 1] = 0;
     
  while(randARRAY[key] != 0 && key < MAX_KEYS){
    address =  HASH(randARRAY[key],tbSIZE);
    while(HT[address] != randARRAY[key] && attempts < tbSIZE){
      address = linearPROBE(address,HT,randARRAY[key],tbSIZE,probe);
      found++;
      attempts++;
    }
    key = key + 2;
    attempts = 0;
  }
  found = probe / found;

  cout << "Linear Probing." << endl;
  cout << probe  << " items examined ";
  cout << "(avg = " << found << " items examined per search.)" << endl;
}

