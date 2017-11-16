/*********************
File name: Driver.cpp
Student name: Seung Hun Lee
Project 1 CMSC 341 Spring 2017

Driver for the Graph class part of project 1.
Goes through all the functions of Graph and 
different cases of usage, including cases of 
not ordinary inputs. Some of the code has been 
copied from the provided tests but a lot of code
has been added in addition to test for all the 
cases.
*************************/

#include <iostream>
#include <utility>
using namespace std ;

#include "Graph.h"

int main() {

  //
  
   // G has 5 vertices numbered 0 thru 4
  Graph G(5) ;
   
   //Dump out initial structure
  G.dump();

   //Check size function
  cout << "Size of the graph is " << G.size() << endl;

  //Test small graph
  Graph small(1);
  small.dump();

  //Test invalid size
  try{
    Graph wrong(-3);
  }catch(out_of_range e){
    cerr << "out of range" << endl;
  }

  //Check out of range error on edges
  try{
     G.addEdge(-1, 2);
  } catch(out_of_range e){
    cerr << "Out of range" << endl;
  }
  try{
    G.addEdge(1, -2);
  } catch(out_of_range e){
    cerr << "Out of range" << endl;
  }
  try{
    G.addEdge(5, 2);
  } catch(out_of_range e){
    cerr << "Out of range" << endl;
  }
  try{
    G.addEdge(1, 5);
  } catch(out_of_range e){
    cerr << "Out of range" << endl;
  }
  
  
  // add some edges
  G.addEdge(3,4) ;
  G.addEdge(1,4) ;
  G.addEdge(0,3) ;
  G.addEdge(0,4) ;
  G.addEdge(0,1) ;
  G.addEdge(1,2) ;
  G.addEdge(2,4) ;
  G.addEdge(4,4) ;
  
  // dump out data structure
  G.dump() ;
  
  // Test neighbor iterator
  //
  Graph::NbIterator nit ;
  
  cout << "\nThe neighbors of vertex 4 are:\n" ;
  for (nit = G.nbBegin(4); nit != G.nbEnd(4) ; nit++) {
    cout << *nit << " " ;
  }
  cout << endl ;
  
  //Check dereference function on end NbIterator
   try{
     cout << *nit << endl;
   }
   catch(out_of_range e){
     cerr << "Can't dereference end NbIterator" << endl;
   }
   
   
   // Test edge iterator
   //
   Graph::EgIterator eit ;
   pair<int,int> edge ;
   
   cout << "\nThe edges in the graph are:\n" ;
   for (eit = G.egBegin() ; eit != G.egEnd() ; eit++) {
     
     edge = *eit ;   // get current edge

     // the two data members of a pair are first and second
     //
     cout << "(" << edge.first << ", " << edge.second << ") " ;
     
   }
   cout << endl ;
   
   //Test edge iterator of empty Graph
   Graph G2(5);
   cout << "\nThe edges in the graph are:\n" ;
   for (eit = G2.egBegin() ; eit != G2.egEnd() ; eit++) {

     edge = *eit ;   // get current edge

     // the two data members of a pair are first and second
     //
     cout << "(" << edge.first << ", " << edge.second << ") " ;

   }
   cout << endl ;

   //Test neighbor iterator of empty graph
   cout << "\nThe neighbors of vertex 4 are:\n" ;
   for (nit = G2.nbBegin(4); nit != G2.nbEnd(4) ; nit++) {
     cout << *nit << " " ;
   }
   cout << endl ;

   //Test edge iterator of semi-empty Graph
   G2.addEdge(2,3);
   G2.dump();
   cout << "\nThe edges in the graph are:\n" ;
   for (eit = G2.egBegin() ; eit != G2.egEnd() ; eit++) {

     edge = *eit ;   // get current edge

     // the two data members of a pair are first and second
     //
     cout << "(" << edge.first << ", " << edge.second << ") " ;

   }
   cout << endl ;


   //Check dereference function on end EgIterator
   try{
     edge = *eit;
   }
   catch(out_of_range e){
     cerr << "Can't dereference end EgIterator" << endl;
   }
   
   Graph * Gptr = &G;
   
   // make a copy using copy constructor
   Graph* Gptr2 = new Graph(*Gptr) ;
   Gptr2->dump() ;
   
   // get rid off original graph
   // check if new graph is still there
   Gptr2->dump() ;

   // Make another graph and dump
   Graph G3(3) ;
   G3.addEdge(0,1) ;
   G3.addEdge(0,2) ;
   G3.addEdge(1,2) ;
   G3.dump() ;

   //Check copying bigger graph onto smaller graph
   Graph* Gptr3 = new Graph(*Gptr2);
   *Gptr3 = G3;
   Gptr3->dump();
   delete Gptr3;

   //Check Self-assignment
   G3 = G3;
   G3.dump();
   
   // Copy over G3 and dump
   G3 = *Gptr2 ;
   G3.dump() ;

   delete Gptr2 ; 
}
