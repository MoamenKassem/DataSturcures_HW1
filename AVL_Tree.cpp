//
// Created by MKassem360 on 5/10/2023.
//

#include "AVL_Tree.h"
#include <cmath>
#include <string>
#include <iostream>
#include <queue>


void AVL_Tree::searchAndAdd(void* content)
{
    // Search

    int toInsert_index= this->getNumOfNodes();
    Node* currentNodePtr = &this->root;
    Node* currentFatherNodePtr;
    while(currentNodePtr != nullptr)
    {
        currentFatherNodePtr = currentNodePtr;
        if (currentNodePtr->key < toInsert_index)
        {
            currentNodePtr = currentNodePtr->rightSon; //Go to right son
            continue;
        }
        currentNodePtr = currentNodePtr->leftSon; //Go to right son
    }
    // Add
    Node* toInsert= new Node(toInsert_index,content,currentFatherNodePtr);
    currentFatherNodePtr->addSon(toInsert);
    int oldHeight = currentFatherNodePtr->height;
    while(oldHeight != currentFatherNodePtr->updateHeight())
    {
        if(abs(currentFatherNodePtr->getBalanceFactor()) == 2)
        {
            //rolling as intended
            break;
        }

        currentFatherNodePtr = currentFatherNodePtr->father;
        oldHeight = currentFatherNodePtr->height;
    }

}

void AVL_Tree::printLevelOrder() {
    Node* root = &this->root;
    if (root == nullptr) {
        return;
    }
    std::queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            Node* curr = q.front();
            q.pop();
            if (curr != NULL) {
                std::cout << curr->key << " ";
                q.push(curr->leftSon);
                q.push(curr->rightSon);
            } else {
                std::cout << "null ";
            }
        }
        std::cout << std::endl;
    }
}
