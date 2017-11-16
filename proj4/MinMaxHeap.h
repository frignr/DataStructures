// File: MinMaxHeap.h
//
// CMSC 341 Sprint 2017 Project 4
// Seung Hun Lee
// Declaration and definition of template classes for
// Node, Heap and MinMaxHeap.
// Node builds up heap, heap build up MinMaxHeap.
//

#ifndef MINMAXHEAP_H
#define MINMAXHEAP_H

#include <stdexcept>
#include <iostream>
using namespace std;

//Declaring these classes so compiler knows these exist
template <typename T>
class Heap;
template <typename T>
class MinMaxHeap;

//Nodes that are going to make up the heaps
template <typename T>
class Node
{
  friend class Heap<T>;//Can be accessed by Heap
  friend class MinMaxHeap<T>;//Can be accessed by MinMaxHeap
 public:
  Node();//Basic constructor
  Node(T key);//Constructor with key input
  ~Node();//Destructor
  T getKey();//returns key. Here to make the comparators easier to implement

 private:
  T m_key;//Key stored in node

  int otherIndex;//Index of the twin
};

//Basic constructor. Does nothing
template <typename T>
Node<T>::Node()
{
}

//Constructor. takes a key.
template <typename T>
Node<T>::Node(T key)
{
  m_key = key;
}

//Destructor. Does not have to delete anything
template <typename T>
Node<T>::~Node()
{
}

//Returns stored key
template <typename T>
T Node<T>::getKey(){
  return m_key;
}

/***********************************
boolean operators using nodes
 *********************************/
template <typename T>
bool operator<(Node<T> left, Node<T> right){
  return left.getKey() < right.getKey();
}

template <typename T>
bool operator<=(Node<T> left, Node<T> right){
  return left.getKey() <= right.getKey();
}

template <typename T>
bool operator==(Node<T> left, Node<T> right){
  return left.getKey() == right.getKey();
}

template <typename T>
bool operator!=(Node<T> left, Node<T> right){
  return left.getKey() != right.getKey();
}

template <typename T>
bool operator>(Node<T> left, Node<T> right){
  return left.getKey() > right.getKey();
}

template <typename T>
bool operator>=(Node<T> left, Node<T> right){
  return left.getKey() >= right.getKey();
}
/********************************************/


//Heap class that will act as both min and max heap
template <typename T>
class Heap
{
  friend class MinMaxHeap<T>;//Can be accessed by MinMaxHeap
 public:
  //Constructor taking in capacity and the comparator
  Heap(int capacity, bool (*comparator)(Node<T>, Node<T>));

  //Copy constructor
  Heap(const Heap<T>& other);

  //Destructor
  ~Heap();

  //Inserts a key
  void insert(T key);

  //Dumps all the nodes in a nice to look at format
  void dump();

  //Deletes a node at index
  T deleteNode(int index);

  //Deletes min/max. Also deletes the twin node
  T deleteRoot();
 private:
  int currentSize;//stores current size of heap
  int maxSize;//Stores capacity of heap
  Node<T> * heapList ;//Where the heap itself is stored
  bool (*comp)(Node<T>, Node<T>);//Pointer to function that will determine how this heap acts
  Heap* otherHeap;//Pointer to the other heap.

  //Swaps node at left index with one at right index
  void swap(int leftIndex, int rightIndex);

  //Makes a node bubble up if needed
  void bubbleUp(int index);

  //Makes a node trickle down if needed
  void trickleDown(int index);
};

//Constructor. Creates a heapList, and sets default values
template <typename T>
Heap<T>::Heap(int capacity, bool (*comparator)(Node<T>, Node<T>)){
  heapList = new Node<T> [capacity + 1];
  comp = comparator;
  maxSize = capacity;
  currentSize = 0;
  otherHeap = NULL;
}

//Copy constructor
template <typename T>
Heap<T>::Heap(const Heap<T>& other){
  heapList = new Node<T> [other.maxSize + 1];
  comp = other.comp;
  maxSize = other.maxSize;
  //Copying the list of nodes
  for(int i = 1; i <= other.currentSize; i++){
    heapList[i].m_key = (other.heapList[i].m_key);
    heapList[i].otherIndex = other.heapList[i].otherIndex;
  }
  currentSize = other.currentSize;
}


//Destructor. Deletes the heapList 
template <typename T>
Heap<T>::~Heap(){
  delete [] heapList;
}

//Swaps node at left index with node at right index
template <typename T>
void Heap<T>::swap(int leftIndex, int rightIndex){

  //Switch the index of its twin
  T tempLeft = heapList[leftIndex].m_key;
  int tempLeftOther = heapList[leftIndex].otherIndex;
  int tempRightOther = heapList[rightIndex].otherIndex;

  //Single heap compatibility achieved with this if statement
  if(otherHeap != NULL){
    otherHeap->heapList[tempLeftOther].otherIndex = rightIndex;
    otherHeap->heapList[tempRightOther].otherIndex = leftIndex;
  }

  //Swap keys and index
  heapList[leftIndex].m_key = heapList[rightIndex].m_key;
  heapList[leftIndex].otherIndex = heapList[rightIndex].otherIndex;

  heapList[rightIndex].m_key = tempLeft;
  heapList[rightIndex].otherIndex = tempLeftOther;
}

//Makes the node at index bubbleup if needed
template <typename T>
void Heap<T>::bubbleUp(int index){
  if(index > 1 && comp(heapList[index], heapList[index/2])){
    swap(index, index/2);
    bubbleUp(index/2);
  }
}

//Makes the node at index trickle down if needed
template <typename T>
void Heap<T>::trickleDown(int index){
  int childIndex1 = index * 2;
  int childIndex2 = index * 2 + 1;
  //Make sure child indices are not oob
  if(childIndex2 <= currentSize){

    //Swap and continue trickle down with smaller node, if there is any
    if(comp(heapList[childIndex1], heapList[index]) ||
       comp(heapList[childIndex2], heapList[index])){
      if(comp(heapList[childIndex1], heapList[childIndex2])){
	swap(childIndex1, index);
	trickleDown(childIndex1);
      }
      else{
	swap(childIndex2, index);
	trickleDown(childIndex2);
      }
    }
  }
  //Case where only one children
  else if(childIndex1 <= currentSize){
    if(comp(heapList[childIndex1], heapList[index])){
      swap(childIndex1, index);
      trickleDown(childIndex1);
    }
  }
}

//Inserts a key into the node and its twin
template <typename T>
void Heap<T>::insert(T key){

  //This should get caught in MinMaxHeap ideally
  if (currentSize == maxSize)
    throw out_of_range("Heap capacity reached");

  currentSize++;
  Node<T> insertNode(key);
  heapList[currentSize] = insertNode;

  //Inserts node for other heap if present
  if(otherHeap != NULL){
    otherHeap-> currentSize = currentSize;
    Node<T> otherInsertNode(key);
    otherHeap->heapList[currentSize] = otherInsertNode;
    otherHeap->heapList[currentSize].otherIndex = currentSize;
    heapList[currentSize].otherIndex = currentSize;
    otherHeap->bubbleUp(currentSize);
  }
  bubbleUp(currentSize);
}

//Prints out all the heaps
template <typename T>
void Heap<T>::dump(){
  cout << "size = " << currentSize << ", capacity = " << maxSize << endl;
  for(int i = 1; i <= currentSize; i++){
    cout << "Heap [" << i << "] =  (" << heapList[i].m_key << ","
	 << heapList[i].otherIndex << ")" <<  endl;
  }
}

//Deletes a node at index
template <typename T>
T Heap<T>::deleteNode(int index){
  T deleted = heapList[index].m_key;
  currentSize--;
  if(index != currentSize + 1){
    swap(index, currentSize + 1);
    //Bubbleup or down if needed
    bubbleUp(index);
    trickleDown(index);
  }
  return deleted;
}

//Deletes root (min/max) and its twin as well
template <typename T>
T Heap<T>::deleteRoot(){
  if(currentSize == 0)
    throw out_of_range("No members to delete");

  //Delete the node in the twin heap first
  //If statement to allow individual heaps
  if(otherHeap != NULL)
    otherHeap->deleteNode(heapList[1].otherIndex);

  T deleted = heapList[1].m_key;
  currentSize--;
  if(currentSize+ 1 != 1){
    swap(1,currentSize + 1);
    trickleDown(1);
  }
  return deleted;
}

//MinMaxHeap class itself
template <typename T>
class MinMaxHeap {
 public:
  //Constructor taking capacity
  MinMaxHeap(int capacity);

  //Copy constructor
  MinMaxHeap(const MinMaxHeap<T>& other);
  
  //Destructor
  ~MinMaxHeap();

  //Assignment operator
  const MinMaxHeap<T>& operator=(const MinMaxHeap& rhs);

  //Returns size of heap
  int size();

  //Inserts data to the heaps
  void insert(const T& data);

  //Deletes min
  T deleteMin();

  //Deletes max
  T deleteMax();

  //Prints out all the heaps
  void dump();

  //Change data and index to data and otherIndex at pos of min
  void locateMin(int pos, T& data, int& index);

  //Change data and index to data and otherIndex at pos of max
  void locateMax(int pos, T& data, int& index);
 private:
  int m_capacity;//Stores capcity of heaps
  int m_size;//Stores size of heaps

  Heap<T>* minHeap;//Minimum heap
  Heap<T>* maxHeap;//Maximum heap
};

//Constructor taking in capacity
template <typename T>
MinMaxHeap<T>::MinMaxHeap(int capacity){
  m_capacity = capacity;
  m_size = 0;
  minHeap = new Heap<T>(m_capacity, operator<);
  maxHeap = new Heap<T>(m_capacity, operator>);

  //Link the two heaps
  minHeap->otherHeap = maxHeap;
  maxHeap->otherHeap = minHeap;
}

//Copy constructor
template <typename T>
MinMaxHeap<T>::MinMaxHeap(const MinMaxHeap<T>& other){
  m_capacity = other.m_capacity;
  m_size = other.m_size;
  
  minHeap = new Heap<T>(*other.minHeap);
  maxHeap = new Heap<T>(*other.maxHeap);

  //Link the two heaps
  minHeap->otherHeap = maxHeap;
  maxHeap->otherHeap = minHeap;
}

//Destructor
template <typename T>
MinMaxHeap<T>::~MinMaxHeap(){
  delete minHeap;
  delete maxHeap;
  minHeap = NULL;
  maxHeap = NULL;
}

//Assignment operator
template <typename T>
const MinMaxHeap<T>& MinMaxHeap<T>::operator=(const MinMaxHeap<T>& other){
  m_capacity = other.m_capacity;
  m_size = other.m_size;
  
  delete minHeap;
  delete maxHeap;

  minHeap = new Heap<T>(*other.minHeap);
  maxHeap = new Heap<T>(*other.maxHeap);

  //Link the two heaps
  minHeap->otherHeap = maxHeap;
  maxHeap->otherHeap = minHeap;
  return *this;
}

//Returns size
template <typename T>
int MinMaxHeap<T>::size(){
  return m_size;
}

//Insert a node
template <typename T>
void MinMaxHeap<T>::insert(const T& data){
  if (m_size == m_capacity)
    throw out_of_range("MinMaxHeap capacity reached");
  
  m_size++;
  minHeap->insert(data);
  //maxHeap->insert(data);
}

//Deletes minimum of heap
template <typename T>
T MinMaxHeap<T>::deleteMin(){
  T deleted = minHeap->deleteRoot();
  m_size --;
  return deleted;
}

//Deletes maximum of heap
template <typename T>
T MinMaxHeap<T>::deleteMax(){
  T deleted = maxHeap->deleteRoot();
  m_size --;
  return deleted;
}

//Prints out all the heaps
template <typename T>
void MinMaxHeap<T>::dump(){
  cout << "------------Min Heap------------" << endl;
  minHeap->dump();
  cout << "------------Max Heap------------" << endl;
  maxHeap->dump();
}

//Change data and index to data and otherIndex at pos of min
template <typename T>
void MinMaxHeap<T>::locateMin(int pos, T& data, int& index){
  data = minHeap->heapList[pos].m_key;
  index = minHeap->heapList[pos].otherIndex;
}

//Change data and index to data and otherIndex at pos of max
template <typename T>
void MinMaxHeap<T>::locateMax(int pos, T& data, int& index){
  data = maxHeap->heapList[pos].m_key;
  index = maxHeap->heapList[pos].otherIndex;
}
#endif // !MinMaxHeap
