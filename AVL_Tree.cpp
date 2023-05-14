//
// Created by MKassem360 on 5/10/2023.
//

#include "AVL_Tree.h"
#include <cmath>
#include <iostream>
#include <queue>


void AVL_Tree::searchAndAdd(int content)
{
    // Search

    int toInsert_index= content;
    Node* currentNodePtr = this->root;
    Node* currentFatherNodePtr = nullptr;
    Node* toInsert = nullptr;
    while(currentNodePtr != nullptr)
    {
        currentFatherNodePtr = currentNodePtr;
        if (currentNodePtr->content < content)
        {
            currentNodePtr = currentNodePtr->rightSon; //Go to right son
            if (currentNodePtr == nullptr)
            {
                toInsert= new Node(toInsert_index,content,currentFatherNodePtr);
                currentFatherNodePtr->addRightSon(toInsert);
                break;
            }
            continue;
        }
        currentNodePtr = currentNodePtr->leftSon; //Go to right son
        if (currentNodePtr == nullptr)
        {
            toInsert = new Node(toInsert_index,content,currentFatherNodePtr);
            currentFatherNodePtr->addLeftSon(toInsert);
            break;
        }
    }
    // Add
    if(currentFatherNodePtr == nullptr && currentNodePtr == nullptr) //new root
    {
        toInsert = new Node(toInsert_index,content, nullptr);
        this->root=toInsert;
        toInsert->updateHeight();
        this->numOfNodes++;
        return;
    }

    int oldHeight = currentFatherNodePtr->height;
    while(oldHeight != currentFatherNodePtr->updateHeight())
    {
        int currentBalanceFactor = currentFatherNodePtr->getBalanceFactor();
        if(abs(currentBalanceFactor) == 2)
        {
            if(currentBalanceFactor == -2) //balance -2 -> RR/RL
            {
                if(currentFatherNodePtr->rightSon->getBalanceFactor() == 1) //RL
                {
                    rightRoll(currentFatherNodePtr->rightSon);
                    leftRoll(currentFatherNodePtr);
                }
                //RR
                leftRoll(currentFatherNodePtr);

            }
            //balance 2 -> LR/LL
            if(currentFatherNodePtr->leftSon->getBalanceFactor() == -1) //LR
            {
                leftRoll(currentFatherNodePtr->leftSon);
                rightRoll(currentFatherNodePtr);
            }
            //LL
            rightRoll(currentFatherNodePtr);
            break;
        }

        currentFatherNodePtr = currentFatherNodePtr->father;
        if (currentFatherNodePtr == nullptr)
            break;
        oldHeight = currentFatherNodePtr->height;
    }
    this->numOfNodes++;
}

void AVL_Tree::leftRoll(Node* node)
{
    Node *newHead,*tempNode;
    newHead = node->rightSon;
    tempNode = newHead->leftSon;
    newHead->leftSon = node;
    node->rightSon = tempNode;
    //correcting fathers
    newHead->father=node->father;
    node->father=newHead;
    tempNode->father=node;
}

void AVL_Tree::rightRoll(Node* node)
{
    Node *newHead,*tempNode;
    newHead = node->leftSon;
    tempNode = newHead->rightSon;
    newHead->rightSon = node;
    node->leftSon = tempNode;
    //correcting fathers
    newHead->father=node->father;
    node->father=newHead;
    tempNode->father=node;
}

void AVL_Tree::printLevelOrder() {
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
            if (curr != nullptr) {
                std::cout << curr->key << " ";
                q.push(curr->leftSon);
                q.push(curr->rightSon);
            } else {
                std::cout << "null ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "---------------------------------------------------------------------" << std::endl;
}
