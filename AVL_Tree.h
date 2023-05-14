//
// Created by MKassem360 on 5/10/2023.
//

#ifndef DATASTURCURES_HW1_AVL_TREE_H
#define DATASTURCURES_HW1_AVL_TREE_H
#include "Node.h"

class AVL_Tree {
    int numOfNodes;
    Node* root;
public:
    AVL_Tree():numOfNodes(0),root(nullptr){};
    ~AVL_Tree()=default;
    AVL_Tree(AVL_Tree& avlTree)=default;
    Node* getRoot(){return this->root;};
    int getNumOfNodes() const{return this->numOfNodes;};
    Node* searchAndAdd (int content);
    Node* search(int content);
    StatusType searchAndDelete(int content);
    void leftRoll(Node* node);
    void rightRoll(Node* node);
    void printLevelOrder(); //FOR DEBUGGING
};



#endif //DATASTURCURES_HW1_AVL_TREE_H
