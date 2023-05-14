//
// Created by MKassem360 on 5/10/2023.
//

#ifndef DATASTURCURES_HW1_NODE_H
#define DATASTURCURES_HW1_NODE_H


class Node {
public:
    int key;
    int content;
    Node* leftSon;
    Node* rightSon;
    Node* father; //if needed
    int numOfLeftSons;
    int numOfRightSons;
    int height;

    void addLeftSon(Node* son);
    void addRightSon(Node* son);
    int getBalanceFactor() const;
    int updateHeight();
    Node():content(0),leftSon(nullptr),rightSon(nullptr),
    father(nullptr),numOfRightSons(0),numOfLeftSons(0),height(0),key(0){};
    Node(int key, int content,Node* father):key(key),content(content),
    leftSon(nullptr),rightSon(nullptr),numOfRightSons(0),numOfLeftSons(0),father(father),height(0){}
    ~Node()=default;
    Node(Node&)=default;
};


#endif //DATASTURCURES_HW1_NODE_H
