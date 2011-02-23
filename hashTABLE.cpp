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
void threeHashMethods();
int* OA_LinearProbe(int *randARRAY,int tbSIZE,int hashTABLE[]);
int* OA_DoubleHash(int *randARRAY,int tbSIZE,int hashTABLE[]);
void openAddressing(int tbSIZE,int randARRAY[]);
int seperateCHAINING();
int linearPROBE(int address,int *HASH,int probeTHIS,int load,double& probe);
int doubleHASH(int key,int tbSIZE);
void listSEARCH(int *randARRAY,int *HT,int tbSIZE);

int main(){
  
  ///driver function for all three
  ///collision resolution techniques
  threeHashMethods();

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
  int percent = 0;
 
  cout << "Enter desired hash table size." << endl;
  cout << "NOTE: hash table size must exceed 6500: " << endl;
  cin >> userCHOOSE;

  while(userCHOOSE < 6500){
    percent = (5000.00 / userCHOOSE) * 100;

    cout << "Whoops! A Hash Table with an index size of " << userCHOOSE << " is too small" << endl; 
    cout << "for 5000 entries. The maximum Load Factor is 75%." << endl;
    cout << "LOAD FACTOR for " << userCHOOSE << " is: " << percent << "%" << endl;
    cout << "Enter a Hash Table size larger than 6500: " << endl;
    cin >> userCHOOSE;
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
  randARRAY[MAX_KEYS + 1] = 0;
  return *randARRAY;
}
void openAddressing(int tbSIZE,int randARRAY[]){
  int *HT;

  HT = new(nothrow) int[tbSIZE];
  if(!HT){
    cout << "ERROR: Allocation failure.\n" << endl;
    cout << "WHOOPS! Most likely your Hash Table ";
    cout << "was too large." << endl;
  } 
  else{
    for(int a = 0; a < tbSIZE; a++){
      HT[a] = 0;
    }
    ///this menu will allow user to select collision method
    HT = OA_LinearProbe(randARRAY,tbSIZE,HT);
    listSEARCH(randARRAY,HT,tbSIZE);
  }
  delete [] HT;
}
void threeHashMethods(){
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
  openAddressing(tbSIZE,randARRAY); 
}
int* OA_LinearProbe(int *randARRAY,int tbSIZE,int hashTABLE[]){
  int key = 0,
    address = 0;
   double  prb = 0;
  int percent = (5000.00 / tbSIZE) * 100;
  randARRAY[MAX_KEYS + 1] = 0;
 
     
  while(randARRAY[key] != 0 && key < MAX_KEYS){
    ///get a purposed address
    ///and move through indexes
    ///in array of random int till
    ///empty index is found
    if(randARRAY[key] > tbSIZE){
      address = HASH(randARRAY[key],MAX_KEYS);
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
  cout << "Load Factor = " << percent << "%" << endl;
  cout << "Results from matching 2500 elements in Rand Array with Hash Tables:\n" << endl;

  return hashTABLE;
}
int* OA_DoubleHash(int *randARRAY,int tbSIZE,int hashTABLE[]){
  int key = 0,
    address = 0;
   double  prb = 0;
  int percent = (5000.00 / tbSIZE) * 100;
  randARRAY[MAX_KEYS + 1] = 0;
 
     
  while(randARRAY[key] != 0 && key < MAX_KEYS){
    ///get a purposed address
    ///and move through indexes
    ///in array of random int till
    ///empty index is found
    if(randARRAY[key] > tbSIZE){
      address = HASH(randARRAY[key],MAX_KEYS);
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
  cout << "Load Factor = " << percent << "%" << endl;
  cout << "Results from matching 2500 elements in Rand Array with Hash Tables:\n" << endl;

  return hashTABLE;
}
int linearPROBE(int address,int *HASH,int probeTHIS,int load,double& probe){
  while(HASH[address] != probeTHIS){
    address = (address + 1);
    probe++;
    if(address > load){
      address = 0;
    }
  }
  return address;
}
void listSEARCH(int *randARRAY,int *HT,int tbSIZE){
  int key = 0,
    address = 0,
    collision = 0;
 double
    probe = 0,
    requiredProbe = 0,
    noProbe = 0,
    verify = 0,
    avg = 0,
    search  = 0;

  randARRAY[MAX_KEYS + 1] = 0;
     
  while(randARRAY[key] != 0 && key <= MAX_KEYS){
    address = key;
    if(HT[address] == randARRAY[key]){
      verify++;
      noProbe++;
    }
    else{
      address =  HASH(randARRAY[key],MAX_KEYS);
      if(HT[address] == randARRAY[key]){
	noProbe++;
      }
      while(HT[address] != randARRAY[key]){
	address = linearPROBE(address,HT,randARRAY[key],tbSIZE,probe);
	requiredProbe++;
        collision = probe;
      }
      if(HT[address] == randARRAY[key]){
	verify++;
      }
    }    
    key = key + 2;
    search++;
  }
  
  avg = 2500 / requiredProbe;

  cout << "<< Linear Probing >>" << endl;
  cout << noProbe << " Matching elements found immediately without probing Hash Table." << endl;
  cout << collision << " Total collisions while probing for match." << endl;
  cout << verify << " Total elements matched between Rand Array and Hash Table." << endl;
  cout << requiredProbe << " elements required probing to find match in Hash Table." << endl;
  cout << "(avg = " << avg << " collisions per element.)" << endl;
  if(verify != 2500){
    cout << "Warning: " << probe << " matches found out of 2500." << endl; 
  }
}
