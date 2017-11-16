#include <iostream>
#include <set>
#include <stdlib.h>
#include "MinMaxHeap.h"
#include <stdexcept>

using namespace std ;


template <typename T>
void sanityCheck(MinMaxHeap<T>& H) {
   int n = H.size() ;
   T minKey, maxKey, leftKey, rightKey ;
   int minPos, maxPos, pos ;
   
   bool passed=true ;

   cout << "Sanity Check minHeap...\n" ;

   for (int i=1 ; i<=n ; i++) {
      H.locateMin(i,minKey,maxPos) ; 
      H.locateMax(maxPos,maxKey,minPos) ; 
      
      if (minKey != maxKey) {
         passed = false ;
         cout << "Key mismatch at i = " << i << ": "
	      << "minKey = " << minKey << ", " 
	      << "minPos = " << minPos << ", " 
	      << "maxKey = " << maxKey << ", " 
	      << "maxPos = " << maxPos 
	      << endl ;
      }

      if (minPos != i) {
         passed = false ;
         cout << "Position mismatch at i = " << i << ": "
	      << "minKey = " << minKey << ", " 
	      << "minPos = " << minPos << ", " 
	      << "maxKey = " << maxKey << ", " 
	      << "maxPos = " << maxPos 
	      << endl ;
      }

      if (2*i <= n) {  // has left child
         H.locateMin(2*i,leftKey,pos) ;
	 if (leftKey < minKey) {  // left child smaller than root 
	    passed = false ;
	    cout << "Bad heap condition at i = " << i << ": "
		 << "root key = " << minKey << ", " 
		 << "left key = " << leftKey 
		 << endl ;
	 }
      }  

      if (2*i+1 <= n) {  // has right child
         H.locateMin(2*i+1,rightKey,pos) ;
	 if (rightKey < minKey) {  // right child smaller than root 
	    passed = false ;
	    cout << "Bad heap condition at i = " << i << ": "
		 << "root key = " << minKey << ", " 
		 << "right key = " << rightKey 
		 << endl ;
	 }
      }  

   }  // end of for (...)


   cout << "Sanity Check maxHeap...\n" ;

   for (int i=1 ; i<=n ; i++) {
      H.locateMax(i,maxKey,minPos) ; 
      H.locateMin(minPos,minKey,maxPos) ; 
      
      if (minKey != maxKey) {
         passed = false ;
         cout << "Key mismatch at i = " << i << ": "
	      << "minKey = " << minKey << ", " 
	      << "minPos = " << minPos << ", " 
	      << "maxKey = " << maxKey << ", " 
	      << "maxPos = " << maxPos 
	      << endl ;
      }

      if (maxPos != i) {
         passed = false ;
         cout << "Position mismatch at i = " << i << ": "
	      << "minKey = " << minKey << ", " 
	      << "minPos = " << minPos << ", " 
	      << "maxKey = " << maxKey << ", " 
	      << "maxPos = " << maxPos 
	      << endl ;
      }

      if (2*i <= n) {  // has left child
         H.locateMax(2*i,leftKey,pos) ;
	 if (leftKey > maxKey) {  // left child bigger than root 
	    passed = false ;
	    cout << "Bad heap condition at i = " << i << ": "
		 << "root key = " << maxKey << ", " 
		 << "left key = " << leftKey 
		 << endl ;
	 }
      }  

      if (2*i+1 <= n) {  // has right child
         H.locateMax(2*i+1,rightKey,pos) ;
	 if (rightKey > maxKey) {  // right child bigger than root 
	    passed = false ;
	    cout << "Bad heap condition at i = " << i << ": "
		 << "root key = " << maxKey << ", " 
		 << "right key = " << rightKey 
		 << endl ;
	 }
      }  
   }  // end of for (...)


   if (passed) {
      cout << "Passed sanityCheck().\n" ;
   } else {
      cout << "*** Failed sanityCheck().\n" ;
   }
}

template <typename T>
void checkAgainstSet(MinMaxHeap<T>& H, multiset<T,greater<T> >& origS) {
   multiset<T,greater<T> > S ;  
   typename multiset<T,greater<T> >::iterator it ;

   int n = H.size() ;
   int pos ;
   int key ;

   bool passed = true ;

   S = origS ;  // make copy

   if ( n != S.size() ) {
      passed = false ;
      cout << "Heap and multiset sizes do not match!\n" ;
      cout << "   Heap size = " << n << endl ;
      cout << "   Set size  = " << S.size() << endl ;
   }


   for (int i=1 ; i <= n ; i++) {
      H.locateMin(i,key,pos) ;
      it = S.find(key) ;
      if (it == S.end()) {
        passed = false ;
	cout << "Key " << key << " in the min-heap but not in the multiset.\n" ;
      } else {
        S.erase(it) ;
      }
   }

   if (S.size() > 0) {
      cout << "There are " << S.size() 
           << " items in multiset that not in the min-heap.\n" ;
      for (it=S.begin() ; it != S.end() ; it++) {
         cout << *it << " " ;
      }
      cout << endl ;
   }


   S = origS ;  // start over

   for (int i=1 ; i <= n ; i++) {
      H.locateMax(i,key,pos) ;
      it = S.find(key) ;
      if (it == S.end()) {
        passed = false ;
	cout << "Key " << key << " in the max-heap but not in the multiset.\n" ;
      } else {
        S.erase(it) ;
      }
   }

   if (S.size() > 0) {
      cout << "There are " << S.size() 
           << " items in multiset that not in the max-heap.\n" ;
      for (it=S.begin() ; it != S.end() ; it++) {
         cout << *it << " " ;
      }
      cout << endl ;
   }

   if (passed) {
      cout << "Passed check against multiset\n" ;
   } else {
      cout << "***Failed check against multiset\n" ;
   }

}


template <typename T>
void checkAgainstSet(MinMaxHeap<T>& H, multiset<T>& origS) {
   multiset<T> S ;  
   typename multiset<T>::iterator it ;

   int n = H.size() ;
   int pos ;
   int key ;

   bool passed = true ;

   S = origS ;  // make copy

   if ( n != S.size() ) {
      passed = false ;
      cout << "Heap and multiset sizes do not match!\n" ;
      cout << "   Heap size = " << n << endl ;
      cout << "   Set size  = " << S.size() << endl ;
   }


   for (int i=1 ; i <= n ; i++) {
      H.locateMin(i,key,pos) ;
      it = S.find(key) ;
      if (it == S.end()) {
        passed = false ;
	cout << "Key " << key << " in the min-heap but not in the multiset.\n" ;
      } else {
        S.erase(it) ;
      }
   }

   if (S.size() > 0) {
      cout << "There are " << S.size() 
           << " items in multiset that not in the min-heap.\n" ;
      for (it=S.begin() ; it != S.end() ; it++) {
         cout << *it << " " ;
      }
      cout << endl ;
   }


   S = origS ;  // start over

   for (int i=1 ; i <= n ; i++) {
      H.locateMax(i,key,pos) ;
      it = S.find(key) ;
      if (it == S.end()) {
        passed = false ;
	cout << "Key " << key << " in the max-heap but not in the multiset.\n" ;
      } else {
        S.erase(it) ;
      }
   }

   if (S.size() > 0) {
      cout << "There are " << S.size() 
           << " items in multiset that not in the max-heap.\n" ;
      for (it=S.begin() ; it != S.end() ; it++) {
         cout << *it << " " ;
      }
      cout << endl ;
   }

   if (passed) {
      cout << "Passed check against multiset\n" ;
   } else {
      cout << "***Failed check against multiset\n" ;
   }

}




void test1() {
   MinMaxHeap<int> H(25) ;
   H.insert(5) ;
   H.insert(10) ;
   H.insert(7) ;
   H.insert(9) ;
   H.insert(6) ;
   H.insert(2) ;
   H.insert(16) ;
   H.insert(12) ;
   H.insert(11) ;

   cout << "Initial MinMax Heap\n" ;
   H.dump() ;

   H.insert(8); 
   cout << "After inserting 8\n" ;
   H.dump() ;

   sanityCheck(H) ;

   int answer ;
   answer = H.deleteMin() ;
   cout << "\n\nMin item " << answer << " removed from MinMax Heap\n" ;

   H.dump() ;
   sanityCheck(H) ;

   answer = H.deleteMax() ;
   cout << "\n\nMax item " << answer << " removed from MinMax Heap\n" ;

   H.dump() ;
   sanityCheck(H) ;
}

void test2(){

   MinMaxHeap<string> H(25) ;
   H.insert("jkl") ;
   H.insert("yz_") ;
   H.insert("abc") ;
   H.insert("mno") ;
   H.insert("vwx") ;
   H.insert("pqr") ;
   H.insert("ghi") ;
   H.insert("def") ;
   H.insert("stu") ;

   H.dump() ;
   sanityCheck(H) ;

   string answer ;
   answer = H.deleteMin() ;
   cout << "Min item " << answer << " removed from MinMax Heap\n" ;

   answer = H.deleteMax() ;
   cout << "Max item " << answer << " removed from MinMax Heap\n" ;

   H.dump() ;
   sanityCheck(H) ;

}

void test3(){

	cout << "No copy string has not been done on this driver since it will not work without the files" << endl;
}

void test4(){

   srand(4178012351) ;

   MinMaxHeap<int> H(1000) ;
   multiset<int> S ;
   multiset<int>::iterator it ;
   int key ;
   bool passed ;

   for (int i=0 ; i < 500 ; i++) {
      key = rand() % 100 ;
      // cout << "Insert key = " << key << endl ;
      H.insert(key) ;
      S.insert(key) ;
   }
   sanityCheck(H) ;
   checkAgainstSet(H,S) ;

   passed = true ;
   for (int i=0 ; i < 450 ; i++) {
      key = H.deleteMin() ;
      if (key != *S.begin()) {
         passed = false ;
         cout << "deleteMin() returns key that is not the smallest key!\n" ;
      } else {
         S.erase(S.begin()) ;
      }
   }

   sanityCheck(H) ;

   if (passed) {
      checkAgainstSet(H,S) ;
   } else {
      cout << "***Failed deleteMin() test!\n" ;
      cout << "Skipped check against multiset\n" ;
   }


}


void test5(){
   srand(4178012351) ;

   MinMaxHeap<int> H(1000) ;
   multiset<int,greater<int> > S ;
   multiset<int,greater<int> >::iterator it ;
   int key ;
   bool passed ;

   for (int i=0 ; i < 750 ; i++) {
      key = rand() % 100 ;
      // cout << "Insert key = " << key << endl ;
      H.insert(key) ;
      S.insert(key) ;
   }
   sanityCheck(H) ;
   checkAgainstSet(H,S) ;

   passed = true ;
   for (int i=0 ; i < 400 ; i++) {
      key = H.deleteMax() ;
      if (key != *S.begin()) {
         passed = false ;
         cout << "deleteMax() returns key that is not the largest key!\n" ;
      } else {
         S.erase(S.begin()) ;
      }
   }

   sanityCheck(H) ;

   if (passed) {
      checkAgainstSet(H,S) ;
   } else {
      cout << "***Failed deleteMax() test!\n" ;
      cout << "Skipped check against multiset\n" ;
   }


}


void test6(){
   MinMaxHeap<int> H(25) ;
   H.insert(5) ;
   H.insert(10) ;
   H.insert(7) ;
   H.insert(9) ;
   H.insert(6) ;
   H.insert(2) ;
   H.insert(16) ;
   H.insert(12) ;
   H.insert(11) ;

   cout << "Initial MinMax Heap\n" ;
   H.dump() ;
   sanityCheck(H) ;

   MinMaxHeap<int> *Gptr = new MinMaxHeap<int>(H) ;
   cout << "copied MinMax Heap\n" ;
   Gptr->dump();

   H.deleteMax() ;
   Gptr->deleteMin() ;
   cout << "\nH and *Gptr after deleteMax and deleteMin\n" ;
   sanityCheck(H) ;
   sanityCheck(*Gptr) ;

   delete Gptr ;

   cout << "\nH after Gptr deleted\n" ;
   H.deleteMin() ;
   H.deleteMax() ;
   sanityCheck(H) ;

   MinMaxHeap<int> K1(11) ;
   K1.insert(29) ;
   K1.insert(24) ;
   K1.insert(23) ;
   K1.insert(22) ;
   K1.insert(28) ;
   K1.insert(26) ;
   K1.insert(30) ;
   K1.insert(21) ;
   K1.insert(25) ;
   K1.insert(27) ;

   cout << "\nK1 after inserts\n" ;
   sanityCheck(K1) ;

   MinMaxHeap<int> K2(4) ;
   K2.insert(43) ;
   K2.insert(42) ;
   K2.insert(44) ;
   K2.insert(41) ;

   cout << "\nK2 after inserts\n" ;
   sanityCheck(K2) ;

   K2 = K1 ;
   K1.deleteMax() ;
   K2.insert(57) ;

   cout << "\nK1 & K2 after assignment, etc...\n" ;
   sanityCheck(K1) ;
   sanityCheck(K2) ;

}

//Testing out of bounds errors
void test7(){
  
  MinMaxHeap<int> H(3);
  try{
    H.deleteMax();
    H.dump();
  }
  catch(exception e){
    cout << "Exception in delete" << endl;
  }
  try{
    H.insert(5);
    H.insert(4);
    H.insert(3);
    H.insert(2);
    H.dump();
  }
  catch(exception e){
    cout << "Exception in insert" << endl;
  }

}

//Massive insert and delete
void test8(){

  cout <<"Start" << endl;
  MinMaxHeap<int> H(1000000);
  for(int i = 1; i <= 500000; i++){
    H.insert(i);
  }
  for(int i = 1000000; i > 500000; i--){
    H.insert(i);
  }
  sanityCheck(H);
  for(int i = 1; i <= 500000; i++){
    H.deleteMax();
    H.deleteMin();
  }
  cout << "Finished" << endl;
}


//Same test, 10 times as large
void test9(){

  cout <<"Start" << endl;
  MinMaxHeap<int> H(10000000);		      
  cout <<"Heap built" << endl;
  for(int i = 1; i <= 5000000; i++){
    H.insert(i);
  }
  for(int i = 10000000; i > 5000000; i--){
    H.insert(i);
  }
  sanityCheck(H);
  for(int i = 1; i <= 5000000; i++){
    H.deleteMax();
    H.deleteMin();
  }
  cout << "Finished" << endl;
}

//Main driver
int main(){

  int userInput;
  do{
    cout << "Menu for driver program for MinMaxHeap" <<endl
	 << "Choose from below: 0 to end" << endl;
    for(int i = 1; i <10; i++){
      cout << i << ". test " << i << endl;
    }

    //Asking for user input
    cout << "Enter your choice: " << endl;
    cin >> userInput;

    //Tells user if input is invalid
    if (userInput < 0 || userInput > 10)
      cout << "Invalid input. Please try again." << endl;
    else{
      switch(userInput){
      case 1:
	test1();
	break;
      case 2:
	test2();
	break;
      case 3: 
	test3();
	break;
      case 4:
	test4();
	break;

      case 5:
	test5();
	break;

      case 6:
	test6();
	break;

      case 7:
	test7();
	break;
      case 8:
	test8();
	break;
      case 9:
	test9();
	break;
      }
    }
  } while(userInput != 0);

}

