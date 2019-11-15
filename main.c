#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "time.h"





int main(int argc, char* argv[]) {

	srand(time(0));
	AVL tree = avl_init_tree();
	avl_insert(tree, 10);
	avl_insert(tree, 19);
	avl_insert(tree, 50);
	avl_insert(tree, 100);
	avl_insert(tree, 110);
	avl_insert(tree, -10);
	avl_insert(tree, -100);
	for (int i = 0; i < 17; i++) {
		avl_insert(tree, i);
	}

	avl_preorder(tree);
	return 0;
}