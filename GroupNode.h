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
    group_node* leftSon;
    group_node* rightSon;
    group_node* father;
    AVL_Tree<Node<group_node>> members;
    int key;
    int content;
    bool isVip;
    int views;
    int numOfLeftSons;
    int numOfRightSons;
    int height;
    int ComedyViews;
    int FantasyViews;
    int DramaViews;
    int ActionViews;
    int moviesWatched;
    int ComedyWatched;
    int FantasyWatched;
    int DramaWatched;
    int ActionWatched;
    double rating;


    group_node():content(0),leftSon(nullptr),rightSon(nullptr),
                 father(nullptr),numOfRightSons(0),numOfLeftSons(0),height(0),key(0), isVip(0),
                 views(0), ComedyViews(0), FantasyViews(0), DramaViews(0), moviesWatched(0) , ActionViews(0)
            ,ComedyWatched(0), ActionWatched(0), FantasyWatched(0),DramaWatched(0), rating(0)
    {members = AVL_Tree<Node<group_node>>();}
    group_node(int key1, int content1,group_node* father1):content(content1),
                                                           leftSon(nullptr),rightSon(nullptr),
                                                           father(father1),numOfRightSons(0),numOfLeftSons(0),height(0),key(key1), isVip(0),
                                                           views(0), ComedyViews(0), FantasyViews(0), DramaViews(0), moviesWatched(0), ActionViews(0)
            ,ComedyWatched(0), ActionWatched(0), FantasyWatched(0),DramaWatched(0), rating(0)
    {members = AVL_Tree<Node<group_node>>();}
    group_node(int key1):content(0),leftSon(nullptr),rightSon(nullptr),
                         father(nullptr),numOfRightSons(0),numOfLeftSons(0),height(0),key(key1), isVip(0),
                         views(0), ComedyViews(0), FantasyViews(0), DramaViews(0), moviesWatched(0), ActionViews(0)
            ,ComedyWatched(0), ActionWatched(0), FantasyWatched(0),DramaWatched(0), rating(0)
    {members = AVL_Tree<Node<group_node>>();}
    void addLeftSon(group_node* son){
        this->leftSon = son;
        group_node* currentFather = son->father;
        while(currentFather != nullptr)
        {
            currentFather->numOfLeftSons++;
            currentFather = currentFather->father;
        }
    }
    void addRightSon(group_node* son){
        this->rightSon = son;
        group_node* currentFather = son->father;
        while(currentFather != nullptr)
        {
            currentFather->numOfRightSons++;
            currentFather = currentFather->father;
        }
    }
    void swapNodes(group_node* node1){
        int temp;
        temp = this->content;
        this->content = node1->content;
        node1->content = temp;
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
