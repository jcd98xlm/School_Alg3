#ifndef __AVL__
#define __AVL__

//Definiçoes de tipos
struct avl_node
{
	int value;
	struct avl_node *left;
	struct avl_node *right;
};

typedef struct avl_node avl_node; 

//Prototipos das funçoes
void avl_initialization(avl_node *root);
avl_node *create_node(int key);
avl_node *avl_insert(avl_node *node, int key);
avl_node *avl_delete(avl_node *node, int key);
void preorder(avl_node *node);
int calculate_height(avl_node *node);
int calculate_height_inverse(avl_node *node, avl_node *current);
int max(int x, int y);
avl_node *rotate_right(avl_node *node);
avl_node *rotate_left(avl_node *node);
int calculate_balancing_factor(avl_node *node);
avl_node *predecessor(avl_node *node);
avl_node *avl_search(avl_node *node, int key);
void avl_free(avl_node *node);

#endif
