
#include "NodeList.h"
#include <iostream>



NodeList::NodeList(){

    this->length = 0;

}


NodeList::~NodeList(){

    clear();

}

NodeList::NodeList(NodeList& other){

    // this is a the address value of another node from a another node list

    this->length = *new int (other.length);

    for (int i = 0; i < length ; ++i) {
        nodes[i] = new Node(*other.nodes[i]);
    }

}


int NodeList::getLength(){
   return length; 
}


NodePtr NodeList::get(int i){
   return nodes[i];
}

void NodeList::addBack(NodePtr newNode){
    nodes[length] = newNode; // Sets current node at current length index to new node
    ++length;

}

bool NodeList::containsNode(NodePtr node){
    // loop through nodelist and if the row and column of that node matches a node in the nodelist return true
    bool condition = false;
    
    for (int i = 0; i < length ; ++i) {
        if (node->getRow() == nodes[i]->getRow() && node->getCol() == nodes[i]->getCol()) {
  
            condition = true;
        }
    }

    return condition;    

}

NodePtr NodeList::returnNode(int row, int col) {
    // This is used to return the node given the integer of row and column
    NodePtr node = new Node(0, 0, 0);

    for (int i = 0 ; i < length ; ++i) {
        if (nodes[i]->getRow() == row && nodes[i]->getCol() == col) {
            node = nodes[i];
        }
    }

    return node;
}

void NodeList::clear(){
    for (int i = 0 ; i < length ; ++i) {
        delete nodes[i];
        
    }
}