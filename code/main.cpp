/*
For milestone 2 identifying reachable positions, the algorithm I used was the pseudocode that was provided in the assignment pdf. 
The algorithm returns a deep copy of the closed list.

For milestone 3 I used a while loop. 
In the loop the current node will initially be the goal node and it will search in the reachable positions node list for any nodes above,
to the right, below and to the left of the current node that have a distance to start value less than the current node’s distance to start. 
If that node is found it is added to a path node list and it will be the next current node. 
This loop will keep on back tracking until the start node is found. A deep copy of of the reversed path node list will be returned.

An issue I have is that after running the code an error appears saying that the pointer being freed was not allocated,
this happens because at the end of the main file it deletes the nodelists that were already deleted in the pathplanners'
class deconstructor.

*/

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathPlanner.h"

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
void readEnvStdin(Env env);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printPath(Env env, NodeList* solution);

void printReachablePositions(Env env, NodeList* reachablePositions);


int main(int argc, char** argv){
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    // std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    // testNode();
    // testNodeList();
    // std::cout << "DONE TESTING" << std::endl << std::endl;

    // Load Environment 
    Env env;
    readEnvStdin(env);
    
    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    PathPlanner* pathplanner = new PathPlanner(env, ENV_DIM, ENV_DIM);
    
    NodeList* reachablePositions = nullptr;

    reachablePositions = pathplanner->getReachableNodes();
   
    //printReachablePositions(env, reachablePositions);

    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList* solution = pathplanner->getPath();
    
    //print the path
    printPath(env, solution);
    
    
    delete pathplanner;
    delete reachablePositions;
    delete solution;

}

void readEnvStdin(Env env){ 

    for (int row = 0; row < ENV_DIM; ++row) {
        for (int col = 0; col < ENV_DIM; ++col) {
            std::cin >> env[row][col];
        }
    }

}

void printPath(Env env, NodeList* solution) {
    /*
    NodePtr currentNode = solution->get(1);

    for (int i = 0 ; i < solution->getLength() - 1; ++i) {
        if (solution->get(i)->getRow() == currentNode->getRow() - 1 && solution->get(i)->getCol() == currentNode->getCol()) {
            env[solution->get(i)->getRow()][solution->get(i)->getCol()] = '^';
            currentNode = solution->get(i);
        }
        else if (solution->get(i)->getRow() == currentNode->getRow() && solution->get(i)->getCol() == currentNode->getCol() + 1) {
            env[solution->get(i)->getRow()][solution->get(i)->getCol()] = '>';
            currentNode = solution->get(i);
        }
        else if (solution->get(i)->getRow() == currentNode->getRow() + 1 && solution->get(i)->getCol() == currentNode->getCol()) {
            env[solution->get(i)->getRow()][solution->get(i)->getCol()] = 'v';
            currentNode = solution->get(i);
        }
        else if (solution->get(i)->getRow() == currentNode->getRow() && solution->get(i)->getCol() == currentNode->getCol() - 1) {
            env[solution->get(i)->getRow()][solution->get(i)->getCol()] = '<';
            currentNode = solution->get(i);
        } 
        if (currentNode->getRow() == solution->get(solution->getLength() - 1)->getRow() && currentNode->getCol() == solution->get(solution->getLength() -1)->getCol()) {
            env[currentNode->getRow()][currentNode->getCol()] = SYMBOL_GOAL;
        } */
        //env[solution->get(i)->getRow()][solution->get(i)->getCol()] = 'S';

    Env env3;

    for (int row = 0 ; row < ENV_DIM ; ++row) {
        for (int col = 0 ; col < ENV_DIM ; ++col) {
            env3[row][col] = env[row][col];
        }
    }
    
    if (solution->getLength() > 0) {
        for (int i = 0 ; i < solution->getLength() - 1; ++i) {
            if (solution->get(i)->getRow() == solution->get(i + 1)->getRow() - 1 && solution->get(i)->getCol() == solution->get(i + 1)->getCol() ) {
                env3[solution->get(i)->getRow()][solution->get(i)->getCol()] = 'v';
            }
            else if (solution->get(i)->getRow() == solution->get(i + 1)->getRow() && solution->get(i)->getCol() == solution->get(i + 1)->getCol() + 1) {
                env3[solution->get(i)->getRow()][solution->get(i)->getCol()] = '<';

            }
            else if (solution->get(i)->getRow() == solution->get(i + 1)->getRow() + 1 && solution->get(i)->getCol() == solution->get(i + 1)->getCol()) {
                env3[solution->get(i)->getRow()][solution->get(i)->getCol()] = '^';

            }
            else if (solution->get(i)->getRow() == solution->get(i + 1)->getRow() && solution->get(i)->getCol() == solution->get(i + 1)->getCol() - 1) {
                env3[solution->get(i)->getRow()][solution->get(i)->getCol()] = '>';
    
            } 
        }

        env3[solution->get(0)->getRow()][solution->get(0)->getCol()] = SYMBOL_START;
    }

    
    for (int row = 0; row < ENV_DIM; ++row) {
        for (int col = 0; col < ENV_DIM; ++col) {
            std::cout << env3[row][col];
  
        }
        std::cout << "\n";
    }

}

void printReachablePositions(Env env, NodeList* reachablePositions){
    
    Env env2;

    for (int row = 0 ; row < ENV_DIM ; ++row) {
        for (int col = 0 ; col < ENV_DIM ; ++col) {
            env2[row][col] = env[row][col];
        }
    }

    std::cout << "Reachable Nodes" << std::endl;
    for (int i = 0; i < reachablePositions->getLength(); ++i) {
        std::cout << reachablePositions->get(i)->getRow() << ", " << reachablePositions->get(i)->getCol() << ", " << reachablePositions->get(i)->getDistanceToS() << std::endl;
        env2[reachablePositions->get(i)->getRow()][reachablePositions->get(i)->getCol()] = '*';
    }

    for (int row = 0; row < ENV_DIM ; ++row) {
        for (int col = 0; col < ENV_DIM ; ++col) {
            std::cout << env2[row][col];
        }
        std::cout << "\n";
    }
}

void testNode() {
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node* node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceToS() << std::endl;
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceToS() << std::endl;
    delete node;
}

void testNodeList() {
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList* nodeList = new NodeList();
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node* b1 = new Node(1, 1, 1);
    nodeList->addBack(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add second Nodetest
    Node* b2 = new Node(0, 0, 1);
    nodeList->addBack(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Test Get-ith - should be 0,0,1
    Node* getB = nodeList->get(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceToS() << std::endl;

    // Print out the NodeList
    std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;
}