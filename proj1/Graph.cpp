/*********************
File name: Graph.cpp
Student name: Seung Hun Lee
Project 1 CMSC 341 Spring 2017

Holds most of the stuff for project 1
which is mostly about creating a graph of
linked list and iterators to step through
said graph and linked lists
*************************/


#include "Graph.h"
#include <iostream>

using namespace std;

//Basic constructor using an int as parameter
Graph::Graph(int n){
  if(n <1)
    throw out_of_range("Invalid size");
  m_size = n;
  m_adjLists = new AdjListNode * [n];
  //Initializing the pointers just to be sure
  for(int i = 0; i < m_size; i++){
    m_adjLists[i] = NULL;
  }
}

//Returns size of this graph
int Graph::size(){
  return m_size;
}

//Copy Constructor of graph.
Graph::Graph(const Graph& G){
  
  m_size = G.m_size;
  m_adjLists = new AdjListNode * [m_size];
  //Copying in the data
  for(int i = 0; i < m_size; i++){
    //Fill with NULL if original is NULl
    if(G.m_adjLists[i] == NULL){
      m_adjLists[i] = NULL;
    }
    else{
      AdjListNode * origNode = G.m_adjLists[i];
      m_adjLists[i] = new AdjListNode(origNode->m_vertex);
      AdjListNode * copyNode = m_adjLists[i];
      origNode = origNode->next;
      //Step through the original node and fill in the copy
      while( origNode !=NULL){
	copyNode->next = new AdjListNode(origNode->m_vertex);
	copyNode = copyNode->next;
	origNode = origNode->next;
      }
    }
  }
}

//Destructor for the graph
Graph::~Graph(){
  for(int i = 0; i < m_size; i++){
    AdjListNode * currentNode = m_adjLists[i];
    AdjListNode * nextNode;
    while( currentNode != NULL){
      nextNode = currentNode->next;
      currentNode->next = NULL;
      delete currentNode;
      currentNode = nextNode;
    }
    m_adjLists[i] = NULL;
  }
  delete [] m_adjLists;
}

//assignment operator on two graphs. Nearly identical to copy constructor except when marked
const Graph& Graph::operator=(const Graph& rhs){
  //Check for self assignment
  if(&rhs == this){
    return *this;
  }
  
  for(int i = 0; i < m_size; i++){
    AdjListNode * currentNode = m_adjLists[i];
    AdjListNode * nextNode;
    while( currentNode != NULL){
      nextNode = currentNode->next;
      currentNode->next = NULL;
      delete currentNode;
      currentNode = nextNode;
    }
    m_adjLists[i] = NULL;
  }
  delete [] m_adjLists;

  
  m_size = rhs.m_size;
  m_adjLists = new AdjListNode * [m_size];
  for(int i = 0; i < m_size; i++){
    if(rhs.m_adjLists[i] == NULL){
      m_adjLists[i] = NULL;
    }
    else{
      AdjListNode * origNode = rhs.m_adjLists[i];
      m_adjLists[i] = new AdjListNode(origNode->m_vertex);
      AdjListNode * copyNode = m_adjLists[i];
      origNode = origNode->next;
      while( origNode !=NULL){
        copyNode->next = new AdjListNode(origNode->m_vertex);
        copyNode = copyNode->next;
        origNode = origNode->next;
      }
    }
  }
  //Return the lvalue of the assignment
  return *this;
}

//Adds an edge between vertices u and v
void Graph::addEdge(int u, int v){
  //Throw an out of bounds error if invalid u and v
  if(u >= m_size || u < 0)
    throw out_of_range("1st Parameter out of range");
  
  if(v >= m_size || v < 0)
    throw out_of_range("2nd Parameter out of range");
  
  //Add new nodes as edges to both vertices
  AdjListNode *newEdge1 = new AdjListNode( v, m_adjLists[u]);
  m_adjLists[u] = newEdge1;
  AdjListNode *newEdge2 = new AdjListNode( u, m_adjLists[v]);
  m_adjLists[v] = newEdge2;
}

//Dumps the data structure out.
void Graph::dump(){
  cout << "Dump out graph (size = " << m_size << "):" << endl;
  for(int i = 0; i < m_size; i++){
    AdjListNode * currentNode = m_adjLists[i];
    cout << "[ " << i << "]:" ;
    while(currentNode != NULL){
      cout << " " << currentNode->m_vertex;
      currentNode = currentNode->next;
    }
    cout << endl;
  }
  cout << "end" << endl;
}


//Creates an EgIterator. Can start at beginning or end
Graph::EgIterator::EgIterator(Graph *Gptr, bool isEnd){
  m_Gptr = Gptr;
  //When it is for the end
  if(isEnd){
    m_source = m_Gptr->size() -1;
    m_where = NULL;
  }
  //For not the end
  else{
    m_source = 0;
    if(Gptr != NULL)
      m_where = m_Gptr->m_adjLists[0];
    //Move to next available edge
    while(m_where == NULL &&m_source < m_Gptr->size()-1){
      m_source++;
      m_where = m_Gptr->m_adjLists[m_source];
    }
  }
}

//Checks if two EgIterator are the not the same
bool Graph::EgIterator::operator!=(const EgIterator& rhs){
  return (m_Gptr != rhs.m_Gptr || m_source != rhs.m_source ||
	  m_where != rhs.m_where);
}

//Increment operator for edgeiterator
void Graph::EgIterator::operator++(int dummy){
  bool edgeFound = false;
  while(!edgeFound){
    if(m_where == NULL){
      //Last row of list, last element
      if(m_source == m_Gptr->m_size -1){
	return;
      }
      //Last element. Move on to next row
      else{
	m_source++;
	m_where = m_Gptr->m_adjLists[m_source];
	//Check if the edge has been mentioned before. Edge should have been
	//mentioned already if m_source > neighbor vertex
	if (m_where != NULL && m_source <= m_where->m_vertex)
	  edgeFound = true;
      }
    }
    //Not the last element. Check next element in row
    else{
      m_where = m_where->next;
      //Edge not repeated if m_source is less than or equal to vertex
      if(m_where!= NULL)
	if( m_source <= m_where->m_vertex)
	  edgeFound = true;
    }
  }
  return;
}

//Dereference operator of EgIterator
std::pair<int,int> Graph::EgIterator::operator*(){
  //Throws error if Iterator is at end
  if(m_where == NULL)
    throw out_of_range("Iterator oor");
  std::pair<int,int> edge = std::make_pair (m_source, m_where->m_vertex);
  return edge;
}

//Create beginning EgIterator
Graph::EgIterator Graph::egBegin(){
  EgIterator begin(this);
  return begin;
}

//Create end EgIterator
Graph::EgIterator Graph::egEnd(){
  EgIterator end(this, true);
  return end;
}

//Constructor for NbIterator
Graph::NbIterator::NbIterator(Graph *Gptr, int v, bool isEnd){
  m_Gptr = Gptr;
  m_source = v;
  //For end NbIterator
  if(isEnd)
    m_where = NULL;
  //For not end NbIterator
  else{
    if(Gptr != NULL)
      m_where = m_Gptr->m_adjLists[v];
  }
}

//Checks if left iterator is not same as the right hand
bool Graph::NbIterator::operator!=(const NbIterator & rhs){
  return (m_Gptr != rhs.m_Gptr || m_source != rhs.m_source || 
	  m_where != rhs.m_where);
}

//Stepss through neighbors once. Not if it's already at end
void Graph::NbIterator::operator++(int dummy){
  if(m_where == NULL)
    return;
  else
    m_where = m_where->next;
}

//Dereference NbIterator
int Graph::NbIterator::operator*(){
  //Error if it is already at end
  if(m_where == NULL)
    throw out_of_range("Iterator oor");
  return m_where->m_vertex;
}

//Create an NbIterator at beginning
Graph::NbIterator Graph::nbBegin(int v){
  NbIterator begin(this, v);
  return begin;
}

//Create an NbIterator at end
Graph::NbIterator Graph::nbEnd(int v){
  NbIterator end(this, v, true);
  return end;
}

//AdjListNode constructor
Graph::AdjListNode::AdjListNode(int v, AdjListNode *ptr){
  m_vertex = v;
  next = ptr;
}

