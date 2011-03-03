/////////////////////////////////////////////////////////////////////////
///CODE FILENAME: hashTABLE
///DESCRIPTION: Two hashtables. First HashTable is created using Open 
///             Adressing twice the first time using a single hash the 
///             second using a double hash. Second HashTable is created
///             using Separate Chaining.
///  DATE:    	02MARCH11
///  DESIGNER:	Jason N Mansfield
///  FUNCTIONS: randNUMS(),hashTableSize(),HASH(),threeHashMethods(),
///             OA_LinearProbe(),OA_DoubleHash(),separateCHAINING(),
///             hashDRIVER(),linearPROBE(),doubleHASH(),tableONE_MATCH(),
///             tableTWO_MATCH().
////////////////////////////////////////////////////////////////////////
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
void threeHashMethods();
int* OA_LinearProbe(int *randARRAY,int tbSIZE,int hashTABLE[]); 
int* OA_DoubleHash(int *randARRAY,int tbSIZE,int hashTABLE[]);
void separateCHAINING(int *randARRAY,int tbSIZE,TABLE *head[]);
void hashDRIVER(int tbSIZE,int randARRAY[]);
int linearPROBE(int address,int *HASH,int probeTHIS,int length);
int doubleHASH(int key,int *HASH,int listSIZE,int search);
void tableONE_MATCH(int *randARRAY,int *HT,int tbSIZE,int loop);
void tableTWO_MATCH(int *randARRAY,TABLE *HT_TWO[]);
///////////////////////////////////////////////////////////////////////////
///  FUNCTION:	main()
///  DESCRIPTION: simple main funtion
///  OUTPUT:   
///  	Return Val: returns 0 if success
///  CALLS TO:  threeHashMethod()
//////////////////////////////////////////////////////////////////////////
int main(){
  
  threeHashMethods();

  return 0;
}
///////////////////////////////////////////////////////////////////////////
///  FUNCTION:	HASH()
///  DESCRIPTION:    basic modulus hashing algorithm
///  INPUT:
///  	Parameters: recieves hash key and listsize to create address
///  	            for hash table.
///  OUTPUT:   
///  	Return Val: returns int address
//////////////////////////////////////////////////////////////////////////
int HASH(int key,int listSIZE){
  int address = 0;
  address = key % listSIZE;
  return address;
}
///////////////////////////////////////////////////////////////////////////
///  FUNCTION:	doubleHASH
///  DESCRIPTION:      performs another modulus hashing algorithm
///  INPUT:
///  	Parameters: recieves previous address created from HASH()
///  	            with key, search represents int being searched
///                 for in *HASH array, listSIZE simply represents the
///                 list size.
///  OUTPUT:   
///  	Return Val: int key
///  	Parameters: returns address found with matching search 
///                 (0 if looking for an available index in array)
//////////////////////////////////////////////////////////////////////////
int doubleHASH(int key,int *HASH,int listSIZE,int search){  

  while(HASH[key] != search){
    key = (1 + key % (listSIZE - 2)) + 1;
  }   
  return key;
}
///////////////////////////////////////////////////////////////////////////
///  FUNCTION:  linearPROBE()
///  DESCRIPTION: incremently checkes each and every index for available
///               empty memory in array.
///  INPUT:
///  	Parameters: address: current address
///  	            *HASH: array being used
///                 probeTHIS: int being searched for (0 if looking for empty index)
///                 length: Hash Table size
///  OUTPUT:   
///  	Return Val: address that has found probeTHIS integer.
//////////////////////////////////////////////////////////////////////////
int linearPROBE(int address,int *HASH,int probeTHIS,int length){
  while(HASH[address] != probeTHIS){
    address = (address + 1);
    if(address > length){
      address = 0;
    }
  }
  return address;
}
///////////////////////////////////////////////////////////////////////////
///  FUNCTION:	hashTableSize()
///  DESCRIPTION:  requests users desired size Hash Table and returns int
///  OUTPUT:   
///  	Return Val: int value of users requested hash table size.
///  	Parameters: userCHOOSE
//////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////
///  FUNCTION:	randNUMS()
///  DESCRIPTION:     Creates array of random numbers
///  INPUT:
///  	Parameters: empty array *randARRAY
///  OUTPUT:   
///  	Return Val: Array with 5000 indexes with random int.
///     Parameters: *randARRAY 
//////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////
///  FUNCTION: hashDRIVER
///  DESCRIPTION:  driver function that calls to the functions used to create
///                the hash table then the function that reads and veriffies
///                the created hash tables.
///  INPUT:
///  	Parameters: *HT pointer to arrays.
///                 *head pointer to array of linked list.
///                  tbSIZE: size requested for hash table size.
///                  randARRAY: the random array of 5000 int used 
///                  for data in all hash tables created.
///  OUTPUT:   
///  	Return Val: Passes created *HT and *head to proper functions.
//////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////
///  FUNCTION:  threeHashMethod()
///  DESCRIPTION: assists in collecting data regarding hash table size and
///               indexes.
///  INPUT:
///  	Parameters: randARRAY: gets random array
///                 tbSIZE: size of hash table
///                 percent: formula calculates Load Factor 
///  OUTPUT:   
///  	Return Val: passes table size and random array to hashDRIVER
///  CALLS TO: randNUMS(),hashTableSize(), hashDRIVER().
//////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////
///  FUNCTION:	OA_LinearProbe()
///  DESCRIPTION:  Open Addressing with use of Linear Probe
///  INPUT:
///  	Parameters: *randARRAY: array of random int
///                 tbSIZE: requested hash table size
///                 hashTABLE[] empty array for hash table
///  OUTPUT:   
///  	Return Val: hashTABLE: hash table with hashed data from 
///                 random array.
///  CALLS TO:  linearPROBE()
//////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////
///  FUNCTION:	OA_DoubleHash()
///  DESCRIPTION:  Open Addressing with use of doubleHASH
///  INPUT:
///  	Parameters: *randARRAY: array of random int
///                 tbSIZE: requested hash table size
///                 hashTABLE[] empty array for hash table
///  OUTPUT:   
///  	Return Val: hashTABLE: hash table with hashed data from 
///                 random array.
///  CALLS TO: doubleHASH()
//////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////
///  FUNCTION:	separateCHAINING()
///  DESCRIPTION:   Uses seperate chaining to create single linked list
///                 of data. Linked list is used for collisions.
///  INPUT:
///  	Parameters: *randARRAY: array of random int
///                 tbSIZE: requested hash table size
///                 *head[] empty array of struct TABLE
///                 for linked list.
///  OUTPUT:   
///  	Return Val: *head becomes an array of linked list data containing
///                  random array int.
//////////////////////////////////////////////////////////////////////////
void separateCHAINING(int *randARRAY,int tbSIZE,TABLE *head[]){
  int key = 0,
    address = 0;

  randARRAY[MAX_KEYS + 1] = 0;
  TABLE *newADDRESS[tbSIZE];
  newADDRESS[tbSIZE] = new TABLE();
 
  for(int a = 0; a < tbSIZE; a++){
    newADDRESS[a] = NULL;
    head[a] = NULL;
  }
    
  while(randARRAY[key] != 0 && key < MAX_KEYS){
    address = HASH(randARRAY[key],MAX_KEYS);
    newADDRESS[address] = new TABLE;
    newADDRESS[address]->key = randARRAY[key];
    if(head[address] != 0){
      newADDRESS[address]->next = head[address]->next;
      head[address]->next = newADDRESS[address];
    }
    else{
      newADDRESS[address]->next = head[address];
      head[address] = newADDRESS[address];        
    }
    key++;  
  }
}
///////////////////////////////////////////////////////////////////////////
///  FUNCTION:  tableONE_MATCH()
///  DESCRIPTION:  Matches original random array data against newly created *HT hash
///                table.
///  INPUT:
///  	Parameters: randARRAY: original random array of int used to load hash table
///                 *HT: freshly created hash table containing random array 
///                 tbSIZE: hash table size
///                 loop: assists hashDRIVER function with reuse of tableONE_MATCH
///                 0 allows call to linearPROBE on first call
///                 1 allows call to doubleHASH on second call
///  CALLS TO:  linearPROBE(), doubleHASH(), HASH()
//////////////////////////////////////////////////////////////////////////
void tableONE_MATCH(int *randARRAY,int *HT,int tbSIZE,int loop){
  int key = 0,
    address = 0;
  double
    requiredProbe = 0,
    avg = 0;

  randARRAY[MAX_KEYS + 1] = 0;
     
  while(randARRAY[key] != 0){
    
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
    key = key + 2; 
  }
  
  avg = 2500 / requiredProbe;
  cout << requiredProbe << " elements required probing to find match in Hash Table." << endl;
  cout << "(avg = " << avg << " collisions per element.)" << endl;
}
///////////////////////////////////////////////////////////////////////////
///  FUNCTION:	tableTWO_MATCH()
///  DESCRIPTION:  Traverses and matches original random array with freshly created
///                linked list of random data.
///  INPUT:
///  	Parameters: *randARRAY: original random array used to make hashed linked list
///                 *HT_TWO: freshly created linked list containing hashed data
///  CALLS TO: HASH()               
//////////////////////////////////////////////////////////////////////////
void tableTWO_MATCH(int *randARRAY,TABLE *HT_TWO[]){
  int key = 0,
    address = 0;
  double requiredProbe = 0,
    avg = 0;

  randARRAY[MAX_KEYS + 1] = 0;

  while(randARRAY[key] != 0){
    address =  HASH(randARRAY[key],MAX_KEYS);
        while(HT_TWO[address]->next != NULL){         
	HT_TWO[address] = HT_TWO[address]->next;
	requiredProbe++;    
      }//end second while 
    key = key + 2;      
  }//end outer while
  avg = 2500 / requiredProbe;
  cout << requiredProbe << " elements required probing to find match in Hash Table." << endl;
  cout << "(avg = " << avg << " collisions per element.)" << endl;
}
