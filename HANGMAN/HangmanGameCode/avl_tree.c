#include "avl_tree.h"
#include "generic_vector.h"
#include "stdlib.h"
#include "my_string.h"

typedef struct node Node;

struct node {
	GENERIC_VECTOR data;
	MY_STRING key;
	Node *left;
	Node *right;
	int BF;
};

int avl_tree_balance(Node *pNode);
Status left_rotation(Node *pNode);
Status right_rotation(Node *pNode);

Node *make_node(MY_STRING new_key, MY_STRING word)
{
	Node *pNode = (Node *)malloc(sizeof(Node));
	if (pNode == NULL)
	{
		printf("ERROR: Failed to allocate space\n");
		return NULL;
	}
	pNode->data = generic_vector_init_default(my_string_assignment, my_string_destroy);
	if (pNode->data == NULL)
	{
		free(pNode);
		return NULL;
	}

	if (generic_vector_push_back(pNode->data, word) == FAILURE)
	{
		free(pNode);
		return NULL;
	}

	// if you want to be awful: pNode->left = pNode->right = NULL;
	pNode->left = NULL;
	pNode->right = NULL;

	pNode->key = new_key;
	pNode->BF = 0;
	return pNode;
}

AVL_TREE avl_tree_init_default()
{
	return NULL;
}

Status avl_tree_insert(AVL_TREE *phTree, MY_STRING new_key, MY_STRING word, int output)
{
	Node **ppNode = (Node **)phTree;
	Node *pNode = *ppNode;

	if (pNode == NULL)
	{
		*ppNode = make_node(new_key, word);
		if(output)
		{
			printf("%s\n", my_string_c_str(new_key));
		}
		return *ppNode == NULL ? FAILURE : SUCCESS;
	}

	int const compare = my_string_compare(new_key, pNode->key);
	if (compare < 0)
	{
		return avl_tree_insert((AVL_TREE *)(&pNode->left), new_key, word, output);
		//avl_tree_balance(pNode);
	}
	else if (compare > 0)
	{
		return avl_tree_insert((AVL_TREE *)(&pNode->right), new_key, word, output);
		//avl_tree_balance(pNode);
	}
	else
	{
		//node already exists, add word to the node's values
		if (pNode->data == NULL)
		{
			pNode->data = generic_vector_init_default(my_string_assignment, my_string_destroy);
			if (pNode->data == NULL)
			{
				return FAILURE;
			}
		}
		generic_vector_push_back(pNode->data, word);
		//no new node was created, so destroy the key
		my_string_destroy(&new_key);
		return SUCCESS;
	}
}

static void get_largest_node(Node *pNode, int *max_size, Node **max_node)
{
	if (pNode == NULL) {
		return;
	}

	int const size = generic_vector_get_size(pNode->data);
	if (*max_node == NULL || *max_size < size)
	{
		*max_size = size;
		*max_node = pNode;
	}

	get_largest_node(pNode->left, max_size, max_node);
	get_largest_node(pNode->right, max_size, max_node);
}

AVL_TREE avl_get_largest_node(AVL_TREE hTree) {
	Node *pNode = (Node *)hTree;
	Node *max_node = NULL;
	int max_size;

	get_largest_node(pNode, &max_size, &max_node);
	return max_node;
}

int my_max(int a, int b)
{
	if (a > b)
	{
		return a;
	}
	return b;
}

int tree_report_height(Node *root)
{
	if (root == NULL)
	{
		return 0;
	}
	else
	{
		return 1 + my_max(tree_report_height(root->left), tree_report_height(root->right));
	}
}


//needs to find bottom node then travel back up it unsureing everything is balanced
//so count must start at the bottom of recursion
int avl_tree_balance(Node *pRoot)
{

	int heightLeft = tree_report_height(pRoot->left);
	int heightRight = tree_report_height(pRoot->right);
	pRoot->BF = heightRight - heightLeft;

	if (pRoot->BF < -1)
	{
		right_rotation(pRoot);
	}
	else if (pRoot->BF > 1)
	{
		left_rotation(pRoot);
	}

	return 0;
}

Status left_rotation(Node *pNode)
{

	if (pNode->right != NULL)
	{
		if (pNode->right->BF < 0)
		{
			right_rotation(pNode->right);
		}
	}
	Status status = FAILURE;
	Node *temp1, *temp2, *orphan = NULL;
	temp1 = (Node *)malloc(sizeof(Node));
	if (temp1 != NULL)
	{
		//make a temp
		status = SUCCESS;
		temp1->BF = 0;
		temp1->data = pNode->data;
		temp1->left = pNode->left;
		temp1->right = pNode->right;
		temp1->key = pNode->key;

		//assign orphan if it exsits & cut it from tree
		if (pNode->right != NULL && pNode->right->left != NULL)
		{
			orphan = pNode->right->left;
			pNode->right->left = NULL;
		}

		//set right child as new parent 
		temp2 = pNode->right;
		if (temp2 != NULL)
		{
			pNode->data = pNode->right->data;
			pNode->key = pNode->right->key;
			pNode->right = pNode->right->right;

			free(temp2);
		}
		pNode->left = temp1;
		//re-assign orphan to the former parent
		temp1->right = orphan;

		//get new balance factor
		pNode->BF = 0;//fix
	}

	return status;
}

Status right_rotation(Node *pNode)
{
	if (pNode->left != NULL)
	{
		if (pNode->left->BF > 0)
		{
			left_rotation(pNode->left);
		}
	}
	Status status = FAILURE;
	Node *temp1, *temp2, *orphan = NULL;
	temp1 = (Node *)malloc(sizeof(Node));
	if (temp1 != NULL)
	{
		//make a temp
		status = SUCCESS;
		temp1->BF = 0;
		temp1->data = pNode->data;
		temp1->left = pNode->left;
		temp1->right = pNode->right;
		temp1->key = pNode->key;

		//assign orphan if it exsits & cut it from tree
		if (pNode->left != NULL && pNode->left->right != NULL)
		{
			orphan = pNode->left->right;
			pNode->left->right = NULL;
		}

		//set left child as new parent 
		temp2 = pNode->left;
		if (temp2 != NULL)
		{
			pNode->data = pNode->left->data;
			pNode->key = pNode->left->key;
			pNode->left = pNode->left->left;
			pNode->right = temp1;
			free(temp2);
		}

		//re-assign orphan to the former parent
		temp1->left = orphan;

		//get new balance factor
		pNode->BF = 0;//fix
	}

	return status;
}

GENERIC_VECTOR avl_tree_swap_destroy(MY_STRING *current_word_family, AVL_TREE key_closet, AVL_TREE next_vector)
{
	int i;
	Node *pTree = (Node *)next_vector;
	MY_STRING temp;
	GENERIC_VECTOR newVector = generic_vector_init_default(my_string_assignment, my_string_destroy);
	MY_STRING new_key = my_string_init_default();
	
	my_string_assignment(current_word_family, pTree->key);

	for (i = 0; i < generic_vector_get_size(pTree->data); i++)
	{
		generic_vector_push_back(newVector, *(generic_vector_at(pTree->data, i)));
	}


	avl_tree_destroy(key_closet);

	return newVector;
}

void avl_get_key_take_value(AVL_TREE hTree, MY_STRING *phKey, GENERIC_VECTOR *phVec)
{
	Node *pNode = (Node *)hTree;
	my_string_assignment(phKey, pNode->key);
	*phVec = pNode->data;
	pNode->data = NULL;
}

static void destroy_nodes(Node *pNode) {
	if (pNode == NULL)
	{
		return;
	}
	
	destroy_nodes(pNode->left);
	destroy_nodes(pNode->right);

	generic_vector_destroy(&(pNode->data));
	my_string_destroy(&(pNode->key));

	free(pNode);
}

void avl_tree_destroy(AVL_TREE *phTree)
{
	Node *pNode = (Node *)*phTree;

	destroy_nodes(pNode);
	*phTree = NULL;
}
