#ifndef AVL_TREE_H
#define AVL_TREE_H
#include "generic_vector.h"
#include "my_string.h"

typedef void* AVL_TREE;


//pre:is given a valid generic vector
//post: returns a valid avl_tree handle, returns Null if failure
AVL_TREE avl_tree_init_default();

//pre: is past a valid handle to an avl tree, and is passed a vaild handle to 
// to a genric vector
//post: returns success if node is added to proper part of hTree, and
//hdata is succesfuly stored in node in proper location
//returns failure if there is memory issues
Status avl_tree_insert(AVL_TREE *phTree, MY_STRING new_key, MY_STRING word, int output);

//pre past a vailid tree MY_string key:
//post: returns address of largest node
AVL_TREE avl_get_largest_node(AVL_TREE hTree);

void avl_get_key_take_value(AVL_TREE hTree, MY_STRING *phKey, GENERIC_VECTOR *phVec);
//will destroy tree 
void avl_tree_destroy(AVL_TREE *phTree);

#endif

