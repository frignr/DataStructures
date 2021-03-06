// File: Driver.cpp
//
// CMSC 341 Sprint 2017 Project 3
// Seung Hun Lee
// Driver for LazyBST
// Has a menu to switch between various tests
// Tests 1-7 are provided tests, others are 
// student produced.
#include <iostream>
#include "LazyBST.h"
#include <stdexcept>
using namespace std;

//test1.cpp
void test1(){

  LazyBST T ;
  
  T.insert(70) ;
  T.inorder() ; cout << endl ;
  
  T.insert(30) ;
  T.inorder() ; cout << endl ;
  
  T.insert(110) ;
  
  T.inorder() ; cout << endl ;
  
  cout << "\n\n***** Insert 40 *****\n" ;
  T.insert(40) ;
  T.inorder() ; cout << endl ;
  
  cout << "\n\n***** Insert 20 *****\n" ;
  T.insert(20) ;
  T.inorder() ; cout << endl ;
  
  cout << "\n\n***** Insert 41 *****\n" ;
  T.insert(41) ;
  T.inorder() ; cout << endl ;
  
  cout << "\n\n***** Insert 31 *****\n" ;
  T.insert(31) ;
  T.inorder() ; cout << endl ;
  
  cout << "\n\n***** Insert 32 *****\n" ;
  T.insert(32) ;
  T.inorder() ; cout << endl ;
  
  cout << "\n\n***** Insert 33 *****\n" ;
  T.insert(33) ;
  T.inorder() ; cout << endl ;
  
  cout << "\n\n***** Insert 19 *****\n" ;
  T.insert(19) ;
  T.inorder() ; cout << endl ;
  
  cout << "\n\n***** Insert 34 *****\n" ;
  T.insert(34) ;
  T.inorder() ; cout << endl ;
  
  cout << "\n\n***** Insert 15 *****\n" ;
  T.insert(15) ;
  T.inorder() ; cout << endl ;
  
  cout << "\n\n***** Insert 14 *****\n" ;
  T.insert(14) ;
  T.inorder() ; cout << endl ;
}

//test2.cpp
void test2(){

  LazyBST T ;

  T.insert(14) ;

  T.insert(7) ;
  T.insert(25) ;

  T.insert(3) ; T.insert(32) ; 
  T.insert(9) ; T.insert(18) ; 

  T.insert(1) ; T.insert(44) ;
  T.insert(12) ; T.insert(15) ; 
  T.insert(4) ; T.insert(29) ; 
  T.insert(10) ; T.insert(21) ;

  T.inorder() ; cout << endl ;

  cout << "removing ..." << endl; 
  //   T.dump() ;

  int n ;

  n = 44 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 32 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 29 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 21 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 18 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 25 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 15 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 14 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 12 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 10 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 9 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
}

//test3.cpp
void test3(){
  LazyBST T;

  T.insert(14) ;

  T.insert(7) ;
  T.insert(25) ;

  T.insert(3) ; T.insert(32) ; 
  T.insert(9) ; T.insert(18) ; 

  // Inserting duplicates
  
  T.insert(3) ; T.insert(32) ; 
  T.insert(9) ; T.insert(18) ; 

  T.insert(1) ; T.insert(44) ;
  T.insert(12) ; T.insert(15) ; 
  T.insert(4) ; T.insert(29) ; 
  T.insert(10) ; T.insert(21) ;

  T.inorder() ; cout << endl ;

  cout << "removing ..." << endl; 
  int answer ;
  //   T.dump() ;

  int n ;

  n = 14 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 12 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n =  7 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 25 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n =  3 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 29 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 32 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 15 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 


  // Removing items that do not exist
  cout << endl ;
  n = 19 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 101 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = -32 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  cout << endl ;

  n = 18 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 21 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 10 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n =  9 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n =  1 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n = 44 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
  n =  4 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
}

//Test4.cpp
void test4(){
  LazyBST T ;

  T.insert(14) ;

  T.insert(7) ;
  T.insert(3) ; T.insert(1) ; T.insert(4) ;
  T.insert(10) ; T.insert(9) ; T.insert(12) ;

  T.insert(25) ;
  T.insert(18) ; T.insert(15) ; T.insert(21) ;
  T.insert(32) ; T.insert(29) ; T.insert(44) ;

  //   T.dump() ;
  T.inorder() ; cout << endl ;

  int n, answer ;


  n = 3  ;
  cout << "Find " << n << endl ;
  if ( T.find(n) ) { 
    cout << "found = " << n << endl ;
  } else {
    cout << "did not find = " << n << endl ;
  }
  cout << endl ;


  n = 4  ;
  cout << "Find " << n << endl ;
  if ( T.find(n) ) { 
    cout << "found = " << n << endl ;
  } else {
    cout << "did not find = " << n << endl ;
  }
  cout << endl ;


  n = 29  ;
  cout << "Find " << n << endl ;
  if ( T.find(n) ) { 
    cout << "found = " << n << endl ;
  } else {
    cout << "did not find = " << n << endl ;
  }
  cout << endl ;


  n = 39  ;
  cout << "Find " << n << endl ;
  if ( T.find(n) ) { 
    cout << "found = " << n << endl ;
  } else {
    cout << "did not find = " << n << endl ;
  }
  cout << endl ;


  n = 301  ;
  cout << "Find " << n << endl ;
  if ( T.find(n) ) { 
    cout << "found = " << n << endl ;
  } else {
    cout << "did not find = " << n << endl ;
  }
  cout << endl ;


  // Checking remove...

  n = 21  ;
  cout << "Remove " << n << endl ;
  if ( T.remove(n) ) { 
    cout << n << " removed\n" ;
  } else {
    cout << n << " not found\n" ;
  }
  T.inorder() ; cout << endl ;

  n = 18  ;
  cout << "Remove " << n << endl ;
  if ( T.remove(n) ) { 
    cout << n << " removed\n" ;
  } else {
    cout << n << " not found\n" ;
  }
  T.inorder() ; cout << endl ;

  n = 7  ;
  cout << "Remove " << n << endl ;
  if ( T.remove(n) ) { 
    cout << n << " removed\n" ;
  } else {
    cout << n << " not found\n" ;
  }
  T.inorder() ; cout << endl ;

  n = 13  ;
  cout << "Remove " << n << endl ;
  if ( T.remove(n) ) { 
    cout << n << " removed\n" ;
  } else {
    cout << n << " not found\n" ;
  }
  T.inorder() ; cout << endl ;

  n = 29  ;
  cout << "Remove " << n << endl ;
  if ( T.remove(n) ) { 
    cout << n << " removed\n" ;
  } else {
    cout << n << " not found\n" ;
  }
  T.inorder() ; cout << endl ;

  n = 32  ;
  cout << "Remove " << n << endl ;
  if ( T.remove(n) ) { 
    cout << n << " removed\n" ;
  } else {
    cout << n << " not found\n" ;
  }
  T.inorder() ; cout << endl ;

  n = 14  ;
  cout << "Remove " << n << endl ;
  if ( T.remove(n) ) { 
    cout << n << " removed\n" ;
  } else {
    cout << n << " not found\n" ;
  }
  T.inorder() ; cout << endl ;
}

//test5.cpp
void test5(){
  LazyBST T1 ;

  T1.insert(14) ;

  T1.insert( 7) ;
  T1.insert(25) ;

  T1.insert( 3) ; T1.insert(32) ; 
  T1.insert( 9) ; T1.insert(18) ; 

  T1.insert( 1) ; T1.insert(44) ;
  T1.insert(12) ; T1.insert(15) ; 
  T1.insert( 4) ; T1.insert(29) ; 
  T1.insert(10) ; T1.insert(21) ;

  cout << "Original T1:         " ;
  T1.inorder() ; cout << endl ;

  // Use copy constructor
  LazyBST *Tptr = new LazyBST(T1) ;

  cout << "Copied T1:           " ;
  Tptr->inorder() ; cout << endl; 
   
  LazyBST T2 ;

  T2.insert(50) ;
  T2.insert(25) ; T2.insert(75) ;
  // T2.inorder() ; cout << endl ;

  T2 = *Tptr ;
  cout << "Second copy:         " ;
  T2.inorder() ; cout << endl ; 

  cout << "Delete first copy...\n" ;
  delete Tptr ;

  cout << "Recheck original:    " ;
  T1.inorder() ; cout << endl ;
  cout << "Recheck second copy: " ;
  T2.inorder() ; cout << endl ; 
}

//test6.cpp
void test6(){
  LazyBST T ;

  T.insert(70) ;
  T.insert(30) ;
  T.insert(110) ;
  T.insert(40) ;
  T.insert(20) ;
  T.insert(41) ;
  T.insert(31) ;
  T.insert(32) ;
  T.insert(33) ;
  T.insert(19) ;
  T.insert(34) ;
  T.insert(15) ;
  T.insert(14) ;

  T.inorder() ; cout << endl ;

  int key = 9999 ;
  bool ans ;
  const char *str ;

  ans = T.locate(str="", key=-1) ;
  cout << str << ": " << ans << " " << key << endl ;

  ans = T.locate(str="LL", key=-1) ;
  cout << str << ": " << ans << " " << key << endl ;

  ans = T.locate(str="LLR", key=-1) ;
  cout << str << ": " << ans << " " << key << endl ;

  ans = T.locate(str="RLLR", key=-1) ;
  cout << str << ": " << ans << " " << key << endl ;
}

//test7.cpp
const int depthLimit = 30 ;


// This function recursively checks if a LazyBST is correct, by checking:
//
//   1. keys are in order
//   2. left subtree is not more than twice the size of right subtree
//      or vice versa
//
// This function relies on locate() member function working correctly.
//
// Parameters:  
//   LazyBST& T  = tree to be checked, passed by reference
//   char pos[]  = must be pre-allocated with depthLimit chars
//   int& key    = stores key in node indicated by pos, if it exists
//   int& height = stores height of node indicated by pos, if it exists
//   int& size   = stores size of node indicated by pos, if it exists
//   bool report = give report for current node? defaults to true.
//
// Return value:
//    true if T has a node at pos
//    false if T does not have a node at pos
//
// Notes: 
// - if return value is false, parameters key, height and size are
//   not changed.
// - The pos string/array essentially acts as a stack for exploration
//   of the LazyBST. It remembers where we've been and is used to
//   determine where we have to check next.
//

bool sanityCheck(LazyBST& T, char pos[], int depth, int& key, int& height, int& size, bool report=true) {

  int leftKey, rightKey ;
  int leftHeight=-1, rightHeight=-1 ;
  int leftSize=0, rightSize=0 ;
  bool hasLeft, hasRight ;


  // Try to catch bad BST with cycles
  //
  if (depth >= depthLimit) {
    throw out_of_range("Depth limit reached. Something looks wrong!\n") ;
  }


  // Is does current position have a node?
  //
  if ( ! T.locate(pos, key) ) return false ;


  // Add extra '\0' so pos string can be extended
  //
  pos[depth+1] = '\0' ;


  // Recursively checks left subtree.
  //
  pos[depth] = 'L' ;
  hasLeft= sanityCheck(T, pos, depth+1, leftKey, leftHeight, leftSize, report) ;


  // Recursively checks right subtree.
  //
  pos[depth] = 'R' ;
  hasRight= sanityCheck(T, pos, depth+1, rightKey, rightHeight, rightSize, report) ;


  pos[depth] = '\0' ;  // restores pos[]


  // Compute current node's height and size
  //
  height = 1 + ( (leftHeight > rightHeight) ? leftHeight : rightHeight ) ; 
  size = 1 + leftSize + rightSize ;


  // Check key ordering for left child
  //
  if (hasLeft && leftKey >= key) {
    cerr << "\nIn position " << pos 
	 << " (key=" << key << ",height=" << height << ",size=" << size << ")"
	 << " left child's key not less than current node's key:"
         << leftKey << " " << key << endl ;
  }


  // Check key ordering for right child
  //
  if (hasRight && rightKey <= key) {
    cerr << "\nIn position " << pos 
	 << " (key=" << key << ",height=" << height << ",size=" << size << ")"
	 << " right child's key not greater than current node's key:"
         << rightKey << " " << key << endl ;
  }


  // Check relative sizes of left and right subtrees.
  // Note: leftSize == 2* rightSize (or vice versa) is not an error
  //    because it is up to the next insert or remove to fix.
  //
  if (height > 3) {
    if (leftSize > 2 * rightSize) {
      cerr << "\nIn position " << pos 
	   << " (key=" << key << ",height=" << height << ",size=" << size << ")"
	   << " left subtree too big: "
	   << leftSize << " " << rightSize << endl ;
    }
    if (rightSize > 2 * leftSize) {
      cerr << "\nIn position " << pos 
	   << " (key=" << key << ",height=" << height << ",size=" << size << ")"
	   << " right subtree too big: "
	   << leftSize << " " << rightSize << endl ;
    }

  }


  // Give stats for current node, if so desired.
  //

  if (report) {
    cout << "\n Node report on position " << pos << " :" << endl ;
    cout << "   key = " << key 
         << "   height = " << height 
         << "   size = " << size 
         << endl ;

    if (hasLeft) {
      cout << "   left child key = " << leftKey << endl ;
    } else {
      cout << "   no left child\n" ;
    }

    if (hasRight) {
      cout << "   right child key = " << rightKey << endl ;
    } else {
      cout << "   no right child\n" ;
    }
  }

  return true ;

}

void test7(){
  LazyBST T ;

  // add a bunch of numbers
  //
  T.insert(70) ;
  T.insert(30) ;
  T.insert(110) ;
  T.insert(40) ;
  T.insert(20) ;
  T.insert(41) ;
  T.insert(31) ;
  T.insert(32) ;
  T.insert(33) ;
  T.insert(19) ;
  T.insert(34) ;
  T.insert(15) ;
  T.insert(14) ;
  T.insert(38) ;
  T.insert(81) ;
  T.insert(95) ;
  T.insert(43) ;
  T.insert(17) ;

  T.inorder() ; cout << endl ;

  char pos[depthLimit] ;
  pos[0] = '\0' ;
  int key, height, size ;

  // Do check
  //
  cout << "First a small test...\n" ;
  sanityCheck(T,pos,0,key,height,size) ;
  cout << "\n\nSmall tree has root with key=" << key
       << ", height=" << height 
       << ", size=" << size 
       << endl; 

  cout << endl << endl ;
  cout << "Now a big test...\n" ;

  LazyBST T2 ;

  cout << "pre" << endl;
  for (int i=1000 ; i<1500 ; i++) {
    T2.insert(i) ;
  }
  cout << "first part" << endl;
  for (int i=250 ; i<900 ; i++) {
    T2.insert(i) ;
  }
  for (int i=3000 ; i>1600 ; i--) {
    T2.insert(i) ;
  }
  for (int i=3500 ; i<6000 ; i++) {
    T2.insert(i) ;
  }

  sanityCheck(T2,pos,0,key,height,size,false) ;
  cout << "\n\nBig tree has root with key=" << key
       << ", height=" << height 
       << ", size=" << size 
       << endl; 

  cout << endl << endl ;

}

//Insertion test
void test8(){

  cout <<"Testing insertion" << endl;
  
  LazyBST T;
  T.inorder();
  T.insert(5);
  T.inorder();
  
  //Insert to right
  T.insert(7);
  T.inorder();
  //Insert to left
  T.insert(3);
  T.inorder();
  //Insert to left of right children
  T.insert(6);
  T.inorder();
  //Insert to right of right
  T.insert(8);
  T.inorder();
  //Insert to right of left
  T.insert(4);
  T.inorder();
  //Insert to left of left
  T.insert(2);
  T.inorder();

}

//Testing remove
void test9(){

  LazyBST T;
  T.insert(5);
  T.insert(4);
  T.inorder();
  cout << "Remove from left" << endl;
  T.remove(4);
  T.inorder();
  T.insert(6);
  T.inorder();
  cout << "Remove from right" << endl;
  T.remove(6);
  T.inorder();
  T.insert(4);
  T.insert(3);
  T.inorder();
  cout << "Remove left with children to left" << endl;
  T.remove(4);
  T.inorder();
  T.remove(3);
  T.inorder();
  
  T.insert(6); T.insert(7);
  T.inorder();
  cout << "Remove from right with children to right" << endl;
  T.remove(6);
  T.inorder();
  T.remove(7);
  T.inorder();

  T.insert(3); T.insert(4); T.inorder();
  cout << "Remove from left with children to right" << endl;
  T.remove(3); T.inorder(); T.remove(4); T.inorder();

  T.insert(7); T.insert(6); T.inorder();
  cout << "Remove from right with children to left" << endl;
  T.remove(7); T.inorder(); T.remove(6); T.inorder();

  T.insert(3); T.insert(4); T.insert(2); T.inorder();
  cout << "Remove from left with both children" << endl;
  T.remove(3); T.inorder(); T.remove(4); T.inorder(); T.remove(2); T.inorder();


  T.insert(7); T.insert(6); T.insert(8); T.inorder();
  cout << "Remove from right with both children" << endl;
  T.remove(7); T.inorder(); T.remove(6); T.inorder(); T.remove(8); T.inorder();
  
  cout << "Remove root" << endl;
  T.remove(5); T.inorder();
  
  T.insert(5); T.inorder();
  T.insert(4); T.inorder();
  cout << "remove root with child to left" << endl;
  T.remove(5); T.inorder();
  
  T.insert(5); T.inorder();
  cout << "Remove root with child to right" << endl;
  T.remove(4); T.inorder();
  
  T.insert(4); T.insert(6); T.inorder();
  cout << "Remove root with both children" << endl;
  T.remove(5); T.inorder();
}
//Main driver
int main(){

  int userInput;
  do{
    cout << "Menu for driver program for LazyBST" <<endl
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
