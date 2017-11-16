// File: HashTable.cpp
//
// CMSC 341 Sprint 2017 Project 5
// Seung Hun Lee
// Function definition for HashTable
//


#include "HashTable.h"
#include "primes.h"

using namespace std;

//Deleted definition
char * const HashTable::DELETED  = (char *) 1 ;


unsigned int hashCode(const char *str) {

  unsigned int val = 0 ;
  const unsigned int thirtyThree = 33 ;  // magic number from textbook

  int i = 0 ;
  while (str[i] != '\0') {
    val = val * thirtyThree + str[i] ;
    i++ ;
  }
  return val ;
}

int findPrime(int n, int primeBegin = 0, int primeEnd = numPrimes - 1){
  if(n <= 101)
    return 101;
  if(n >= 200000)
    throw out_of_range("Size out of range");
  int currentIndex = (primeEnd - primeBegin) / 2   + primeBegin;
  int currentPrime = primes[currentIndex];
  if(currentPrime < n){
    return findPrime(n, currentIndex + 1, primeEnd);
  }
  else{
    if(primes[currentIndex - 1] < n && currentPrime >= n)
      return currentPrime;
    else{
      return findPrime(n, primeBegin, currentIndex - 1);
    }
  }
}

//Basic constructor also possible with input
HashTable::HashTable(int n){
  //Only worry about first table since other two don't matter yet
  capacity0 = findPrime(n);
  table0 = new char* [capacity0]();
  currentSize0 = 0;
  
  rehashing = 0;

  table1 = NULL;
  table2 = NULL;
  currentSize1 = 0;
  currentSize2 = 0;
}

//Destructor
HashTable::~HashTable(){
  //Destruct table0
  if(table0 != NULL){
    for(int i = 0; i < capacity0; i++){
      if(table0[i] != NULL && table0[i] != DELETED)
	free(table0[i]);      
    }
  }
  delete[] table0;

  //Destruct table1
  if(table1 != NULL){
    for(int i = 0; i < capacity1; i++){
      if(table1[i] != NULL && table1[i] != DELETED)
	free(table1[i]);      
    }
  }
  delete[] table1;
  
  //Destruct table2
  if(table2 != NULL){
    for(int i = 0; i < capacity2; i++){
      if(table2[i] != NULL && table2[i] != DELETED)
	free(table2[i]);      
    }
  }
  delete[] table2;
}

//Copy constructor
HashTable::HashTable(HashTable& other){
  if(other.rehashing > 0)
    other.rehash();

  //Only worry about first table since other two don't matter yet
  capacity0 = other.capacity0;
  table0 = new char* [capacity0]();
  for(int i = 0; i < capacity0; i++){
    if(other.table0[i] != NULL && other.table0[i] != DELETED){
      table0[i] = strdup(other.table0[i]);
    }
  }
  currentSize0 = other.currentSize0;
  
  rehashing = 0;

  table1 = NULL;
  table2 = NULL;
  currentSize1 = 0;
  currentSize2 = 0;

}

//Assignment operator
const HashTable& HashTable::operator=(HashTable& rhs){

  //Deallocate existing memory first
  if(table0 != NULL){
    for(int i = 0; i < capacity0; i++){
      if(table0[i] != NULL && table0[i] != DELETED)
	free(table0[i]);      
    }
  }
  delete[] table0;

  //Destruct table1
  if(table1 != NULL){
    for(int i = 0; i < capacity1; i++){
      if(table1[i] != NULL && table1[i] != DELETED)
	free(table1[i]);      
    }
  }
  delete[] table1;
  
  //Destruct table2
  if(table2 != NULL){
    for(int i = 0; i < capacity2; i++){
      if(table2[i] != NULL && table2[i] != DELETED)
	free(table2[i]);      
    }
  }
  delete[] table2;

  //Let the rhs finish rehashing if needed
  if(rhs.rehashing > 0)
    rhs.rehash();

  capacity0 = rhs.capacity0;
  table0 = new char* [capacity0]();
  for(int i = 0; i < capacity0; i++){
    if(rhs.table0[i] != NULL && rhs.table0[i] != DELETED){
      table0[i] = strdup(rhs.table0[i]);
    }
  }
  currentSize0 = rhs.currentSize0;
  
  rehashing = 0;

  table1 = NULL;
  table2 = NULL;
  currentSize1 = 0;
  currentSize2 = 0;

  return *this;
} 
//Inserts an element and rehashes if needed
void HashTable::insert(const char * str){
  int probeCount = 1;//Counter for linear probe
  unsigned int hashIndex = hashCode(str);//Keeps track of hashcode
  unsigned int currentIndex;//Keeps track of current index
  bool duplicate = false;//Keeps track of whether element is already present
  unsigned int insertHere = -1;//index to insert to
  int probeCount1 = 1;//Counter for linear probe for second table if needed

  //Move touched cluster
  if(table0[hashIndex % capacity0] != NULL && rehashing == 1){
    rehashCluster(hashIndex % capacity0);
  }

  //insert to table0 if not rehashing
  if(rehashing == 0){
    currentIndex = hashIndex % capacity0;
    //Loop till NULL is found
    while(table0[currentIndex] != NULL){
      probeCount++;
      //String is already there
      if(table0[currentIndex] == DELETED){
	if(insertHere == -1)
	  insertHere = currentIndex;
      }
      else if(strcmp(table0[currentIndex], str) == 0){
	duplicate = true;
      }

      currentIndex = (currentIndex + 1)% capacity0;
    }
    
    //Insert only if this is not duplicate
    if(!duplicate){
      if(insertHere != -1)
	table0[insertHere] = strdup(str);
      else
	table0[currentIndex] = strdup(str);

      currentSize0++;
    }

    //Check for rehash triggers and rehash if needed
    if(probeCount >= 10){
      rehashing = 1;
      rehashCluster(hashIndex % capacity0 );
    }
    
    if((currentSize0/(double)capacity0) > .5){
      rehashing = 1;
      rehashCluster(hashIndex % capacity0);
    }
  }

  //If we're working on the second table
  else if(rehashing == 1){

    currentIndex = hashIndex % capacity1;

    //Loop till NULL is found
    while(table1[currentIndex] != NULL){
      probeCount1++;

      if(table1[currentIndex] == DELETED){
	if(insertHere == -1)
	  insertHere = currentIndex;
      }
      else if(strcmp(table1[currentIndex], str) == 0)
	duplicate = true;
      
      currentIndex = (currentIndex + 1)% capacity1;
    }
    
    //Insert only if this is not duplicate
    if(!duplicate){
      if(insertHere != -1)
	table1[insertHere] = strdup(str);
      else
	table1[currentIndex] = strdup(str);
      currentSize1++;
    }

    //Full rehash if second one is needed
    if(probeCount1 >= 10){
      rehashing = 2;
      rehash();
    }
    
    if((currentSize1/(double)capacity1) > .5){
      rehashing = 2;
      rehash();
    }
  }

  //If we're rehashing to third table. Should not be actually used
  else if(rehashing == 2){

    currentIndex = hashIndex % capacity2;

    //Loop till NULL is found
    while(table2[currentIndex] != NULL){
      
      if(table2[currentIndex] == DELETED){
	if(insertHere == -1)
	  insertHere = currentIndex;
      }
      if(strcmp(table2[currentIndex], str) == 0)
	duplicate = true;

      currentIndex = (currentIndex + 1)% capacity2;
    }
    
    //Insert only if this is not duplicate
    if(!duplicate){
      if(insertHere != -1)
	table2[insertHere] = strdup(str);
      else
	table2[currentIndex] = strdup(str);
      currentSize2++;
    }
  }
}

//Inserts to table1
void HashTable::insertToOne(const char * str){
  unsigned int hashIndex = hashCode(str); //keeps track of hashcode
  unsigned int currentIndex = hashIndex % capacity1;//Current index
  int probeCount = 1; //probe counter on table0
  unsigned int insertHere = -1; //Where to insert if DELETED is present
  bool duplicate = false; //Tells whether the element is already there

  //Loop till NULL is found
  while(table1[currentIndex] != NULL){
    probeCount++;
    
    if(table1[currentIndex] == DELETED){
      if(insertHere == -1)
	insertHere = currentIndex;
    }
    else if(strcmp(table1[currentIndex], str) == 0)
      duplicate = true;
    
    currentIndex = (currentIndex + 1)% capacity1;
  }
    
  //Insert only if this is not duplicate
  if(!duplicate){
    if(insertHere != -1)
      table1[insertHere] = strdup(str);
    else
      table1[currentIndex] = strdup(str);
    currentSize1++;
  }
    
  if(probeCount >= 10){
    rehashing = 2;
    rehash();
  }
    
  if((currentSize1/(double)capacity1) > .5){
    rehashing = 2;
    rehash();
  }
}

//Insert to table2
void HashTable::insertToTwo(const char * str){
  unsigned int hashIndex = hashCode(str); //Keeps track of hash code
  unsigned int currentIndex = hashIndex % capacity2; //Keeps track of current index
  unsigned int insertHere = -1; //Keeps track of any DELETED that can be inserted to
  bool duplicate = false; //Keeps track of whether new str is a duplicate

  //Loop till NULL is found
  while(table2[currentIndex] != NULL){
    
    if(table2[currentIndex] == DELETED){
      if(insertHere == -1)
	insertHere = currentIndex;
    }
    else if(strcmp(table2[currentIndex], str) == 0)
      duplicate = true;
    
    currentIndex = (currentIndex + 1)% capacity2;
  }
    
  //Insert only if this is not duplicate
  if(!duplicate){
    if(insertHere != -1)
      table2[insertHere] = strdup(str);
    else
      table2[currentIndex] = strdup(str);
    currentSize2++;
  }
}

//Finds whether a string is in the table
bool HashTable::find(const char * str){
  int probeCount = 1;//Counter for linear probe
  unsigned int hashIndex = hashCode(str);//Keeps track of where to insert
  unsigned int currentIndex; //Keeps track of current index
  bool strFound = false;//Keeps track of whether element is found
  int probeCount1 = 1;//Counter for linear probe on second table


  //Move touched cluster if rehashing
  if(table0[hashIndex % capacity0] != NULL && rehashing == 1){
    rehashCluster(hashIndex % capacity0);
  }

  //Not rehashing only one table
  if(rehashing == 0){
    currentIndex = hashIndex % capacity0;

    while(table0[currentIndex] != NULL){
      probeCount++;
      //Skip DELETED
      if(table0[currentIndex] == DELETED){
      }
      else if( strcmp(table0[currentIndex], str) == 0){
	strFound = true;
      break;
      }
      currentIndex = (currentIndex + 1) % capacity0;
    }
    
    //Check conditions to see if it needs rehashing and do so if needed
    if(probeCount >= 10){
      rehashing = 1;
      rehashCluster(hashIndex % capacity0 );
    }
    
    if((currentSize0/(double)capacity0) > .5){
      rehashing = 1;
      rehashCluster(hashIndex % capacity0);
    }
  }
  
  //Rehashing
  else if(rehashing == 1){
    		    
    //Look for element in second table
    currentIndex = hashIndex % capacity1;
    
    while(table1[currentIndex] != NULL){
      probeCount1++;
      if(table1[currentIndex] == DELETED){}
      else if(strcmp(table1[currentIndex], str) == 0){
	strFound = true;
	break;
      }
      currentIndex = (currentIndex + 1) % capacity1;
    }
  
    //Check conditions for second rehash and do so if needed
    if(probeCount1 >= 10){
      rehashing = 2;
      rehash();
      
    }
    if((currentSize1/(double)capacity1) > .5){
      rehashing = 2;
      rehash();
    }
  }

  return strFound;
}

//Remove a string from table returns NULL if not found
char * HashTable::remove(const char *str){
  int probeCount = 1;//Counter for linear probe
  unsigned int hashIndex = hashCode(str);//Keeps track of where to insert
  unsigned int currentIndex;
  bool strFound = false;//Keeps track of whether element is found
  char * returnString = NULL;//String to return
  int probeCount1 = 1;//Counter for linear probe for second table

  //Move touched cluster if rehashing
  if(table0[hashIndex % capacity0] != NULL && rehashing == 1){
    rehashCluster(hashIndex % capacity0);
  }
  
  //Just remove frome table0 if it's the only one
  if(rehashing == 0){
    currentIndex = hashIndex % capacity0;
    while(table0[currentIndex] != NULL){
      probeCount++;
      if(table0[currentIndex] == DELETED){
	
      }
      else if(strcmp(table0[currentIndex], str) == 0){
	strFound = true;
	break;
      }
      currentIndex = (currentIndex + 1) % capacity0;
    }
    
    //Delete the string if found
    if(strFound){
      returnString = table0[currentIndex];
      table0[currentIndex] = DELETED;
      currentSize0--;
    }

    //CHeck for rehash conditions and do so if so
    if(probeCount >= 10){
      rehashing = 1;
      rehashCluster(hashIndex % capacity0 );
    }
    
    if((currentSize0/(double)capacity0) > .5){
      rehashing = 1;
      rehashCluster(hashIndex % capacity0);
    }
  }

  //Otherwise try to remove from table1
  else if(rehashing == 1){

    currentIndex = hashIndex % capacity1;
    while(table1[currentIndex] != NULL){
      probeCount1++;
      if(table1[currentIndex] == DELETED){

      }
      else if(strcmp(table1[currentIndex], str) == 0){
	strFound = true;
	break;
      }
      currentIndex = (currentIndex + 1) % capacity1;
    }

    //Delete the string if found
    if(strFound){
      returnString = table1[currentIndex];
      table1[currentIndex] = DELETED;
      currentSize1--;
    }

    //Check if second rehash is needed and do so if so
    if(probeCount1 >= 10){
      rehashing = 2;
      rehash();
    }
    
    if((currentSize1/(double)capacity1) > .5){
      rehashing = 2;
      rehash();
    }
  }
  
  return returnString;
}

//Rehashes one cluster
void HashTable::rehashCluster(unsigned int index){
  
  unsigned int m_index = index;

  //Create table1 if it's not already there
  if(table1 == NULL){
    capacity1 = findPrime(currentSize0 * 4);
    currentSize1 = 0;
    table1 = new char * [capacity1]();
  }

  //Move the leftRehash so it will start with a whole cluster not a part of one
  while(table0[(m_index - 1) % capacity0] != NULL){
    m_index = (m_index - 1) % capacity0;
  }

  //Move cluster to table1, checking table1 to see if second rehashing has been completed
  while(table0[m_index] != NULL && table1 != NULL){
    if(table0[m_index] != DELETED){
      insertToOne(table0[m_index]);
      
      //Protected in case second rehash
      if(table1 != NULL){
	free(table0[m_index]);
	table0[m_index] = NULL;
	
	currentSize0--;
      }
    }
    
    m_index = (m_index + 1) % capacity0;
  }
  
  //Finish moving everything if few items are left
  if((currentSize0/(double)capacity0) < .03){
    while(currentSize0 > 0){
      if(table0[m_index] != NULL && table0[m_index] != DELETED && table1 != NULL){
	insertToOne(table0[m_index]);
	if(table1 != NULL){
	  free(table0[m_index]);
	  table0[m_index] = NULL;
	  
	  currentSize0--;
	}
      }
      m_index = (m_index + 1) % capacity0;
    }
    
    rehashing = 0;
    delete[] table0;
    table0 = table1;
    table1 = NULL;
    currentSize0 = currentSize1;
    capacity0 = capacity1; 
  }

}

//Rehash completely
void HashTable::rehash(){
  unsigned int rehashCounter = 0;
  capacity2 = findPrime((currentSize0 + currentSize1) * 4);
  currentSize2 = 0;
  table2 = new char * [capacity2]();
  
  //First table to third table
  while(currentSize0 > 0){
    if(table0[rehashCounter] != NULL && table0[rehashCounter] != DELETED){
      insertToTwo(table0[rehashCounter]);
      free(table0[rehashCounter]);
      table0[rehashCounter] = NULL;
      
      currentSize0--;
    }
    
    //Protected step just in case
    rehashCounter = (rehashCounter + 1) % capacity0;
  }
  delete[] table0;

  //Second table to third table
  if(table1 != NULL){
    unsigned int rehashCounter1 = 0;//int to step through second table
    while(currentSize1 > 0){
      if(table1[rehashCounter1] != NULL && table1[rehashCounter1] != DELETED){
	insertToTwo(table1[rehashCounter1]);
	free(table1[rehashCounter1]);
	table1[rehashCounter1] = NULL;
	
	currentSize1--;
      }
      
      //Protected step just in case
      rehashCounter1 = (rehashCounter1 + 1) % capacity1;
    }
    delete[] table1;
  }
  table0 = table2;
  table1 = NULL;
  table2 = NULL;
  currentSize0 = currentSize2;
  capacity0 = capacity2;
  rehashing = 0;
}


//Tells whether the table is rehashing
bool HashTable::isRehashing(){
  return (rehashing > 0);
}

//Returns table size
int HashTable::tableSize(int table){
  if(table == 0)
    return capacity0;
  else if(table == 1 )
    return capacity1;
  else if(table == 2)
    return capacity2;
  else
    throw out_of_range("out of range");
}

//Returns current number of items in table
int HashTable::size(int table){
  if(table == 0)
    return currentSize0;
  else if(table == 1 )
    return currentSize1;
  else if(table == 2)
    return currentSize2;
  else
    throw out_of_range("out of range");
}

//Returns string at index of table chosen
const char * HashTable::at(int index, int table){
  if(table == 0){
    if(index >= capacity0)
      throw out_of_range("Index out of range");
    else
      return table0[index];
  }
  else if(table == 1 ){
    if(index >= capacity1)
      throw out_of_range("Index out of range");
    else
      return table1[index];
  }
  else if(table == 2){
    if(index >= capacity2)
      throw out_of_range("Index out of range");
    else
      return table2[index];
  }
  else
    throw out_of_range("out of range");
}

//Dumps out all the tables
void HashTable::dump(){
  cout << "HashTable #1: size = " << currentSize0 <<
    ", tableSize = " << capacity0 << endl;
  for(int i = 0; i < capacity0 ; i++){
    cout << "H1[" << i << "] =" ;
    if(table0[i] == DELETED)
      cout << "DELETED" ;
    else if(table0[i] != NULL)
      cout << table0[i] << " (" << hashCode(table0[i]) % capacity0 << ")";
    cout << endl;
  }

  if(rehashing){
    cout << endl << endl << endl << "HashTable #2: size = " << currentSize1 <<
      ", tableSize = " << capacity1 << endl;
    for(int i = 0; i < capacity1 ; i++){
      cout << "H2[" << i << "] =" ;
      if(table1[i] == DELETED)
	cout << "DELETED" ;
      else if(table1[i] != NULL)
	cout << table1[i]  << " (" << hashCode(table1[i]) % capacity1 << ")";
      cout << endl;
    }
  }
}
