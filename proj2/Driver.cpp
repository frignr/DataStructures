// File: Driver.cpp
//
// CMSC 341 Spring 2017 Project 2
//
// Simple driver program to call the Sally Forth interpreter
// This version will take test.sally as input.
// 
//


#include <iostream>
#include <fstream>
using namespace std ;

#include "Sally.h"

int main() {
  string fname = "test.sally";

  ifstream ifile(fname.c_str()) ;

  Sally S(ifile) ;

  S.mainLoop() ;

  ifile.close() ;
  return 0 ;
}
