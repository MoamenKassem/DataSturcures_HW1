#include "Node.h"

//
// Created by MKassem360 on 5/10/2023.

void Node::addLeftSon(Node *son)
{
    this->leftSon = son;
    this->numOfLeftSons++;
}

//
void Node::addRightSon(Node *son)
{
    this->rightSon = son;
    this->numOfRightSons++;
}
int Node::updateHeight()
{
    int leftHeight,rightHeight;
    if(this->leftSon == nullptr)
    {
        leftHeight = -1;
    }
    else
    {
        leftHeight= this->leftSon->height;
    }
    if(this->rightSon == nullptr)
    {
        rightHeight = -1;
    }
    else
    {
        rightHeight= this->rightSon->height;
    }

    if(leftHeight > rightHeight)
    {
        this->height = leftHeight+1;
        return height;
    }
    this->height = rightHeight+1;
    return height;
}

