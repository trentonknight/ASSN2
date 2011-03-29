////////////////////////////////////////////////////////////////////////////////
///CODE FILENAME: Programming Assignment #2
///DESCRIPTION:   Two hashtables. First HashTable is created using Open 
///               Adressing twice the first time using a single hash the 
///               second using a double hash. Second HashTable is created
///               using Separate Chaining.
///  DATE:    	  24 MARCH, 2011
///  DESIGNER:	  Jason N Mansfield & Jeremy Bradshaw
///  FUNCTIONS:   headerMain ()
///               randNUMS()
///               hashTableSize()
///               HASH()
///               threeHashMethods()
///               OA_LinearProbe()
///               OA_DoubleHash()
///               separateCHAINING()
///               hashDRIVER()
///               linearPROBE()
///               doubleHASH()
///               tableONE_MATCH()
///               tableTWO_MATCH()
////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cmath>
#include <cstddef>
using namespace std;

// Constants:
const int    MAX_INT_SIZE            = 30000,
             MIN_INT_SIZE            = 1,
             NUM_PROBING_LOOPS       = 3,
             MIN_HASH_TABLE_SIZE     = 6500,
             MAX_KEYS                = 5000,
             NUM_ITEMS_TO_SEARCH     = 2500;
const double NUM_ITEMS_TO_SEARCH_DBL = 2500.00,
             MAX_KEYS_DBL            = 5000.00;

          
struct TABLE{
  TABLE () {key = 0;}     
  int key;
  TABLE* next;
};          

void HeaderMain      ();    
int  RandNums        (int *rand);
int  HashTableSize   ();
int  hash            (int key,int listSize);
void ThreeHashMethods();
int* OA_LinearProbe  (int *randArray,int tbSize,int hashTable[]); 
void OA_DoubleHash   (int *randArray,int tbSize,int hashTable[], 
                      bool& infiniteLoop);
void SeparateChaining(int *randArray,int tbSize,TABLE chainingArray[]);
int HashDriver      (int tbSize,int randArray[], double loadFactor);
void LinearProbe     (int& address,int hashTable[],int probeThis,int length, 
                      int& colCount);
int  DoubleHash      (int key, int listSize);
int  TableOneMatch   (int *randArray,int *ht,int tbSize, int loop, 
                      int colCount);
int  TableTwoMatch   (int *randArray,TABLE chainingArray[], int colCount,
                      int tbSize);
void DisplayResults  (int colCount, double loadFactor, int loop);

////////////////////////////////////////////////////////////////////////////////
///  FUNCTION:	     main()
///  DESCRIPTION:    simple main function
///  OUTPUT:   
///  	Return Val:  returns 0 if success
///  CALLS TO:       ThreeHashMethods()
///  IMPLEMENTED BY:
////////////////////////////////////////////////////////////////////////////////
int main ()
{   
  HeaderMain ();
  ThreeHashMethods();
    
  system ("PAUSE") ;
  return 0;
}

////////////////////////////////////////////////////////////////////////////////
///  FUNCTION:	     HeaderMain()
///  DESCRIPTION:    Displays a header to name and author the program 
///                  for the user to see.
///  IMPLEMENTED BY: Jeremy Bradshaw
////////////////////////////////////////////////////////////////////////////////
void HeaderMain ()  
{
  cout << "    Programming Assignment #2" << endl;
  cout << setfill(' ') << setw(16) << right << "by" << endl;
  cout << setw(27) << "Jason Mansfield & Jeremy Bradshaw" << endl << endl;
    
  return;
}

////////////////////////////////////////////////////////////////////////////////
///  FUNCTION:	     Hash()
///  DESCRIPTION:    Basic modulus hashing algorithm.
///  INPUT:
///  	Parameters:  key:      The number slot for hashing 
///                  listSize: The user selected list size
///  OUTPUT:   
///  	Return Val:  address:  Hashed address
///  IMPLEMENTED BY: Jason Mansfield
////////////////////////////////////////////////////////////////////////////////
int Hash (int key, int listSize)
{
  int address = 0;
  
  address = key % listSize;
  
  return address;
}
////////////////////////////////////////////////////////////////////////////////
///  FUNCTION:	     DoubleHash()
///  DESCRIPTION:    Performs another modulus hashing algorithm.
///  INPUT:
///  	Parameters:  key:      The number slot for hashing 
///                  listSize: The user selected list size
///                  search:   The value to search for
///  OUTPUT:   
///  	Return Val:  key:      Returns address found with matching search 
///  IMPLEMENTED BY: Jeremy Bradshaw
////////////////////////////////////////////////////////////////////////////////
int DoubleHash (int key, int listSize)
{   
  key = (key % (listSize - 2)) + 1;
  
  return key;
} 

////////////////////////////////////////////////////////////////////////////////
///  FUNCTION:	     RandNums()
///  DESCRIPTION:    Creates array of MAX_KEYS amount of random numbers
///  INPUT:
///  	Parameters:  *randArray:  Empty array 
///  OUTPUT:   
///  	Return Val:  *randArray: with MAX_KEYS amount of random ints.
///  IMPLEMENTED BY: Jason Mansfield
////////////////////////////////////////////////////////////////////////////////
int RandNums(int *randArray)
{
  int  count   = 0,
       randNum = 0;
  bool randNumDuplicate;
   
  srand(time(0));
  
  while (count < MAX_KEYS) {
    randNum = rand() % MAX_INT_SIZE;
    randNumDuplicate = false;
    
    for (int index = 0; (index < count) && !randNumDuplicate; index++){
      if (randArray[index] == randNum) 
        randNumDuplicate = true;       
    }
       
    if (!randNumDuplicate) {
      randArray[count] = randNum;
      ++count;
    } 
  }                              
  return *randArray;
}
      
////////////////////////////////////////////////////////////////////////////////
///  FUNCTION:	    HashTableSize()
///  DESCRIPTION:   Requests users desired size Hash Table and returns int
///  OUTPUT:   
///  	Return Val: userChoose: Int value of user requested hash table size.
/// IMPLEMENTED BY: Jason Mansfield
////////////////////////////////////////////////////////////////////////////////
int HashTableSize()
{
  int userChoose = 0;
 
  cout << "Enter desired hash table size."               << endl;
  cout << "NOTE: Hash table size must be "
       << MIN_HASH_TABLE_SIZE << " or greater: ";
  cin  >> userChoose;
  cout << endl;

  while(userChoose < MIN_HASH_TABLE_SIZE){

    cout << "Whoops! A Hash Table with an index size of " 
         << userChoose << " is too small"                << endl; 
    cout << "for "     << MAX_KEYS 
         << " entries. The maximum Load Factor is 75%. " << endl;
    cout << "Enter a Hash Table size "
         << MIN_HASH_TABLE_SIZE << " or greater: ";
    cin  >> userChoose;
    cout << endl;
  }
  return userChoose;
}

////////////////////////////////////////////////////////////////////////////////
///  FUNCTION:       ThreeHashMethods()
///  DESCRIPTION:    Calls functions to load randArray numbers, prompt user
///                  hash table size, and calls HashDriver. Displays data 
///                  regarding the load factor, MAX_KEYS and tbSize
///  CALLS TO:       RandNums()
///                  HashTableSize()
///                  HashDriver().
///  IMPLEMENTED BY: Jason Mansfield
////////////////////////////////////////////////////////////////////////////////
void ThreeHashMethods()
{
  int    tbSize     = 0,
         randArray[MAX_KEYS];
  double loadFactor = 0.00;
  
  for(int index = 0; index <= MAX_KEYS; index++){
    randArray[index] = 0; 
  }
   
  RandNums(randArray);
  
  tbSize     = HashTableSize();  
  loadFactor = MAX_KEYS_DBL / tbSize;

  cout << fixed            << setprecision(2);
  cout << MAX_KEYS         << " items loaded into a " 
       << tbSize           << " element hash table."          << endl;
  cout << "Load Factor = " << loadFactor              << endl << endl;
  cout << "Results of searching for " 
       << NUM_ITEMS_TO_SEARCH << " items:"            << endl << endl;
       
  HashDriver(tbSize,randArray, loadFactor);
  
  return; 
}

////////////////////////////////////////////////////////////////////////////////
///  FUNCTION:       HashDriver
///  DESCRIPTION:    Driver function that calls to the functions used to 
///                  create the hash table, the collision search functions, 
///                  and the function that displays the results. Function 
///                  loops 3 times once for each type.
///  INPUT:
///  	Parameters:  tbSize:      Size requested for hash table.
///                  randArray:   The random array of MAX_KEYS size ints used 
///                               for data in all hash tables created.
///                  loadFactor:  The load factor
///  CALLS TO:       OA_LinearProbe()
///                  TableOneMatch()
///                  DisplayResults()
///                  OA_DoubleHash()
///                  SeparateChaining()
///                  TableTwoMatch()
///  IMPLEMENTED BY: Jason Mansfield
////////////////////////////////////////////////////////////////////////////////
int HashDriver(int tbSize, int randArray[], double loadFactor)
{
  int    *ht = NULL,                  //hash table
         colCount;                    //collision count
  TABLE *chainingArray;
  try{
    chainingArray = new TABLE[tbSize];
  }catch (bad_alloc xa){
    cout << "Allocation Failure\n";
    return 1;
  }
  bool   infiniteLoop;   

  for(int loop = 0; loop < NUM_PROBING_LOOPS; loop++){

    colCount = 0;
    
    ht = new (nothrow) int[tbSize];
    
    if(!ht){
      cout << "ERROR: Allocation failure.\n"   << endl;
      cout << "WHOOPS! Most likely your Hash "
           << "Table was too large."           << endl;
    } 
    else{
      for(int index = 0; index < tbSize; index++){
    	ht[index] = 0;
      }
      
      if(loop == 0){
	    ht       = OA_LinearProbe(randArray, tbSize, ht);	    
	    colCount = TableOneMatch(randArray, ht, tbSize, loop, colCount);
	    DisplayResults(colCount, loadFactor, loop);
        delete [] ht;
        ht = NULL;
      }
      else if(loop == 1){      
	    OA_DoubleHash(randArray, tbSize, ht, infiniteLoop);
	    if (infiniteLoop){
          cout << "Hashing Error. No data displayed for Double Hashing." 
               << endl;
        }                  
	    else {          
	      colCount = TableOneMatch(randArray, ht, tbSize, loop, colCount);	      
	      DisplayResults (colCount, loadFactor, loop);
          delete [] ht;
          ht = NULL;
        }
      }
      else{
        SeparateChaining(randArray, tbSize, chainingArray);        
        colCount = TableTwoMatch(randArray, chainingArray, colCount, tbSize );
        DisplayResults (colCount, loadFactor, loop);
      }
      
    }
    cout << endl;
  }
  return 0;
}
       
////////////////////////////////////////////////////////////////////////////////
///  FUNCTION:	     OA_LinearProbe
///  DESCRIPTION:    Open Addressing with use of Linear Probe
///  INPUT:
///  	Parameters:  *randArray: Array of random int
///                  tbSize:     Requested hash table size
///                  hashTable:  Empty array for hash table
///  OUTPUT:   
///  	Return Val:  hashTable: Hash table with hashed data from 
///                             random array.
///  CALLS TO:       LinearProbe()
///                  Hash()
///  IMPLEMENTED BY: Jason Mansfield
////////////////////////////////////////////////////////////////////////////////
int* OA_LinearProbe(int *randArray, int tbSize, int *hashTable)
{
  int key      = 0,
      address  = 0,
      nulCount = 0; 
      
  while(key < MAX_KEYS){
    address = Hash(randArray[key],tbSize);
    if(hashTable[address] != 0){
      LinearProbe(address, hashTable, 0, tbSize, nulCount);
    }
    
    hashTable[address] = randArray[key];
    ++key;
  }
  return hashTable;
}

////////////////////////////////////////////////////////////////////////////////
///  FUNCTION:       LinearProbe
///  DESCRIPTION:    Incrementally checks each and every index for available
///                  empty memory in array. Keeps counter of number of 
///                  attempts before valid enry is found. 
///  INPUT:
///  	Parameters:  address:    Current address
///  	             *hashTable: Array being used
///                  probeThis:  Int being searched for 
///                              0 if looking for empty index
///                  htSize:     Hash Table size
///                  colCount:   The count of how many searches were performed.   
///  OUTPUT:   
///  	Parameters:  address:    Address of valid location
///                  colCount:   The count of how many searches were performed.
///  IMPLEMENTED BY: Jason Mansfield
////////////////////////////////////////////////////////////////////////////////
void LinearProbe(int& address,int hashTable[],int probeThis,int tbSize, 
                 int& colCount)
{
    
  while(hashTable[address] != probeThis){
    ++colCount;
    ++address;
    
    if(address >= tbSize)
      address = 0;
      
  }
  return;
}

////////////////////////////////////////////////////////////////////////////////
///  FUNCTION:       DisplayResults
///  DESCRIPTION:    Calculates Knuth results per collision type. Displays
///                  actual results vs Knuth predicted results
///  INPUT:
///  	Parameters:  colCount:    The count of how many searches were performed.
///  	             loadFactor:  The calculated load factor 
///                  loop:        The loop number to set the display per 
///                               collision type.       
///  IMPLEMENTED BY: Jeremy Bradshaw
////////////////////////////////////////////////////////////////////////////////
void DisplayResults (int colCount, double loadFactor, int loop)
{
  double avg          = 0,
         knuthResults = 0;
  
  
  if (loop == 0) {
    knuthResults = 0.5 * (1 + ( 1 / (1 - loadFactor) ) );
    cout << "<< Linear Probing >>" << endl;
  }
  else if (loop == 1) { 
    knuthResults = (-log(1 - loadFactor)) / loadFactor;
    cout << "<< Double Hashing >>" << endl;
  }
  else {
    knuthResults = 1 + (loadFactor / 2);
    cout << "<< Separate Chaining >>" << endl;
  }                 
  
  avg = colCount / NUM_ITEMS_TO_SEARCH_DBL;
  
  cout << fixed << setprecision(2) << right << setfill(' ') << setw(7);
  cout << colCount << " items examined (avg = " 
       << avg      << " items examined per search)"         << endl;
  cout << "     vs Knuth predicted avg = " << knuthResults
       << " items examined per search"                      << endl << endl;
  
  return;
}
  
////////////////////////////////////////////////////////////////////////////////
///  FUNCTION:	     OA_DoubleHash
///  DESCRIPTION:    Open Addressing with use of DoubleHash
///  INPUT:
///  	Parameters:  *randArray:   array of random int
///                  tbSize:       requested hash table size
///                  hasTable:     empty array for hash table
///  OUTPUT:   
///  	Parameters:  hashTable:    hash table with hashed data from 
///                                random array.
///                  infiniteLoop: Bool test for an infinite loop error
///  CALLS TO:       DoubleHash()
///                  Hash()
///  IMPLEMENTED BY: Jeremy Bradshaw
////////////////////////////////////////////////////////////////////////////////
void OA_DoubleHash(int *randArray,int tbSize,int hashTable[], 
                   bool& infiniteLoop){
  int key       = 0,
      address   = 0,
      errorCount,
      debugCount = 0;
  
  infiniteLoop = false; 
    
  while((key < MAX_KEYS) && !infiniteLoop){
    address    = Hash(randArray[key], tbSize);
    ++debugCount;
    errorCount = 0;
    while((hashTable[address] != 0) && !infiniteLoop){
      address += DoubleHash(address, tbSize);
      ++errorCount;
      if (address > tbSize)
        address = address % tbSize;
      if (errorCount > (2 * tbSize))
        infiniteLoop = true;
                        
    }
    
    hashTable[address] = randArray[key];
    ++key;
  }
  return;
}

////////////////////////////////////////////////////////////////////////////////
///  FUNCTION:	     SeparateChaining
///  DESCRIPTION:    Uses seperate chaining to create single linked lists
///                  of data. Linked list is used for collisions.
///  INPUT:
///  	Parameters:  *randArray:     Array of random int
///                  tbSize:         Requested hash table size
///                  *chainingArray: Empty array of struct TABLE
///                                  for linked list.
///  OUTPUT:   
///  	Parameters:  *chainingArray : becomes an array of linked list data 
///                                   containing random array int.
///  CALLS TO:       Hash()
///  IMPLEMENTED BY: Jeremy Bradshaw
////////////////////////////////////////////////////////////////////////////////
void SeparateChaining(int *randArray,int tbSize, TABLE chainingArray[]){
  int    key       = 0,
         address   = 0; 
  TABLE *newPtr    = NULL;
  bool   heapError = false;
  
  while ((key < MAX_KEYS) && !heapError) {
    address = Hash(randArray[key], tbSize);          
  
    if (chainingArray[address].key == 0) { 
      chainingArray[address].key = randArray[key];
      chainingArray[address].next = NULL;
      ++key;
    }
       
    else if (chainingArray[address].key != 0) {
      newPtr = new (nothrow) TABLE;   
      
      if (newPtr == NULL) {
        cout << "Heap error - could not allocate memory." << endl;
        heapError = true;
      }
      else {
        newPtr->key = chainingArray[address].key;
        newPtr->next = chainingArray[address].next;
        chainingArray[address].key = randArray[key];
        chainingArray[address].next = newPtr;
        ++key;
      }
    }
  }       

  return;
}

////////////////////////////////////////////////////////////////////////////////
///  FUNCTION:        TableOneMatch
///  DESCRIPTION:     Matches original random array data against newly created
///                   *ht hash table.
///  INPUT:
///  	Parameters:   randArray: Original random array of int used to load 
///                              hash table
///                   *ht:       Freshly created hash table containing 
///                              random array 
///                   tbSize:    Hash table size
///                   loop:      Assists HashDriver function with reuse of 
///                              TableOneMatch
///                              -0 allows call to LinearProbe on first call
///                              -1 allows call to DoubleHash on second call
///  OUTPUT:
///     Return Value: colCount:  The count of how many searches were performed. 
///  CALLS TO:        LinearProbe()
///                   DoubleHash()
///                   Hash()
///  IMPLEMENTED BY: Jason Mansfield
////////////////////////////////////////////////////////////////////////////////
int TableOneMatch(int *randArray, int *ht, int tbSize, int loop, 
                  int colCount)
{
  int key = 0,
      address = 0;
    
  colCount = 0;     //resetting count for each collision method
     
  while(key < MAX_KEYS){
    
    address = Hash(randArray[key],tbSize);
    
    if (ht[address] == randArray[key])
    ++colCount;
    
    else {
      while(ht[address] != randArray[key]){
        ++colCount;   //one count for not finding it at original element                
        if(loop == 0) {
	      LinearProbe(address, ht, randArray[key], tbSize, colCount);
	      ++colCount; 
        }
	      
      
        else if(loop == 1){
          while (ht[address] != randArray[key]) {
            ++colCount;  
	        address += DoubleHash(address, tbSize);
	        if (address > tbSize) {          
              address = address % tbSize;
            }
          }
        }
      }
    }    
    key += 2; 
  }
  return colCount;
}

////////////////////////////////////////////////////////////////////////////////
///  FUNCTION:	     TableTwoMatch
///  DESCRIPTION:    Traverses and matches original random array with freshly 
///                  created inked list of random data.
///  INPUT:
///  	Parameters:  *randArray:     Original random array used to make hashed 
///                                  linked list
///                  *chainingArray: Linked list containing hashed data
///  OUTPUT:
///     ReturnValue: colCount:  The count of how many searches were performed.
///                             
///  CALLS TO:       HASH()
///  IMPLEMENTED BY: Jeremy Bradshaw              
////////////////////////////////////////////////////////////////////////////////
int TableTwoMatch(int *randArray, TABLE chainingArray[], int colCount, 
                  int tbSize){
  int key     = 0,
      address = 0,
      missedCount = 0;
  bool linearError;
  TABLE *tempPtr = NULL; 

  colCount = 0;                 //reinitializing colCount

  while (key < MAX_KEYS){
    address =  Hash(randArray[key],tbSize);
    linearError = false;

    if (chainingArray[address].key == randArray[key]) {
      ++colCount;   //for the item being found at the first location                  
    }
    
    else {
      tempPtr  = chainingArray[address].next;
              
      while((tempPtr->key  != randArray[key]) && !linearError){
        ++colCount; //for each time the item is not found                                         
	    tempPtr = tempPtr->next;
        ++missedCount;          	       
      }             //end second while 
      
      ++colCount;   //for the item being found           
    }               //end of else statement
    
    key += 2; 
         
  }                 //end outer while

  return colCount;
}


  
  
  