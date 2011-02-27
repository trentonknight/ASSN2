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
void separateCHAINING(int *randARRAY,int tbSIZE,TABLE *head[]);
void hashDRIVER(int tbSIZE,int randARRAY[]);
int linearPROBE(int address,int *HASH,int probeTHIS,int load);
int doubleHASH(int key,int *HASH,int listSIZE,int search);
void tableONE_MATCH(int *randARRAY,int *HT,int tbSIZE,int loop);
void tableTWO_MATCH(int *randARRAY,TABLE *HT_TWO[]);

int main(){
  
  threeHashMethods();

  return 0;
}
int HASH(int key,int listSIZE){
  int address = 0;
  address = key % listSIZE;
  return address;
}
int doubleHASH(int key,int *HASH,int listSIZE,int search){  

  while(HASH[key] != search){
    key = (1 + key % (listSIZE - 2)) + 1;
  }   
  return key;
}
int linearPROBE(int address,int *HASH,int probeTHIS,int load){
  while(HASH[address] != probeTHIS){
    address = (address + 1);
    if(address > load){
      address = 0;
    }
  }
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
void hashDRIVER(int tbSIZE,int randARRAY[]){
  int *HT; 
  TABLE *head[tbSIZE];
  head[tbSIZE] = new TABLE();
  int loop = 0;
  

  for(int a = 0; a < 3; a++){

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
      if(loop == 0){
	HT = OA_LinearProbe(randARRAY,tbSIZE,HT);
	cout << "<< Linear Probing >>" << endl;
	tableONE_MATCH(randARRAY,HT,tbSIZE,loop);
        delete [] HT;
      }
      else if(loop == 1){      
	HT = OA_DoubleHash(randARRAY,tbSIZE,HT);
	cout << "<< Double Hashing >>" << endl;
	tableONE_MATCH(randARRAY,HT,tbSIZE,loop);
        delete [] HT;
      }
      else{
        separateCHAINING(randARRAY,tbSIZE,head);
        cout << "<< Separate Chaining >>" << endl;
        tableTWO_MATCH(randARRAY,head);
      }
    }
    loop++;
    cout << endl;
  }
}
void threeHashMethods(){
  int tbSIZE = 0;
  int percent = 0;
  int randARRAY[MAX_KEYS];
  for(int a = 0; a < MAX_KEYS + 1; a++){
    randARRAY[a] = 0; 
   
  }
  randNUMS(randARRAY);
  tbSIZE = hashTableSize();
  percent = (5000.00 / tbSIZE) * 100;
  cout << "5000 items loaded into a " << tbSIZE << " element hash table." << endl;
  cout << "Load Factor = " << percent << "%" << endl;
  cout << "Results from matching 2500 elements from Rand Array with Hash Tables:\n" << endl;
  hashDRIVER(tbSIZE,randARRAY); 
}
int* OA_LinearProbe(int *randARRAY,int tbSIZE,int hashTABLE[]){
  int key = 0,
    address = 0;
  randARRAY[MAX_KEYS + 1] = 0;
      
  while(randARRAY[key] != 0 && key < MAX_KEYS){
    address = HASH(randARRAY[key],MAX_KEYS);
    if(hashTABLE[address] != 0){
      address = linearPROBE(address,hashTABLE,0,tbSIZE);
    }
    hashTABLE[address] = randARRAY[key];
    key++;
  }
  return hashTABLE;
}
int* OA_DoubleHash(int *randARRAY,int tbSIZE,int hashTABLE[]){
  int key = 0,
    address = 0;
  randARRAY[MAX_KEYS + 1] = 0;
    
  while(randARRAY[key] != 0 && key < MAX_KEYS){
    address = HASH(randARRAY[key],MAX_KEYS);
    while(hashTABLE[address] != 0){
      address = doubleHASH(address,hashTABLE,tbSIZE,0);
    }
    hashTABLE[address] = randARRAY[key];
    key++;
  }
  return hashTABLE;
}
void separateCHAINING(int *randARRAY,int tbSIZE,TABLE *head[]){
  int key = 0,
    address = 0,
    collisions = 0,
    newONE = 0;
  randARRAY[MAX_KEYS + 1] = 0;
  TABLE *newADDRESS[tbSIZE];
  newADDRESS[tbSIZE] = new TABLE();
 
  for(int a = 0; a < tbSIZE; a++){
    newADDRESS[a] = NULL;
    head[a] = NULL;
  }
    
  while(randARRAY[key] != 0){
    address = HASH(randARRAY[key],MAX_KEYS);
    newADDRESS[address] = new TABLE;
    newADDRESS[address]->key = randARRAY[key];
    if(head[address] != 0){
      newADDRESS[address]->next = head[address]->next;
      head[address]->next = newADDRESS[address];
      collisions++;
    }
    else{
      newADDRESS[address]->next = head[address];
      head[address] = newADDRESS[address]; 
      newONE++;   
    }
    key++;  
  }
  cout << "total collisions: " << collisions << endl;
  cout << "new: " << newONE << endl;
  cout << "added: " << collisions + newONE << endl;
  cout << "key: " << key << endl;
}
void tableONE_MATCH(int *randARRAY,int *HT,int tbSIZE,int loop){
  int key = 0,
    address = 0;
  double
    requiredProbe = 0,
    avg = 0;

  randARRAY[MAX_KEYS + 1] = 0;
     
  while(randARRAY[key] != 0){
    address = key;
    if(HT[address] == randARRAY[key]){
    }
    else{
      address =  HASH(randARRAY[key],MAX_KEYS);
      if(HT[address] == randARRAY[key]){
      }
      while(HT[address] != randARRAY[key]){
        if(loop == 0){
	  address = linearPROBE(address,HT,randARRAY[key],tbSIZE);
	}
        else if(loop == 1){
	  address = doubleHASH(address,HT,tbSIZE,randARRAY[key]);
	}
	requiredProbe++;
      }
    }    
    key = key + 2; 
  }
  
  avg = 2500 / requiredProbe;
  cout << requiredProbe << " elements required probing to find match in Hash Table." << endl;
  cout << "(avg = " << avg << " collisions per element.)" << endl;
}
void tableTWO_MATCH(int *randARRAY,TABLE *HT_TWO[]){
  int key = 0,
    address = 0,
    match = 0,
    collision = 0;
 randARRAY[MAX_KEYS + 1] = 0;

  while(randARRAY[key] != 0){
    address = HASH(randARRAY[key],MAX_KEYS);
      while(HT_TWO[address]->next != NULL && HT_TWO[address]->key != randARRAY[key]){         
	HT_TWO[address] = HT_TWO[address]->next;
      }//end second while 
     if(HT_TWO[address]->key == randARRAY[key]){
      match++;      
    }//end if
  key = key + 2;
  }//end outer while
  cout << "match: " << match << endl;
  cout << "collsion: " << collision << endl;
  cout << "TOTAL: " << match + collision << endl;
  cout << "key: " << key << endl;
}
