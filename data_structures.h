//Richard Matejka - 1221297844

#ifndef _data_structures_h
#define _data_structures_h 1

enum Color {RED, BLACK};

typedef struct TAG_NODE{
    double key;
    Color color;
    struct TAG_NODE *P;
    struct TAG_NODE *L;
    struct TAG_NODE *R;
}NODE;

typedef struct TAG_RBT{
    int size;
    struct TAG_NODE *root;
    struct TAG_NODE* nill;
}TREE;

typedef struct TAG_STORE{
    int size;
    struct TAG_NODE *head;
}STORE;

#endif
