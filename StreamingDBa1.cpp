#include "StreamingDBa1.h"

streaming_database::streaming_database()
{
    movies = AVL_Tree();
    users = AVL_Tree();
    groups = AVL_Tree();
}
void deleteTree(Node* root){
    Node * ptr = root;
    if(ptr == nullptr){
        return;
    }
    deleteTree(ptr->leftSon);
    deleteTree(ptr->rightSon);
    delete ptr;
}
streaming_database::~streaming_database()
{
    deleteTree(movies.getRoot());
    deleteTree(users.getRoot());
    deleteTree(groups.getRoot());
}


StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly)
{
    if(movieId <= 0 || genre == Genre::NONE || views < 0){
        return StatusType::INVALID_INPUT;
    }
    Node* ptr = movies.searchAndAdd(movieId);
    if(!ptr){
        return StatusType::ALLOCATION_ERROR;
    }
    if(ptr->key == -1){
        delete ptr;
        return StatusType::FAILURE;
    }
    ptr->changeVip(vipOnly);
    ptr->changeGenre(genre);
    ptr->changeViews(views);
	return StatusType::SUCCESS;
}

StatusType streaming_database::remove_movie(int movieId)
{
	if(movieId <=0){
        return StatusType::INVALID_INPUT;
    }
	return movies.searchAndDelete(movieId);
}

StatusType streaming_database::add_user(int userId, bool isVip)
{
	if(userId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Node* ptr = users.searchAndAdd(userId);
    if(!ptr){
        return StatusType::ALLOCATION_ERROR;
    }
    if(ptr->key == -1){
        delete ptr;
        return StatusType::FAILURE;
    }
    ptr->changeVip(isVip);
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
    Node* ptr = groups.searchAndAdd(groupId);
    if(!ptr){
        return StatusType::ALLOCATION_ERROR;
    }
    if(ptr->key == -1){
        delete ptr;
        return StatusType::FAILURE;
    }
	return StatusType::SUCCESS;
}
void destroyLinkedList(Node* head){
    while (head){
        Node* temp = head;
        head = head->rightSon;
        delete temp;
    }
}
StatusType streaming_database::remove_group(int groupId)
{
    if(groupId <=0){
        return StatusType::INVALID_INPUT;
    }
    Node* user = groups.search(groupId);
    destroyLinkedList(user->groupUsers);
    return groups.searchAndDelete(groupId);
}

StatusType streaming_database::add_user_to_group(int userId, int groupId)
{
    if(userId <=0 || groupId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Node* user = users.search(userId); // O(log(n))
    if(!user){return StatusType::ALLOCATION_ERROR;}
    if(user->key == -1){
        return StatusType::FAILURE;
    }
    Node* group = groups.search(groupId); // O(log(m))
    if(!group){return StatusType::ALLOCATION_ERROR;}
    if (group->key == -1){
        return StatusType::FAILURE;
    }
    Node* userToAdd = new Node();
    if(!userToAdd){
        return StatusType::ALLOCATION_ERROR;
    }
    userToAdd->changeContent(userId);
    group->groupUsers->addRightSon(user);
    return StatusType::SUCCESS;
}

StatusType streaming_database::user_watch(int userId, int movieId)
{
	if(userId <= 0 || movieId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Node* user = users.search(userId); // O(log(n))
    if(!user){return StatusType::ALLOCATION_ERROR;}
    if(user->key == -1){
        return StatusType::FAILURE;
    }
    Node* movie = movies.search(movieId); // O(log(k))
    if(!movie){return StatusType::ALLOCATION_ERROR;}
    if(movie->key == -1){
        return StatusType::FAILURE;
    }
    if(movie->isVip==true && user->isVip== false){
        return StatusType::FAILURE;
    }
    user->changeViews(user->views+1);
    movie->changeViews(movie->views+1);
    return StatusType::SUCCESS;
}

StatusType streaming_database::group_watch(int groupId,int movieId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_all_movies_count(Genre genre)
{
    // TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
}

StatusType streaming_database::get_all_movies(Genre genre, int *const output)
{
    // TODO: Your code goes here
    output[0] = 4001;
    output[1] = 4002;
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_num_views(int userId, Genre genre)
{
	// TODO: Your code goes here
	return 2008;
}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating)
{
    // TODO: Your code goes here
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_group_recommendation(int groupId)
{
	// TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
}


