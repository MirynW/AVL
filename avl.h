#pragma once
#include <stdio.h>
#include <stdlib.h>


typedef void* AVL;

/*<----- PUBLIC FUNCTION SIGNATURES ----->*/
AVL avl_init_tree(void);

void avl_insert(AVL hAvl, int item);

void avl_preorder(AVL hAvl);