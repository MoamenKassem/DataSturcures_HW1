//
// Created by MKassem360 on 5/18/2023.
//

#ifndef DATASTURCURES_HW1_GROUPNODE_H
#define DATASTURCURES_HW1_GROUPNODE_H
#ifndef NODE
#include "Node.h"
#define NODE
#endif

#include "AVL_Tree.h"
//group_node.h
class group_node
{
public:
    int content;
    group_node* leftSon;
    group_node* rightSon;
    group_node* father;
    int height;
    int key;
    bool isVip;
    int views;
    int ComedyViews;
    int FantasyViews;
    int DramaViews;
    int moviesWatched;
    int ActionViews;
    int ComedyWatched;
    int ActionWatched;
    int FantasyWatched;
    int DramaWatched;
    double rating;
    int numOfVipUsers;
    AVL_Tree<Node<group_node>> members;


    group_node():content(0),leftSon(nullptr),rightSon(nullptr),
                 father(nullptr),height(0),key(0), isVip(false),
                 views(0), ComedyViews(0), FantasyViews(0), DramaViews(0), moviesWatched(0) , ActionViews(0)
            ,ComedyWatched(0), ActionWatched(0), FantasyWatched(0),DramaWatched(0), rating(0), numOfVipUsers(0)
    {members = AVL_Tree<Node<group_node>>();}
    group_node(int key1, int content1,group_node* father1):content(content1),
    leftSon(nullptr),rightSon(nullptr),father(father1),height(0),key(key1),
    isVip(false),views(0), ComedyViews(0), FantasyViews(0), DramaViews(0), moviesWatched(0), ActionViews(0)
            ,ComedyWatched(0), ActionWatched(0), FantasyWatched(0),DramaWatched(0), rating(0), numOfVipUsers(0)
    {members = AVL_Tree<Node<group_node>>();}
    explicit group_node(int key1):content(0),leftSon(nullptr),rightSon(nullptr),
    father(nullptr),height(0),key(key1), isVip(false),
    views(0), ComedyViews(0), FantasyViews(0), DramaViews(0), moviesWatched(0), ActionViews(0)
            ,ComedyWatched(0), ActionWatched(0), FantasyWatched(0),DramaWatched(0), rating(0), numOfVipUsers(0)
    {members = AVL_Tree<Node<group_node>>();}

    void addLeftSon(group_node* son){
        this->leftSon = son;
    }

    void addRightSon(group_node* son){
        this->rightSon = son;
    }

    void swapNodes(group_node* node1)
    {
        group_node* temp= new group_node();

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
    int updateHeight()
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
    int getBalanceFactor() const
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
    ~group_node()=default;
    group_node(group_node&)=default;
    group_node& operator=(const group_node& other)= default;
};

// group_node.h end


#endif //DATASTURCURES_HW1_GROUPNODE_H
