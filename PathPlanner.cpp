
#include "PathPlanner.h"
#include <iostream>


PathPlanner::PathPlanner(Env env, int rows, int cols){
    
    for (int row = 0; row < rows ; ++row) {
        for (int col = 0 ; col < cols ; ++col) {
            new_env[row][col] = env[row][col];
        }
    }  

    this->O_List = new NodeList();
    this->C_List = new NodeList();
    this->ReachableNodes = new NodeList();
    this->FinalPath = new NodeList();

    this->rows = rows;
    this->cols = cols;
    this->initialPos = new Node(0, 0, 0);

}

PathPlanner::~PathPlanner(){
    
    delete C_List;
    delete O_List;
    delete ReachableNodes;
    delete FinalPath;
    delete initialPos;

}

void PathPlanner::initialPosition(int row, int col){
    
    for (int i = 0 ; i < ReachableNodes->getLength() ; ++i) {
        if (ReachableNodes->get(i)->getRow() == row && ReachableNodes->get(i)->getCol() == col) {
            initialPos = new Node(row, col, ReachableNodes->get(i)->getDistanceToS());
        }
    }

}

NodePtr PathPlanner::getGoalPosition(NodeList* nodes) {
    
    NodePtr node = new Node(0, 0 , 0);

    for (int row = 0 ; row < ENV_DIM ; ++row) {
        for (int col = 0 ; col < ENV_DIM ; ++col) {
            if (new_env[row][col] == SYMBOL_GOAL) {
                for (int i = 0 ; i < nodes->getLength() ; ++i) {
                    if (nodes->get(i)->getRow() == row && nodes->get(i)->getCol() == col) {
                        node = nodes->get(i);
                    }
                }
            }
        }
    }

    return node;
    
}

NodePtr PathPlanner::getStartPosition(NodeList* nodes) {
    
    NodePtr node = new Node(0, 0 , 0);

    for (int row = 0 ; row < ENV_DIM ; ++row) {
        for (int col = 0 ; col < ENV_DIM ; ++col) {
            if (new_env[row][col] == SYMBOL_START) {
                for (int i = 0 ; i < nodes->getLength() ; ++i) {
                    if (nodes->get(i)->getRow() == row && nodes->get(i)->getCol() == col) {
                        node = nodes->get(i);
                    }
                }
            }
        }
    }

    return node;
    
}

NodePtr PathPlanner::getStartPositionNoDtoS() {
    // This returns the start position from the environment without a node parameter.
    NodePtr node = new Node(0, 0, 0);

    for (int row = 0 ; row < ENV_DIM ; ++row) {
        for (int col = 0 ; col < ENV_DIM ; ++col) {
            if (new_env[row][col] == SYMBOL_START) {
                node = new Node(row, col, 0);
            }
        }
    }

    return node;
}

NodeList* PathPlanner::getReachableNodes(){

    O_List->addBack(PathPlanner::getStartPositionNoDtoS());

    NodePtr p = O_List->get(0);

    bool pFound = true;
    bool exit = false;

    int index = 0;

    NodePtr upNode = new Node(0, 0, 0);
    NodePtr rightNode = new Node(0, 0, 0);
    NodePtr downNode = new Node(0, 0, 0);
    NodePtr leftNode = new Node(0, 0, 0);

    while (pFound == true)  {

        upNode = new Node(p->getRow() - 1, p->getCol(), p->getDistanceToS() + 1);
        rightNode = new Node(p->getRow(), p->getCol() + 1, p->getDistanceToS() + 1);
        downNode = new Node(p->getRow() + 1, p->getCol(), p->getDistanceToS() + 1);
        leftNode = new Node(p->getRow(), p->getCol() - 1, p->getDistanceToS() + 1);
    
        if (new_env[p->getRow() - 1][p->getCol()] != SYMBOL_WALL && O_List->containsNode(upNode) == false) {                    
            O_List->addBack(upNode);
        }
        if (new_env[p->getRow()][p->getCol() + 1] != SYMBOL_WALL && O_List->containsNode(rightNode) == false) {                    
            O_List->addBack(rightNode);
        }     
        if (new_env[p->getRow() + 1][p->getCol()] != SYMBOL_WALL && O_List->containsNode(downNode) == false) {                   
            O_List->addBack(downNode);
        }
        if (new_env[p->getRow()][p->getCol() - 1] != SYMBOL_WALL && O_List->containsNode(leftNode) == false) {         
            O_List->addBack(leftNode);
        }
        
        C_List->addBack(p);
        
        
        // for loop version of the loop below
        /*
        for (int i = 0 ; i < O_List->getLength() ; ++i) {
            if (C_List->containsNode(O_List->get(i)) == false) {
                p = O_List->get(i);
                break;
            }
            if (C_List->containsNode(O_List->get(i)) == true && i == O_List->getLength() - 1) {
                pFound = false;
            }
        } */
        
        while ((index < O_List->getLength()) && (exit == false)) {
            if (C_List->containsNode(O_List->get(index)) == false) {
                p = O_List->get(index);
                //std::cout << "EXITED WHILE LOOP with index " << index << " and O length " << O_List->getLength() << std::endl;
                exit = true;
            }
            else {
                ++index;
            }

            if (C_List->containsNode(O_List->get(index)) == true && index == O_List->getLength() - 1) {
                
                pFound = false;
                exit = true;
            }
        }
        index = 0;
        exit = false; 
        
    }
    /*
    for (int i = 0 ; i < O_List->getLength() ; ++i) {
        std::cout << "(" << O_List->get(i)->getRow() << ", " << O_List->get(i)->getCol() << ", " << O_List->get(i)->getDistanceToS() << ")\n";
    } */

    
    ReachableNodes = new NodeList(*C_List);


    delete p;
    delete upNode;
    delete rightNode;
    delete downNode;
    delete leftNode;

    return ReachableNodes;

}

NodeList* PathPlanner::getPath(){
    // get reachable nodes must be ran before get path
    // the nodelist returned must be from start pos to goal
  
    NodeList* path = new NodeList();
    NodeList* pathInOrder = new NodeList();

    
    NodePtr CurrentNode = PathPlanner::getGoalPosition(ReachableNodes);
    initialPosition(CurrentNode->getRow(), CurrentNode->getCol());
    NodePtr StartNode = PathPlanner::getStartPosition(ReachableNodes);
    
    path->addBack(CurrentNode);
    bool foundStart = false;
    
    NodePtr upNode = new Node(0, 0 ,0);
    NodePtr rightNode = new Node(0, 0, 0);
    NodePtr downNode = new Node(0, 0, 0);
    NodePtr leftNode = new Node(0, 0, 0); 
    
    while (foundStart == false) {
        upNode = new Node(CurrentNode->getRow() - 1, CurrentNode->getCol(), 0);
        rightNode = new Node(CurrentNode->getRow(), CurrentNode->getCol() + 1, 0);
        downNode = new Node(CurrentNode->getRow() + 1, CurrentNode->getCol(), 0);
        leftNode = new Node(CurrentNode->getRow(), CurrentNode->getCol() - 1, 0);

        if (ReachableNodes->containsNode(upNode) == true && path->containsNode(upNode) == false && ReachableNodes->returnNode(CurrentNode->getRow() - 1, CurrentNode->getCol())->getDistanceToS() == CurrentNode->getDistanceToS() - 1 ) {
            // Search up
            //std::cout << "Searched Up" <<std::endl;
            CurrentNode = new Node(CurrentNode->getRow() - 1, CurrentNode->getCol(), CurrentNode->getDistanceToS() - 1);
            path->addBack(CurrentNode);
            
        }
        else if (ReachableNodes->containsNode(rightNode) == true && path->containsNode(rightNode) == false && ReachableNodes->returnNode(CurrentNode->getRow(), CurrentNode->getCol() + 1)->getDistanceToS() == CurrentNode->getDistanceToS() - 1) {
            // Search right
            //std::cout << "Searched Right" << std::endl;
            CurrentNode = new Node(CurrentNode->getRow(), CurrentNode->getCol() + 1, CurrentNode->getDistanceToS() - 1);
            path->addBack(CurrentNode);
        }
        else if (ReachableNodes->containsNode(downNode) == true && path->containsNode(downNode) == false && ReachableNodes->returnNode(CurrentNode->getRow() + 1, CurrentNode->getCol())->getDistanceToS() == CurrentNode->getDistanceToS() - 1) {
            // Search down
            //std::cout << "Searched Down" << std::endl; 
            CurrentNode = new Node(CurrentNode->getRow() + 1, CurrentNode->getCol(), CurrentNode->getDistanceToS() - 1);
            path->addBack(CurrentNode);
        }
        else if (ReachableNodes->containsNode(leftNode) == true && path->containsNode(leftNode) == false && ReachableNodes->returnNode(CurrentNode->getRow(), CurrentNode->getCol() - 1)->getDistanceToS() == CurrentNode->getDistanceToS() - 1) {
            // Search left
            //std::cout << "Searched Left" << std::endl;
            CurrentNode = new Node(CurrentNode->getRow(), CurrentNode->getCol() - 1, CurrentNode->getDistanceToS() - 1);
            path->addBack(CurrentNode);
        }

        if (CurrentNode->getRow() == StartNode->getRow() && CurrentNode->getCol() == StartNode->getCol()) {
            foundStart = true;
            
        } 

        //std::cout << CurrentNode->getRow() << ", " << CurrentNode->getCol() << ", " << CurrentNode->getDistanceToS() << std::endl;
    } 

    for (int i = path->getLength() - 1 ; i >= 0 ; --i) {
        pathInOrder->addBack(path->get(i));
    }
        
    FinalPath = new NodeList(*pathInOrder);
    
    delete StartNode;
    delete CurrentNode;
    delete upNode;
    delete rightNode;
    delete downNode;
    delete leftNode;

    return FinalPath;

}
