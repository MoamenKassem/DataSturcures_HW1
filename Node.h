#ifndef DTASTURCURES_HW1_NODE_H
#define DTASTURCURES_HW1_NODE_H

#include "wet1util.h"

template<class T>
class Node {
public:
    int key;
    int content;
    Genre genre;
    bool isVip;
    int views;
    int numOfLeftSons;
    int numOfRightSons;
    int height;
    int ComedyViews;
    int FantasyViews;
    int DramaViews;
    int ActionViews;
    int GroupComedyViews;
    int GroupFantasyViews;
    int GroupDramaViews;
    int GroupActionViews;
    double rating;
    int usersRated;
    Node* leftSon;
    Node* rightSon;
    Node* father; //if needed
    T* curGroup;
    int groupViews;
    Node* groupUser;

    void addLeftSon(Node<T>* son);
    void addRightSon(Node<T>* son);
    void swapNodes(Node<T>* node1);
    int getBalanceFactor() const;
    int updateHeight();


    Node():content(0),leftSon(nullptr),rightSon(nullptr),
           father(nullptr),numOfRightSons(0),numOfLeftSons(0),height(0),key(0),
           genre(Genre::NONE), isVip(0), views(0), ComedyViews(0), FantasyViews(0), DramaViews(0), ActionViews(0),
           curGroup(nullptr), groupViews(0), groupUser(nullptr), GroupActionViews(0), GroupComedyViews(0),
           GroupDramaViews(0), GroupFantasyViews(0), rating(0), usersRated(0){};


    Node(int key, int content,Node* father):key(key),content(content),genre(Genre::NONE),isVip(0),views(0),
                                            leftSon(nullptr),rightSon(nullptr),numOfRightSons(0),numOfLeftSons(0),father(father),height(0), ComedyViews(0)
            , FantasyViews(0), DramaViews(0), ActionViews(0), curGroup(nullptr), groupViews(0), groupUser(nullptr)
            , GroupActionViews(0), GroupComedyViews(0), GroupDramaViews(0), GroupFantasyViews(0), rating(0), usersRated(0){}


    Node(int key):content(0),leftSon(nullptr),rightSon(nullptr),
                  father(nullptr),numOfRightSons(0),numOfLeftSons(0),height(0),key(key),
                  genre(Genre::NONE), isVip(0), views(0), ComedyViews(0),FantasyViews(0), DramaViews(0), ActionViews(0)
            ,curGroup(nullptr), groupViews(0), groupUser(nullptr)
            , GroupActionViews(0), GroupComedyViews(0), GroupDramaViews(0), GroupFantasyViews(0), rating(0), usersRated(0){};


    ~Node()=default;
    Node(Node&)=default;
    Node& operator=(const Node& other)= default;
    void changeVip(bool newVip){isVip = newVip;}
    void changeViews(int newViews){views = newViews;}
    void changeGenre(Genre newGenre){genre = newGenre;}
    void changeContent(int newContent){content = newContent;}
};


template<class T>
void Node<T>::addLeftSon(Node<T>* son)
{
    this->leftSon = son;
    Node<T>* currentFather = son->father;
    while(currentFather != nullptr)
    {
        currentFather->numOfLeftSons++;
        currentFather = currentFather->father;
    }
}

//
template<class T>
void Node<T>::addRightSon(Node<T>* son)
{
    this->rightSon = son;
    Node<T>* currentFather = son->father;
    while(currentFather != nullptr)
    {
        currentFather->numOfRightSons++;
        currentFather = currentFather->father;
    }

}
template<class T>
int Node<T>::updateHeight()
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

template<class T>
int Node<T>::getBalanceFactor() const
{
    int leftHeight,rightHeight;
    if(this->leftSon == nullptr)
    {
        leftHeight = -1;
    } else
    {
        leftSon->updateHeight();
        leftHeight = leftSon->height;
    }
    if(this->rightSon == nullptr)
    {
        rightHeight = -1;
    } else
    {

        rightSon->updateHeight();
        rightHeight = rightSon->height;
    }
    return leftHeight-rightHeight;
}

template<class T>
void Node<T>::swapNodes(Node<T>* node1)
{
    Node<T>* temp= new Node();
    copyNodeContent(temp,node1);
    copyNodeContent(node1,this);
    copyNodeContent(this,temp);

}
#endif //DATASTURCURES_HW1_NODE_H