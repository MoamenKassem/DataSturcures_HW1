#ifndef DTASTURCURES_HW1_NODE_H
#define DTASTURCURES_HW1_NODE_H

#include "wet1util.h"

template<class T>
class Node {
public:
    int content;
    Node* leftSon;
    Node* rightSon;
    Node* father;
    int height;
    int key;
    Genre genre;
    bool isVip;
    int views;
    int ComedyViews;
    int FantasyViews;
    int DramaViews;
    int ActionViews;
    T* curGroup;
    int groupViews;
    Node* groupUser;
    int GroupActionViews;
    int GroupComedyViews;
    int GroupDramaViews;
    int GroupFantasyViews;
    double rating;
    int usersRated;

    void addLeftSon(Node<T>* son);
    void addRightSon(Node<T>* son);
    void swapNodes(Node<T>* node1);
    int getBalanceFactor() const;
    int updateHeight();


    Node():content(0),leftSon(nullptr),rightSon(nullptr),
           father(nullptr),height(0),key(0),
           genre(Genre::NONE), isVip(false), views(0), ComedyViews(0), FantasyViews(0), DramaViews(0), ActionViews(0),
           curGroup(nullptr), groupViews(0), groupUser(nullptr), GroupActionViews(0), GroupComedyViews(0),
           GroupDramaViews(0), GroupFantasyViews(0), rating(0), usersRated(0){};


    Node(int key, int content,Node* father):content(content),leftSon(nullptr),rightSon(nullptr),
    father(father),height(0),key(key),
    genre(Genre::NONE), isVip(false), views(0), ComedyViews(0), FantasyViews(0), DramaViews(0), ActionViews(0),
    curGroup(nullptr), groupViews(0), groupUser(nullptr), GroupActionViews(0), GroupComedyViews(0),
    GroupDramaViews(0), GroupFantasyViews(0), rating(0), usersRated(0){};


    explicit Node(int key):content(0),leftSon(nullptr),rightSon(nullptr),
                  father(nullptr),height(0),key(key),
                  genre(Genre::NONE), isVip(false), views(0), ComedyViews(0),FantasyViews(0), DramaViews(0), ActionViews(0)
            ,curGroup(nullptr), groupViews(0), groupUser(nullptr)
            , GroupActionViews(0), GroupComedyViews(0), GroupDramaViews(0), GroupFantasyViews(0), rating(0), usersRated(0){};


    ~Node()
    {

    };
    Node(Node&)=default;
    Node& operator=(const Node& other)= default;
    void changeVip(bool newVip){isVip = newVip;}
    void changeViews(int newViews){views = newViews;}
    void changeGenre(Genre newGenre){genre = newGenre;}
};


template<class T>
void Node<T>::addLeftSon(Node<T>* son)
{
    this->leftSon = son;
}

//
template<class T>
void Node<T>::addRightSon(Node<T>* son)
{
    this->rightSon = son;
}
template<class T>
int Node<T>::updateHeight()
{
    int leftHeight,rightHeight;
    if(!this->leftSon)
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
    Node<T>* temp= new Node<T>();

    //save temp members
    temp->height = this->height;
    temp->rightSon = this->rightSon;
    temp->leftSon = this->leftSon;
    if(this->father == node1)
    {
        temp->father = this;
    }
    else{temp->father = this->father;}

    //change pointers for this node

    if(node1->rightSon == this)
    {
        this->rightSon = node1;
    }
    else{this->rightSon = node1->rightSon;}
    this->leftSon = node1->leftSon;
    this->father = node1->father;
    this->height = node1->height;

    //change pointers for this node

    node1->rightSon = temp->rightSon;
    node1->leftSon = temp->leftSon;
    node1->father = temp->father;
    node1->height = temp->height;

    delete temp;

    //change this node's members' connections to node1

    if(this->leftSon != nullptr)
        this->leftSon->father = this;
    if(this->rightSon != nullptr)
        this->rightSon->father = this;
    if (this->father != nullptr)
    {
        if(this->father->rightSon == node1)
        {
            this->father->rightSon = this;
        }
        else{this->father->leftSon = this;}

    }

    //change node1's members' connections to this
    if(node1->leftSon != nullptr)
        node1->leftSon->father = node1;
    if(node1->rightSon != nullptr)
        node1->rightSon->father = node1;
    if (node1->father != nullptr && node1->father->rightSon != node1)
    {
        if(node1->father->rightSon == this)
        {
            node1->father->rightSon = node1;
        }
        else{node1->father->leftSon = node1;}

    }


}
#endif //DTASTURCURES_HW1_NODE_H