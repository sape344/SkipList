#include <cstdlib>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <random>
#include <bits/stdc++.h>
#include <limits>
  
struct node
{

    int data;  // value of node
    node(int data, int level); // initiliaze  constructor function 
    ~node(); // delete  ** towar from  heap
    inline node* Forward(int i ){ // pointer for tower[i]
        return towar[i]; 
    }

    inline void Assign(int i, node* value){ //assing value to tower[i]
        towar[i]=value; 
    }
    private:
    node **towar; //keeps all node* pointers   inside


};
 
  
class skiplist
{
    int size=0; // size keep total number of node
    int maxLevel; // it limit level of skip list 
    float fractation;  
    int curLevel;  // show current maximun level
    node *header; // Holds the starting pointer of all notes. 
public:
    skiplist(int maxLevel, float fraction); //constructer
    inline int randLevel(); //decide level every new node. 
    bool Insert(int); // Insert new node
    bool Delete(int); // Delete a node
    bool Search(int); // Search a node
    void Print(); // Print all nodes
    ~skiplist(); // 
    
};