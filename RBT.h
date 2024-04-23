//Richard Matejka - 1221297844

#ifndef _RBT_h
#define _RBT_h 1
#include "data_structures.h"

void preOrder(TREE *, int, NODE *, bool, FILE *);
void inOrder(TREE *, int, NODE *);
void postOrder(TREE *, int, NODE *);

NODE* rbtSearch(TREE *, double, NODE *);
NODE* rbtMaximum(TREE *, NODE *);
NODE* rbtMinimum(TREE *, NODE *);

void rbtInsert(TREE *, NODE *);
void rbtInsertFixup(TREE *, NODE *);

void rbtLeftRotate(TREE *, NODE *);
void rbtRightRotate(TREE *, NODE *);

void rbtTransplant(TREE *, NODE *, NODE *);
void rbtDelete(TREE *, NODE *);
void rbtDeleteFixup(TREE *, NODE *);    

#endif
