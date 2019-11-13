#include "avl.h"

typedef struct node Node;
typedef struct tree Tree;
struct node {
	int data;
	int balance_factor;
	int height;
	Node* left;
	Node* right;
};
struct tree {
	Node* root;
};

// Private Function Declarations
Node* init_node(int data);
void recur_insert(Node** n, int i);
void recur_preorder(Node* n);
void ll_rotate(Node** n);
void rr_rotate(Node** n);
int get_balance(Node* n);
int get_height(Node* n);
// max is already predefined as a macro apparently -> may need to create max macro on linux.


/*<----- PUBLIC FUNCTIONS ----->*/
AVL avl_init_tree() {
	Tree* new_tree = (Tree*)malloc(sizeof(Tree));
	if (new_tree == NULL) {
		printf("Memory Error During Allocation\n");
		return NULL;
	}
	new_tree->root = NULL;
	return new_tree;
}

// Insert
void avl_insert(AVL hAvl, int item) {
	Tree* pTree = (Tree*)hAvl;
	recur_insert(&(pTree->root), item);
}

// Traversals
void avl_preorder(AVL hAvl) {
	Tree* pTree = (Tree*)hAvl;
	recur_preorder(pTree->root);
}



/*<----- PRIVATE FUNCTIONS ----->*/
Node* init_node(int data) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	if (new_node == NULL) {
		printf("Memory Error\n");
		return NULL;
	}
	new_node->balance_factor = 0;
	new_node->data = data;
	new_node->height = 0;
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}

void recur_insert(Node** n, int i) {
	if ((*n) == NULL) {
		(*n) = init_node(i);
		if ((*n) == NULL)
			printf("Tree Insertion Failed Due To Failed Memory Allocation\n");
		return;
	}
	else if ((*n)->data > i) {
		(*n)->balance_factor--;
		recur_insert(&(*n)->left, i);
	}
	else if ((*n)->data < i) {
		(*n)->balance_factor++;
		recur_insert(&(*n)->right, i);
		puts("Here");
	}
	else
		return;

	// Set height of current node
	(*n)->height = max(get_height((*n)->left), get_height((*n)->right))+1;
	// Get balance of current node
	(*n)->balance_factor = get_balance((*n));

	// Determine rotations needed for current node if rebalance is necessary ****ISSUE WITH LOST NODES IN REBALANCE -> Need a dynamic way of getting node height & balance
	if ((*n)->balance_factor > 1 && i > (*n)->right->data) {
		// LL
		ll_rotate(&(*n));
		//(*n)->balance_factor = 0;
	}
	else if ((*n)->balance_factor < -1 && i < (*n)->left->data) {
		// RR
		rr_rotate(&(*n));
		//(*n)->balance_factor = 0;
	}
	else if ((*n)->balance_factor < -1 && i >(*n)->left->data) {
		// LR
		ll_rotate(&(*n)->left);
		rr_rotate(&(*n));
		//(*n)->balance_factor = 0;
	}
	else if ((*n)->balance_factor > 1 && i < (*n)->right->data) {
		// RL
		rr_rotate(&(*n)->right);
		ll_rotate(&(*n));
		//(*n)->balance_factor = 0;
	}
}

void recur_preorder(Node* n) {
	if (n != NULL) {
		printf("Data: %d\tBalance Factor: %d\n", n->data, n->balance_factor);
		recur_preorder(n->left);
		recur_preorder(n->right);
	}
}

void ll_rotate(Node** n) {
	Node* temp_root = (*n);
	(*n) = (*n)->right;
	temp_root->right = NULL;
	(*n)->left = temp_root;
	(*n)->height = max(get_height((*n)->left), get_height((*n)->right)) + 1;
	(*n)->left->height = max(get_height((*n)->left), get_height((*n)->right)) + 1;

}

void rr_rotate(Node** n) {
	Node* temp_root = (*n);
	(*n) = (*n)->left;
	temp_root->left = NULL;
	(*n)->right = temp_root;
	(*n)->height = max(get_height((*n)->left), get_height((*n)->right)) + 1;
	(*n)->right->height = max(get_height((*n)->left), get_height((*n)->right)) + 1;
}

int get_balance(Node* n) {
	if (n == NULL)
		return 0;
	return get_height(n->right) - get_height(n->left);
}

int get_height(Node* n) {
	if (n == NULL)
		return 0;
	return n->height;
}