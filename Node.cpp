#include "Node.h"

//
// Created by MKassem360 on 5/10/2023.
void Node::addSon(Node *son)
{
    if (son->father == nullptr)
        return;
    if (son->father->rightSon == son)
    {
        this->addRightSon(son);
        return;
    }
    this->addLeftSon(son);
}

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
    if(this->leftSon->height >= this->rightSon->height)
    {
        this->height = leftSon->height+1;
        return height;
    }
    this->height = leftSon->height+1;
    return height;
}
#include "Node.h"
