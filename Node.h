//
// Created by MKassem360 on 5/10/2023.
//

#ifndef DATASTURCURES_HW1_NODE_H
#define DATASTURCURES_HW1_NODE_H


class Node {
public:
    int key;
    void* content;
    Node* leftSon;
    Node* rightSon;
    Node* father; //if needed
    int numOfLeftSons;
    int numOfRightSons;
    int height;

    void addSon(Node* son);
    void addLeftSon(Node* son);
    void addRightSon(Node* son);
    int getBalanceFactor(){return numOfLeftSons-numOfRightSons;}
    int updateHeight();
    Node()=default;
    Node(int key, void* content,Node* father):key(key),content(content),
                                              leftSon(nullptr),rightSon(nullptr),numOfRightSons(0),numOfLeftSons(0),father(father){}
    ~Node()=default;
    Node(Node&)=default;
};


#endif //DATASTURCURES_HW1_NODE_H
