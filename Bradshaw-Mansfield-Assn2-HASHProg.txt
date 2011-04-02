////////////////////////////////////////////////////////////////////////////////
///CODE FILENAME: Programming Assignment #2 Hashing Program
///DESCRIPTION:   Program will create MAX_KEYS random integers from 1 to 
///               MAX_INT_SIZE and store them into a random ordered array. 
///               Program will prompt user for hash table size. Program will
///               run use modulo-division as an original hash method. Program
///               will use three different collision resolution methods. Space
///               will be dynamically allocated in an array to hold values for
///               linear probing and double hashing methods. An array of 
///               structures will be used to hold the hash info for separate
///               chaining. All MAX_KEYS will be hashed using each method
///               into the appropriate arrays. Then program will search for
///               every other element in the arrays. It will keep a count
///               for each method of how many attempts were needed to find 
///               the elements searched. It will display the number of elements
///               searched per collision resolution method and display that 
///               value alongside a Knuth average calculated per the type of
///               collision resolution.   
///  DATE:    	  30 MARCH, 2011
///  DESIGNER:	  Jason N Mansfield & Jeremy Bradshaw
///  FUNCTIONS:   HeaderMain()
///               RandNums()
///               HashTableSize()
///               Hash()
///               ThreeHashMethods()
///               OA_LinearProbe()
///               OA_DoubleHash()
///               SeparateChaining()
///               HashDriver()
///               LinearProbe()
///               DoubleHash()
///               TableOneMatch()
///               TableTwoMatch()
///               DisplayResults()
////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cmath>
#include <cstddef>

#ifdef _WIN32 
#include <windows.h>
#endif


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

void HeaderMain      (                                          );    
int  RandNums        (int*                                      );
int  HashTableSize   (                                          );
int  hash            (int  , int                                );
void ThreeHashMethods(                                          );
int* OA_LinearProbe  (int* , int      , int []                  ); 
void OA_DoubleHash   (int* , int      , int []   , bool&        );
void SeparateChaining(int* , int      , TABLE []                );
int  HashDriver      (int  , int []   , double                  );
void LinearProbe     (int& , int []   , int      , int   , int& );
int  DoubleHash      (int  , int      , int                     );
int  TableOneMatch   (int* , int*     , int      , int   , int  );
int  TableTwoMatch   (int* , TABLE [] , int      , int          );
void DisplayResults  (int  , double   , int                     );

////////////////////////////////////////////////////////////////////////////////
///  FUNCTION:	     main()
///  DESCRIPTION:    simple main function
///  OUTPUT:   
///  	Return Val:  returns 0 if success
///  CALLS TO:       ThreeHashMethods()
///  IMPLEMENTED BY: Jeremy and Jason
////////////////////////////////////////////////////////////////////////////////
int main ()
{   
  HeaderMain ();
  //get user info and create table followed by
  //display of hash table info
  ThreeHashMethods();
  //system pause for windows
  //you can remove if using on Unix or Linux
  #ifdef _WIN32 
  system ("PAUSE");
  #endif
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
  //introductive printout to user
  cout << "    Programming Assignment #2" << endl;
  cout << setfill(' ') << setw(16) << right << "by" << endl;
  cout << setw(27) << "Jason Mansfield & Jeremy Bradshaw" << endl << endl;
    
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
  //modulo-division method
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
  //open addressing via double hash method
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
    //use rand() to create random int
    randNum = rand() % MAX_INT_SIZE;
    randNumDuplicate = false;
    
    for (int index = 0; (index < count) && !randNumDuplicate; index++){
      //go back through current array and verify no int match current random int
      if (randArray[index] == randNum) 
	//if a int within current array is a match mark bool below true
        randNumDuplicate = true;       
    }
       
    if (!randNumDuplicate) {
      //if no duplicate was found enter new rand int into array and
      //increment count
      randArray[count] = randNum;
      ++count;
    } 
  }
  //return array full of random int                              
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
  //ensure the users selection is large enough
  //if not the below while loop will continue until a satisfactory
  //size is chosen by user
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
  //return int which is the users selected size for the two hash tables
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
  //make sure all indexes are NULL
  for(int index = 0; index <= MAX_KEYS; index++){
    randArray[index] = 0; 
  }
  //get a random array of int
  RandNums(randArray);
  //now enter HashTableSize() function which requests the size
  //the user wishes for Hash Table sizes
  tbSize     = HashTableSize();
  //calculate the load factor of requested Hash Table by it's size  
  loadFactor = MAX_KEYS_DBL / tbSize;

  cout << fixed            << setprecision(2);
  cout << MAX_KEYS         << " items loaded into a " 
       << tbSize           << " element hash table."          << endl;
  cout << "Load Factor = " << loadFactor              << endl << endl;
  cout << "Results of searching for " 
       << NUM_ITEMS_TO_SEARCH << " items:"            << endl << endl;
  //now enter driver function
  HashDriver(tbSize,randArray, loadFactor);
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
  int      *ht = NULL,                  //hash table
             colCount;                    //collision count
  bool   infiniteLoop;  
  //Calling memory from HEAP and creating a Structure Array.                         
  TABLE  *chainingArray = new (nothrow) TABLE[tbSize];   
  //verify memory is available on this computer.
  if(!chainingArray){
    cout << "Allocation Error!" << endl;
    return 1;
  }
       
  for(int loop = 0; loop < NUM_PROBING_LOOPS; loop++){
    
    colCount = 0;
    //fill hash table ht
    ht = new (nothrow) int[tbSize];
    //verify memory is available
    if(!ht){
      cout << "ERROR: Allocation failure.\n"   << endl;
      cout << "WHOOPS! Most likely your Hash "
           << "Table was too large."           << endl;
    } 
    else{
      for(int index = 0; index < tbSize; index++){
        //make sure all index are clean before running through
        //all hash tables one by one.
    	ht[index] = 0;
      }
      //variable loop signifies which method will be used each time
      //in this case loop == 0 so Linear Probing will be used
      if(loop == 0){
	//create the hash table
	ht       = OA_LinearProbe(randArray, tbSize, ht);
	//verify table matches random array after creation above	    
	colCount = TableOneMatch(randArray, ht, tbSize, loop, colCount);
	//lastly display findings
	DisplayResults(colCount, loadFactor, loop);
	//delete and return memory
        delete [] ht;
	//ht == 0
        ht = NULL;
      }
      //loop == 1 so this time a Double Hash will be used
      else if(loop == 1){
	//fill new hash table ht again      
	OA_DoubleHash(randArray, tbSize, ht, infiniteLoop);
	//safeguard make sure its not entering dangerous never ending loop
	if (infiniteLoop){
          cout << "Hashing Error. No data displayed for Double Hashing." 
               << endl;
        }                  
	else { 
	  //verify random array equals hash table ht after creation above         
	  colCount = TableOneMatch(randArray, ht, tbSize, loop, colCount);
	  //display findings	      
	  DisplayResults (colCount, loadFactor, loop);
	  //delete and release memory
          delete [] ht;
          //ht == 0
          ht = NULL;
        }
      }
      //finally on the last loop Separate Chaining will be used
      else{
        //fill hash table chainingArray with randArray
        SeparateChaining(randArray, tbSize, chainingArray);
        //verify filled chainingArray matches randArray        
        colCount = TableTwoMatch(randArray, chainingArray, colCount, tbSize );
        //display findings
        DisplayResults (colCount, loadFactor, loop);
      }
      
    }
    cout << endl;
  }
  //return 0 if memory was allocated properly for hash table chainingArray
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
    //use modulo-division method by calling HASH function
    address = Hash(randArray[key],tbSize);
    if(hashTable[address] != 0){
      //if new address is NULL 
      LinearProbe(address, hashTable, 0, tbSize, nulCount);
    }
    //once null address found add int to hash table
    hashTable[address] = randArray[key];
    //increment
    ++key;
  }
  //return full hash table
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
  //linear probe list until int probeThis is
  //an exact match with hashTable[address]  
  while(hashTable[address] != probeThis){
    ++colCount;
    ++address;
    //prevent addresses above table size being accessed
    if(address >= tbSize)
      address = 0;
      
  }
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
  
  //calculate knuth using loadFactor for each loop
  //0 = linear probing
  //1 = Double hash
  //2 = Separate Chaining
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
  //get average
  avg = colCount / NUM_ITEMS_TO_SEARCH_DBL;
  //print results to user
  cout << fixed << setprecision(2) << right << setfill(' ') << setw(7);
  cout << colCount << " items examined (avg = " 
       << avg      << " items examined per search)"         << endl;
  cout << "     vs Knuth predicted avg = " << knuthResults
       << " items examined per search"                      << endl << endl;
  
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
         errorCount;
  
  infiniteLoop = false; 
    
  while((key < MAX_KEYS) && !infiniteLoop){
    //call modulos division method
    address    = Hash(randArray[key], tbSize);
    errorCount = 0;
    while((hashTable[address] != 0) && !infiniteLoop){
      //use double hash until address is found or
      //error count becomes too high
      address += DoubleHash(randArray[key], tbSize);
      ++errorCount;
      //redo hash if address reaches the end of list
      if (address > tbSize)
        address = address % tbSize;
      //if error count becomes to high escape while loop
      if (errorCount > (2 * tbSize))
        infiniteLoop = true;                       
    }
    //if found give hashtable address new key
    hashTable[address] = randArray[key];
    //increment
    ++key;
  }
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
  int       key       = 0,
            address   = 0; 
  TABLE *newPtr    = NULL;
  bool  heapError = false;
  
  while ((key < MAX_KEYS) && !heapError) {
    //get address via modulos division method
    address = Hash(randArray[key], tbSize);          
    //enter random int into correct address in
    //new node
    if (chainingArray[address].key == 0) { 
      chainingArray[address].key  = randArray[key];
      chainingArray[address].next = NULL;
      ++key;
    }
    //allocate memory for new node from heap
    else if (chainingArray[address].key != 0) {
      newPtr = new (nothrow) TABLE;   
      if (newPtr == NULL) {
        cout << "Heap error - could not allocate memory." << endl;
        heapError = true;
      }
      //add new node to linked list
      else {
        newPtr->key  = randArray[key];
        newPtr->next = chainingArray[address].next;
        chainingArray[address].next = newPtr;
        ++key;
      }
    }
  }       

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
  int key     = 0,
      address = 0;
    
  colCount = 0;//resetting count for each collision method
  //using random array for matches therefore while loops until
  //all matches are discovered against MAX_KEYS which is the 
  //same amount of indexes in the random array.  
  while(key < MAX_KEYS){
    //use function which runs modulo-division method
    address = Hash(randArray[key],tbSize);
    //if address directly after modulos is a match then
    //continue on imediatly 
    if (ht[address] == randArray[key])
      ++colCount;
    //if address is not a match use linear probe method searching
    else {
      while(ht[address] != randArray[key]){
        ++colCount;
        //if loop equals 0 use Linear probing
        //int loop was determined in driver function previously               
        if(loop == 0) {
          //call linear probe and try and find a matching address
	  LinearProbe(address, ht, randArray[key], tbSize, colCount);
	  ++colCount; 
        }
        //if loop equals 1 use Double Hash Method
        //int loop was determined in driver function previously
        else if(loop == 1){
          while (ht[address] != randArray[key]) {
            ++colCount;
            //call function to handle Double Hash function  
	    address += DoubleHash(randArray[key], tbSize);
	    if (address > tbSize) {
              //use modulo-division method if address becomes larger than
              //allowed table size.          
              address = address % tbSize;
            }
          }
        }
      }
    }
    //increment by two for entire while loop and continue on until
    //MAX_KEYS is reached    
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
  int      key         = 0,
           address     = 0;
  TABLE *tempPtr    = NULL; 

  colCount = 0;                 //reinitializing colCount

  while (key < MAX_KEYS){
    //use modulo-division method
    address =  Hash(randArray[key],tbSize);
    //if hashed address is a match then increment key and loop
    if (chainingArray[address].key == randArray[key]) {
      ++colCount;   //for the item being found at the first location                  
    }
    //if not traverse until found
    else {
      tempPtr  = chainingArray[address].next;
              
      while(tempPtr->key  != randArray[key]){
        ++colCount; //for each time the item is not found                                         
	tempPtr = tempPtr->next;        	       
      }             //end second while 
      
      ++colCount;   //for the item being found           
    }               //end of else statement
    
    key += 2; 
         
  }                 //end outer while

  return colCount;
}
