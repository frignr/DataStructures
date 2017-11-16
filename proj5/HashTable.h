// File: HashTable.h
//
// CMSC 341 Sprint 2017 Project 5
// Seung Hun Lee
// Declarations for HashTable
//

#ifndef HASHTABLE_H
#define HASHTABLE_H


#include <stdexcept>
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

unsigned int hashCode(const char *str);

class HashTable{

  
  char ** table0; // holds first hash table
  int currentSize0; // hold number on items in table0
  int capacity0; // holds capacity of table0

  //Will hold second table if rehashing
  char ** table1; // holds second hash table
  int currentSize1; // hold number on items in table1
  int capacity1; // holds capacity of table1

  //Third table used in case table1 is not enough
  char ** table2; // holds third hash table
  int currentSize2; // hold number on items in table2
  int capacity2; // holds capacity of table2

  int rehashing;//Stores whether table is rehashing
  //0 = no 1 = yes 2 = third table needed finish rehashing

  static char * const DELETED;

 public:
  HashTable(int n = 101);
  ~HashTable();
  HashTable(HashTable& other);

  const HashTable& operator= (HashTable& rhs);

  void insert(const char * str);//Insert with rehash capability
  //void insertOnly(const char * str);//Insert with no rehash capability
  void insertToOne(const char * str);//Insert to table1
  void insertToTwo(const char * str);//Insert to table2
  bool find(const char * str);
  char * remove(const char *str);

  void rehash();
  void rehashCluster(unsigned int index);

  //Testing functions
  bool isRehashing();
  int tableSize(int table=0);
  int size(int table=0);
  const char * at(int index, int table=0);
  void dump();
};


#endif
