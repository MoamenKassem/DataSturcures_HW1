// 
// 234218 Data Structures 1.
// Semester: 2023B (spring).
// Wet Exercise #1.
// 
// Recommended TAB size to view this file: 8.
// 
// The following main file is necessary to link and run your code.
// This file is READ ONLY: even if you submit something else, the compiler ..
// .. WILL use our file.
// 

#include "AVL_Tree.h"

int main()
{
    AVL_Tree avlTree;
    int arr[10]={10,5,12,3,9,11,13,14,2,4};
    for (int i = 0; i < 10; ++i) {
        avlTree.searchAndAdd(arr[i]);
        avlTree.printLevelOrder();
    }
}
