//
// Created by MKassem360 on 5/10/2023.
//
#include "wet1util.h"
#ifndef DATASTURCURES_HW1_NODE_H
#define DATASTURCURES_HW1_NODE_H


class Node {
public:
    int key;
    int content;
    Genre genre;
    bool isVip;
    int views;
    Node* leftSon;
    Node* rightSon;
    Node* father; //if needed
    int numOfLeftSons;
    int numOfRightSons;
    int height;
    Node* groupUsers;

    void addLeftSon(Node* son);
    void addRightSon(Node* son);
    int getBalanceFactor() const;
    int updateHeight();
    void swapNodes(Node* node1);
    Node():content(0),leftSon(nullptr),rightSon(nullptr),
    father(nullptr),numOfRightSons(0),numOfLeftSons(0),height(0),key(0),
    genre(Genre::NONE), isVip(0), views(0), groupUsers(nullptr){};
    Node(int key, int content,Node* father):key(key),content(content),genre(Genre::NONE),isVip(0),views(0),
    leftSon(nullptr),rightSon(nullptr),numOfRightSons(0),numOfLeftSons(0),
    father(father),height(0), groupUsers(nullptr){}
    Node(int key):content(0),leftSon(nullptr),rightSon(nullptr),
    father(nullptr),numOfRightSons(0),numOfLeftSons(0),height(0),key(key),
    genre(Genre::NONE), isVip(0), views(0), groupUsers(nullptr){};
    ~Node()=default;
    Node(Node&)=default;
    Node& operator=(const Node& other)= default;
    void changeVip(bool newVip){isVip = newVip;}
    void changeViews(int newViews){views = newViews;}
    void changeGenre(Genre newGenre){genre = newGenre;}
    void changeContent(int newContent){content = newContent;}
};


#endif //DATASTURCURES_HW1_NODE_H
