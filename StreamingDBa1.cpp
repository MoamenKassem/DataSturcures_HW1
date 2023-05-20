#include "AVL_Tree.h"
#include "wet1util.h"
#include "StreamingDBa1.h"
#ifndef NODE
#include "Node.h"
#define NODE
#endif



streaming_database::streaming_database()
{
    movies = AVL_Tree<Node<group_node>>();
    users = AVL_Tree<Node<group_node>>();
    groups = AVL_Tree<group_node>();
    comedyMovies = AVL_Tree<Node<group_node>>();
    actionMovies = AVL_Tree<Node<group_node>>();
    fantasyMovies = AVL_Tree<Node<group_node>>();
    dramaMovies = AVL_Tree<Node<group_node>>();
    moviesRating = AVL_Tree<Node<group_node>>();
}

int max_view_in_group(int action, int drama, int comedy, int fantasy) {
    if (action > comedy) {
        if (action > drama) {
            if (action >= fantasy) //action > fantasy > drama > comedy
            {
                return (int) Genre::ACTION;
            }
            return (int) Genre::FANTASY;//fantasy > action > drama > comedy
        }

        if (drama >= fantasy) {
            return (int) Genre::DRAMA; //drama > fantasy > action >  comedy
        }
        return (int) Genre::FANTASY; //fantasy > drama > action > comedy
    }
    if (comedy >= drama) {
        if (comedy >= fantasy) //comedy > fantasy > drama > action
        {
            return (int) Genre::COMEDY;
        }
        return (int) Genre::FANTASY;//fantasy > action > drama > comedy
    }
    if (drama >= fantasy)
        return (int) Genre::DRAMA;
    return (int) Genre::FANTASY;
}




template <class T>
void copyNodeContent(Node<T>* ptr1, const Node<T>* ptr2){
    ptr1->key = ptr2->key;
    ptr1->content = ptr2->content;
    ptr1->views = ptr2->views;
    ptr1->groupViews = ptr2->groupViews;
    ptr1->GroupFantasyViews = ptr2->GroupFantasyViews;
    ptr1->GroupDramaViews = ptr2->GroupDramaViews;
    ptr1->GroupComedyViews = ptr2->GroupComedyViews;
    ptr1->GroupActionViews = ptr2->GroupActionViews;
    ptr1->isVip = ptr2->isVip;
    ptr1->curGroup =ptr2->curGroup;
    ptr1->genre = ptr2->genre;
    ptr1->ActionViews = ptr2->ActionViews;
    ptr1->DramaViews = ptr2->DramaViews;
    ptr1->FantasyViews = ptr2->FantasyViews;
    ptr1->ComedyViews = ptr2->ComedyViews;
    ptr1->rating = ptr2->rating;
}

template<class T>
void deleteTree(T* root){
    T* ptr = root;
    if(ptr == nullptr){
        return;
    }
    deleteTree(ptr->leftSon);
    deleteTree(ptr->rightSon);
    delete ptr;
}

streaming_database::~streaming_database()
{
    deleteTree(users.getRoot());
    deleteTree(groups.getRoot());
    deleteTree(movies.getRoot());
    deleteTree(comedyMovies.getRoot());
    deleteTree(actionMovies.getRoot());
    deleteTree(fantasyMovies.getRoot());
    deleteTree(dramaMovies.getRoot());
    deleteTree(moviesRating.getRoot());
}


StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly)
{
    if(movieId <= 0 || genre == Genre::NONE || views < 0){
        return StatusType::INVALID_INPUT;
    }
    Node<group_node>* movie = new Node<group_node>(0,movieId, nullptr);
    if(!movie){
        return StatusType::ALLOCATION_ERROR;
    }
    StatusType status = movies.searchAndAdd(movie);
    if(status != StatusType::SUCCESS){
        return status;
    }
    Node<group_node>* genreMovie = new Node<group_node>(0,movieId, nullptr);
    Node<group_node>* rattingMovie = new Node<group_node>(0,movieId, nullptr);
    movie->changeVip(vipOnly);
    movie->changeGenre(genre);
    movie->changeViews(views);
    copyNodeContent(genreMovie, movie);
    copyNodeContent(rattingMovie, movie);
    moviesRating.searchAndAddRating(rattingMovie);
    switch (genre) {
        case Genre::COMEDY:
            comedyMovies.searchAndAddRating(genreMovie);
            maxRatingComedyMovie = comedyMovies.getMax();
            return StatusType::SUCCESS;
        case Genre::ACTION:
            actionMovies.searchAndAddRating(genreMovie);
            maxRatingActionMovie = actionMovies.getMax();
            return StatusType::SUCCESS;
        case Genre::FANTASY:
            fantasyMovies.searchAndAddRating(genreMovie);
            maxRatingFantasyMovie = fantasyMovies.getMax();
            return StatusType::SUCCESS;
        case Genre::DRAMA:
            dramaMovies.searchAndAddRating(genreMovie);
            maxRatingDramaMovie = dramaMovies.getMax();
            return StatusType::SUCCESS;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_movie(int movieId)
{
    if(movieId <=0){
        return StatusType::INVALID_INPUT;
    }
    Node<group_node>* curMovie = movies.search(movieId);
    if(curMovie->key == -1){
        delete curMovie;
        return StatusType::FAILURE;
    }
    switch (curMovie->genre){
        case Genre::COMEDY:
            comedyMovies.searchAndDeleteRating(curMovie->rating,curMovie->views,curMovie->content);
            maxRatingComedyMovie = comedyMovies.getMax();
            break;
        case Genre::ACTION:
            actionMovies.searchAndDeleteRating(curMovie->rating,curMovie->views,curMovie->content);
            maxRatingActionMovie = actionMovies.getMax();
            break;
        case Genre::FANTASY:
            fantasyMovies.searchAndDeleteRating(curMovie->rating,curMovie->views,curMovie->content);
            maxRatingFantasyMovie = fantasyMovies.getMax();
            break;
        case Genre::DRAMA:
            dramaMovies.searchAndDeleteRating(curMovie->rating,curMovie->views,curMovie->content);
            maxRatingDramaMovie = dramaMovies.getMax();
            break;
    }

    moviesRating.searchAndDeleteRating(curMovie->rating,curMovie->views,curMovie->content);
    return movies.searchAndDelete(movieId);
}

StatusType streaming_database::add_user(int userId, bool isVip)
{
    if(userId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Node<group_node>* user = new Node<group_node>(0,userId, nullptr);
    if(!user){
        return StatusType::ALLOCATION_ERROR;
    }
    StatusType status = users.searchAndAdd(user);
    if(status != StatusType::SUCCESS){
        return status;
    }
    user->changeVip(isVip);
    user->changeViews(0);
    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_user(int userId)
{
    if(userId <=0){
        return StatusType::INVALID_INPUT;
    }
    return users.searchAndDelete(userId);
}

StatusType streaming_database::add_group(int groupId)
{
    if(groupId <=0){
        return StatusType::INVALID_INPUT;
    }
    group_node* group = new group_node(0,groupId, nullptr);
    if(!group){
        return StatusType::ALLOCATION_ERROR;
    }
    StatusType status = groups.searchAndAdd(group);
    if(status != StatusType::SUCCESS){
        return status;
    }
    group->views = 0;
    group->isVip = false;
    return StatusType::SUCCESS;
}
void incrementAndDelete(Node<group_node>* ptr, const group_node* group){
    if(!ptr){
        return;
    }
    incrementAndDelete(ptr->leftSon,group);
    incrementAndDelete(ptr->rightSon,group);
    ptr->groupUser->views = ptr->groupUser->views + group->moviesWatched - ptr->groupUser->groupViews;
    ptr->groupUser->FantasyViews = ptr->groupUser->FantasyViews + group->FantasyWatched
                                   - ptr->groupUser->GroupFantasyViews;
    ptr->groupUser->ActionViews = ptr->groupUser->ActionViews + group->ActionWatched -
                                  ptr->groupUser->GroupActionViews;
    ptr->groupUser->DramaViews = ptr->groupUser->DramaViews + group->DramaWatched
                                 - ptr->groupUser->GroupDramaViews;
    ptr->groupUser->ComedyViews = ptr->groupUser->ComedyViews + group->ComedyWatched
                                  - ptr->groupUser->GroupComedyViews;
    ptr->groupUser->curGroup = nullptr;
    delete ptr;
}
StatusType streaming_database::remove_group(int groupId)
{
    if(groupId <=0){
        return StatusType::INVALID_INPUT;
    }
    group_node* groupToDelete = groups.search(groupId);
    if(groupToDelete->key == -1){
        delete groupToDelete;
        return StatusType::FAILURE;
    }
    Node<group_node>* ptr = groupToDelete->members.getRoot();
    incrementAndDelete(ptr, groupToDelete);
    return groups.searchAndDelete(groupId);
}

StatusType streaming_database::add_user_to_group(int userId, int groupId)
{
    if(userId <=0 || groupId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Node<group_node>* user = users.search(userId); // O(log(n))
    if(user->key == -1){
        delete user;
        return StatusType::FAILURE;
    }
    if(user->curGroup != nullptr){
        return StatusType::FAILURE;
    }
    group_node* group = groups.search(groupId); // O(log(m))
    if(!group){
        return StatusType::ALLOCATION_ERROR;
    }
    if (group->key == -1){
        delete group;
        return StatusType::FAILURE;
    }
    user->curGroup = group;
    if(!group->isVip && user->isVip){
        group->isVip = true;
    }
    Node<group_node>* groupUser = new Node<group_node>(0,userId, nullptr);
    if(!groupUser){
        return StatusType::ALLOCATION_ERROR;
    }
    user->groupViews = group->moviesWatched;
    user->GroupFantasyViews = group->FantasyWatched;
    user->GroupDramaViews = group->DramaWatched;
    user->GroupComedyViews = group->ComedyWatched;
    user->GroupActionViews = group->ActionWatched;
    copyNodeContent(groupUser,user);
    groupUser->groupUser = user;
    group->views+=user->views;
    group->ComedyViews+= user->ComedyViews;
    group->DramaViews+= user->DramaViews;
    group->ActionViews+= user->ActionViews;
    group->FantasyViews+= user->FantasyViews;
    StatusType status = group->members.searchAndAdd(groupUser);
    if(status != StatusType::SUCCESS){
        delete groupUser;
        return status;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::user_watch(int userId, int movieId)
{
    if(userId <= 0 || movieId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Node<group_node>* user = users.search(userId); // O(log(n))
    if(user->key == -1){
        delete user;
        return StatusType::FAILURE;
    }
    Node<group_node>* movie = movies.search(movieId); // O(log(k))
    if(movie->key == -1){
        delete movie;
        return StatusType::FAILURE;
    }
    if(movie->isVip && !user->isVip){
        return StatusType::FAILURE;
    }
    StatusType status = moviesRating.searchAndDeleteRating(movie->rating,movie->views,movie->content);
    if(status != StatusType::SUCCESS){
        return status;
    }
    user->views++;
    movie->views++;

    Node<group_node>* curMovie2 = new Node<group_node>(0,movieId, nullptr);
    copyNodeContent(curMovie2,movie);

    StatusType status2 = moviesRating.searchAndAddRating(curMovie2);
    if(status != StatusType::SUCCESS){
        return status;
    }


    Node<group_node>* curMovie = new Node<group_node>(0,movieId, nullptr);
    copyNodeContent(curMovie,movie);
    switch (movie->genre) {
        case Genre::COMEDY:
            user->ComedyViews++;
            comedyMovies.searchAndDeleteRating(movie->rating,movie->views-1,movie->content);
            comedyMovies.searchAndAddRating(curMovie);
            if(user->curGroup)
            {
                user->curGroup->ComedyViews++;
                user->curGroup->views++;
            }
            break;
        case Genre::ACTION:
            user->ActionViews++;
            actionMovies.searchAndDeleteRating(movie->rating,movie->views-1,movie->content);
            actionMovies.searchAndAddRating(curMovie);
            maxRatingActionMovie = actionMovies.getMax();
            if(user->curGroup)
            {
                user->curGroup->ActionViews++;
                user->curGroup->views++;
            }
            break;
        case Genre::FANTASY:
            user->FantasyViews++;
            fantasyMovies.searchAndDeleteRating(movie->rating,movie->views-1,movie->content);
            fantasyMovies.searchAndAddRating(curMovie);
            maxRatingFantasyMovie = fantasyMovies.getMax();
            if(user->curGroup)
            {
                user->curGroup->FantasyViews++;
                user->curGroup->views++;
            }
            break;
        case Genre::DRAMA:
            user->DramaViews++;
            dramaMovies.searchAndDeleteRating(movie->rating,movie->views-1,movie->content);
            dramaMovies.searchAndAddRating(curMovie);
            maxRatingDramaMovie = dramaMovies.getMax();
            if(user->curGroup)
            {
                user->curGroup->DramaViews++;
                user->curGroup->views++;
            }
            break;
        case Genre::NONE:
            break;
    }
    return StatusType::SUCCESS;
}

StatusType streaming_database::group_watch(int groupId,int movieId)
{
    if(groupId <= 0 || movieId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Node<group_node>* movie = movies.search(movieId); // O(log(k))
    if(movie->key == -1){
        delete movie;
        return StatusType::FAILURE;
    }
    group_node* group = groups.search(groupId); // O(log(m))
    if(group->key == -1){
        delete group;
        return StatusType::FAILURE;
    }
    if(movie->isVip && !group->isVip){
        return StatusType::FAILURE;
    }
    if(group->members.getNumOfNodes() == 0){
        return StatusType::FAILURE;
    }
    StatusType status = moviesRating.searchAndDeleteRating(movie->rating,movie->views,movie->content);
    if(status != StatusType::SUCCESS){
        return status;
    }
    movie->views+=group->members.getNumOfNodes();

    Node<group_node>* curMovie2 = new Node<group_node>(0,movieId, nullptr);
    copyNodeContent(curMovie2,movie);

    StatusType status2 = moviesRating.searchAndAddRating(curMovie2);
    if(status != StatusType::SUCCESS){
        return status;
    }


    Node<group_node>* curMovie = new Node<group_node>(0,movieId, nullptr);
    copyNodeContent(curMovie,movie);
    group->moviesWatched++;
    switch (movie->genre) {
        case Genre::COMEDY:
            group->ComedyWatched++;
            comedyMovies.searchAndDeleteRating(movie->rating,
                                               movie->views-group->members.getNumOfNodes(),movie->content);
            comedyMovies.searchAndAddRating(curMovie);
            maxRatingComedyMovie = comedyMovies.getMax();
            group->ComedyViews += group->members.getNumOfNodes();
            break;
        case Genre::ACTION:
            group->ActionWatched++;
            actionMovies.searchAndDeleteRating(movie->rating,
                                               movie->views-group->members.getNumOfNodes(),movie->content);
            actionMovies.searchAndAddRating(curMovie);
            maxRatingActionMovie = actionMovies.getMax();
            group->ActionViews += group->members.getNumOfNodes();
            break;
        case Genre::FANTASY:
            group->FantasyWatched++;
            fantasyMovies.searchAndDeleteRating(movie->rating,
                                                movie->views-group->members.getNumOfNodes(),movie->content);
            fantasyMovies.searchAndAddRating(curMovie);
            maxRatingFantasyMovie = fantasyMovies.getMax();
            group->FantasyViews += group->members.getNumOfNodes();
            break;
        case Genre::DRAMA:
            group->DramaWatched++;
            dramaMovies.searchAndDeleteRating(movie->rating,
                                              movie->views-group->members.getNumOfNodes(),movie->content);
            dramaMovies.searchAndAddRating(curMovie);
            maxRatingDramaMovie = dramaMovies.getMax();
            group->DramaViews += group->members.getNumOfNodes();
            break;
        case Genre::NONE:
            break;
    }
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_all_movies_count(Genre genre)
{
    switch (genre) {
        case Genre::COMEDY:
            return output_t<int>{comedyMovies.getNumOfNodes()};
        case Genre::ACTION:
            return output_t<int>{actionMovies.getNumOfNodes()};
        case Genre::FANTASY:
            return output_t<int>{fantasyMovies.getNumOfNodes()};
        case Genre::DRAMA:
            return output_t<int>{dramaMovies.getNumOfNodes()};
        case Genre::NONE:
            return output_t<int>{movies.getNumOfNodes()};
    }
    return output_t<int>(StatusType::ALLOCATION_ERROR);
}
void iterate(int* i, int *const output, Node<group_node>* ptr){ // not finished
    if(!ptr){
        return;
    }
    iterate(i, output, ptr->rightSon);
    output[i[0]] = ptr->content;
    i[0]++;
    iterate(i, output, ptr->leftSon);
}
StatusType streaming_database::get_all_movies(Genre genre, int *const output) // not finished
{
    if(movies.getNumOfNodes() == 0){
        return StatusType::FAILURE;
    }
    int i[1];
    i[0] = 0;
    switch (genre) {
        case Genre::COMEDY:
            if(comedyMovies.getNumOfNodes() == 0){
                return StatusType::FAILURE;
            }
            iterate(i,output,comedyMovies.getRoot());
            return StatusType::SUCCESS;
        case Genre::ACTION:
            if(actionMovies.getNumOfNodes() == 0){
                return StatusType::FAILURE;
            }
            iterate(i,output,actionMovies.getRoot());
            return StatusType::SUCCESS;
        case Genre::FANTASY:
            if(fantasyMovies.getNumOfNodes() == 0){
                return StatusType::FAILURE;
            }
            iterate(i,output,fantasyMovies.getRoot());
            return StatusType::SUCCESS;
        case Genre::DRAMA:
            if(dramaMovies.getNumOfNodes() == 0){
                return StatusType::FAILURE;
            }
            iterate(i,output,dramaMovies.getRoot());
            return StatusType::SUCCESS;
        case Genre::NONE:
            iterate(i,output,moviesRating.getRoot());
            return StatusType::SUCCESS;
    }
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_num_views(int userId, Genre genre)
{
    if(userId <= 0 ){
        return output_t<int>{StatusType::INVALID_INPUT};
    }
    Node<group_node>* user = users.search(userId); // O(log(n))
    if(user->key == -1){
        delete user;
        return StatusType::FAILURE;
    }
    switch (genre) {
        case Genre::COMEDY:
            if(!user->curGroup){
                return output_t<int>{user->ComedyViews};
            }
            return output_t<int>{user->ComedyViews + user->curGroup->ComedyWatched - user->GroupComedyViews};
        case Genre::ACTION:
            if(!user->curGroup){
                return output_t<int>{user->ActionViews};
            }
            return output_t<int>{user->ActionViews + user->curGroup->ActionWatched - user->GroupActionViews};
        case Genre::FANTASY:
            if(!user->curGroup){
                return output_t<int>{user->FantasyViews};
            }
            return output_t<int>{user->FantasyViews + user->curGroup->FantasyWatched - user->GroupFantasyViews};
        case Genre::DRAMA:
            if(!user->curGroup){
                return output_t<int>{user->DramaViews};
            }
            return output_t<int>{user->DramaViews + user->curGroup->DramaWatched - user->GroupDramaViews};
        case Genre::NONE:
            if(!user->curGroup){
                return output_t<int>{user->views};
            }
            return output_t<int>{user->views + user->curGroup->moviesWatched - user->groupViews};
    }
    return output_t<int>(StatusType::ALLOCATION_ERROR);
}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating)
{
    if(userId <= 0 || movieId <= 0 || rating > 100 || rating < 0){
        return StatusType::INVALID_INPUT;
    }
    Node<group_node>* user = users.search(userId); // O(log(n))
    if(user->key == -1){
        delete user;
        return StatusType::FAILURE;
    }
    Node<group_node>* movie = movies.search(movieId); // O(log(k))
    if(movie->key == -1){
        delete movie;
        return StatusType::FAILURE;
    }
    if(movie->isVip && !user->isVip){
        return StatusType::FAILURE;
    }
    double oldRating = movie->rating;
    StatusType status = moviesRating.searchAndDeleteRating(oldRating,movie->views,movie->content);
    if(status != StatusType::SUCCESS){
        return status;
    }


    movie->rating*=movie->usersRated;
    movie->rating+=rating;
    movie->usersRated++;
    movie->rating/=movie->usersRated;

    Node<group_node>* curMovie2 = new Node<group_node>(0,movieId, nullptr);
    copyNodeContent(curMovie2,movie);

    StatusType status2 = moviesRating.searchAndAddRating(curMovie2);
    if(status != StatusType::SUCCESS){
        return status;
    }


    Node<group_node>* curMovie = new Node<group_node>(0,movieId, nullptr);
    copyNodeContent(curMovie,movie);
    switch (movie->genre) {
        case Genre::COMEDY:
            comedyMovies.searchAndDeleteRating(oldRating,movie->views,movie->content);
            comedyMovies.searchAndAddRating(curMovie);
            maxRatingComedyMovie = comedyMovies.getMax();
            break;
        case Genre::ACTION:
            actionMovies.searchAndDeleteRating(oldRating,movie->views,movie->content);
            actionMovies.searchAndAddRating(curMovie);
            maxRatingActionMovie = actionMovies.getMax();
            break;
        case Genre::FANTASY:
            fantasyMovies.searchAndDeleteRating(oldRating,movie->views,movie->content);
            fantasyMovies.searchAndAddRating(curMovie);
            maxRatingFantasyMovie = fantasyMovies.getMax();
            break;
        case Genre::DRAMA:
            dramaMovies.searchAndDeleteRating(oldRating,movie->views-1,movie->content);
            dramaMovies.searchAndAddRating(curMovie);
            maxRatingDramaMovie = dramaMovies.getMax();
            break;
        case Genre::NONE:
            break;
    }
    // still not finished
    return StatusType::SUCCESS;
}




output_t<int> streaming_database::get_group_recommendation(int groupId) // not finished
{
    if(groupId <= 0){
        return StatusType::INVALID_INPUT;
    }
    group_node* group = groups.search(groupId); // O(log(m))
    if(group->key == -1){
        delete group;
        return StatusType::FAILURE;
    }
    if(group->members.getNumOfNodes() == 0){
        return StatusType::FAILURE;
    }
    int groupFavorite = max_view_in_group(group->ActionViews,group->DramaViews,
                                          group->ComedyViews,group->FantasyViews);
    switch (groupFavorite) {
        case 0:
            if(comedyMovies.getNumOfNodes() == 0){
                return StatusType::FAILURE;
            }
            return maxRatingComedyMovie->content;
        case 1:
            if(dramaMovies.getNumOfNodes() == 0){
                return StatusType::FAILURE;
            }
            return maxRatingDramaMovie->content;
        case 2:
            if(actionMovies.getNumOfNodes()==0)
            {
                return StatusType::FAILURE;
            }
            return maxRatingActionMovie->content;
        case 3:
            if(fantasyMovies.getNumOfNodes()==0)
            {
                return StatusType::FAILURE;
            }
            return maxRatingFantasyMovie->content;
    }
    return StatusType::FAILURE;
}

void print(output_t<int> output){
    switch (output.status()) {
        case StatusType::FAILURE:
            std::cout << std::endl << "FAILURE";
            return;
        case StatusType::SUCCESS:
            std::cout << std::endl << "SUCCESS  value = " <<output.ans();
            return;
        case StatusType::ALLOCATION_ERROR:
            std::cout << std::endl << "ALLOCATION_ERROR";
            return;
        case StatusType::INVALID_INPUT:
            std::cout << std::endl << "INVALID_INPUT";
            return;
    }
}
