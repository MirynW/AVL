#include <stdio.h>
#include <stdlib.h>
#include "avl.h"





int main(int argc, char* argv[]) {

	AVL tree = avl_init_tree();
	for (int i = 10; i >= 0; i--) {
		avl_insert(tree, i);
	}
	avl_preorder(tree);
	return 0;
}