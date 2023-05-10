//
// Created by MKassem360 on 5/10/2023.
//

#ifndef DATASTURCURES_HW1_AVL_TREE_H
#define DATASTURCURES_HW1_AVL_TREE_H
#include "Node.h"

class AVL_Tree {
    int numOfNodes;
    Node root;
public:
    AVL_Tree()=default;
    ~AVL_Tree()=default;
    AVL_Tree(AVL_Tree& avlTree)=default;
    Node getRoot(){return this->root;};
    int getNumOfNodes(){return this->numOfNodes;};
    void searchAndAdd(void* content);
    void searchAndDelete(void* content);
    static void leftRoll();
    static void rightRoll();
    void printLevelOrder(); //FOR DEBUGGING
};



#endif //DATASTURCURES_HW1_AVL_TREE_H
