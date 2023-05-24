//streamingdtb.h
#ifndef STREAMINGDBA1_H_
#define STREAMINGDBA1_H_
#ifndef NODE
#include "Node.h"
#define NODE
#endif

#include <cmath>
#include <iostream>
#include "AVL_Tree.h"
#include "GroupNode.h"
#include "wet1util.h"
class streaming_database {
private:
    AVL_Tree<Node<group_node>> users;
    AVL_Tree<group_node> groups;
    AVL_Tree<Node<group_node>> movies;
    AVL_Tree<Node<group_node>> comedyMovies;
    AVL_Tree<Node<group_node>> actionMovies;
    AVL_Tree<Node<group_node>> dramaMovies;
    AVL_Tree<Node<group_node>> fantasyMovies;
    AVL_Tree<Node<group_node>> moviesRating;
    Node<group_node>* maxRatingComedyMovie;
    Node<group_node>* maxRatingActionMovie;
    Node<group_node>* maxRatingDramaMovie;
    Node<group_node>* maxRatingFantasyMovie;



public:
    // <DO-NOT-MODIFY> {

    streaming_database();

    virtual ~streaming_database();

    StatusType add_movie(int movieId, Genre genre, int views, bool vipOnly);

    StatusType remove_movie(int movieId);

    StatusType add_user(int userId, bool isVip);

    StatusType remove_user(int userId);

    StatusType add_group(int groupId);

    StatusType remove_group(int groupId);

    StatusType add_user_to_group(int userId, int groupId);

    StatusType user_watch(int userId, int movieId);

    StatusType group_watch(int groupId,int movieId);

    output_t<int> get_all_movies_count(Genre genre);

    StatusType get_all_movies(Genre genre, int *const output);

    output_t<int> get_num_views(int userId, Genre genre);

    StatusType rate_movie(int userId, int movieId, int rating);

    output_t<int> get_group_recommendation(int groupId);

    // } </DO-NOT-MODIFY>
};
#endif // STREAMINGDBA1_H_
//streamingdtb.h end