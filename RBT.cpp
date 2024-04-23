//Richard Matejka - 1221297844

#include "stdio.h"
#include "cmath"
#include "RBT.h"

void preOrder(TREE *tree, int option, NODE *x, bool writing, FILE *fp) {
    const char* color_strings[] = {"RED", "BLACK"};
    if (option == 0) {
        if (x != tree->nill) {
            if (writing) {
                fprintf(fp, "%lf (%s)\n", x->key, color_strings[x->color]);
                preOrder(tree, option, x->L, true, fp);
                preOrder(tree, option, x->R, true, fp);
            }
            else {
                fprintf(stdout, "%lf (%s)\n", x->key, color_strings[x->color]);
                preOrder(tree, option, x->L, false, fp);
                preOrder(tree, option, x->R, false, fp); 
            }
        }
    }
    else {
        if (x != tree->nill) {
            fprintf(stdout, "%lf (%s)\n", x->key, color_strings[x->color]);
            preOrder(tree, option, x->L, false, fp);
            preOrder(tree, option, x->R, false, fp);
        }
        if (tree->root != tree->nill && x == tree->nill) {
            fprintf(stdout, "NULL\n");
        }
    }
}

void inOrder(TREE *tree, int option, NODE *x) {
    const char* color_strings[] = {"RED", "BLACK"};
    if (option == 0) {
        if (x != tree->nill) {
            inOrder(tree, option, x->L);
            if (x != tree->nill) {
                fprintf(stdout, "%10.2lf (%s)\n", x->key, color_strings[x->color]);
            }
            inOrder(tree, option, x->R);
        }
    }
    else {
        if (tree->root != tree->nill && x == tree->nill) {
            fprintf(stdout, "NULL\n");
        }
        if (x != tree->nill) {
            inOrder(tree, option, x->L);
            fprintf(stdout, "%10.2lf (%s)\n", x->key, color_strings[x->color]);
            inOrder(tree, option, x->R);
        }
    }
}

void postOrder(TREE *tree, int option, NODE *x) {
    const char* color_strings[] = {"RED", "BLACK"};
    if (option == 0) {
        if (x != tree->nill) {
            postOrder(tree, option, x->L);
            postOrder(tree, option, x->R);
            fprintf(stdout, "%10.2lf (%s)\n", x->key, color_strings[x->color]);
        }
    }
    else {
        if (x != tree->nill) {
            postOrder(tree, option, x->L);
            postOrder(tree, option, x->R);
            fprintf(stdout, "%10.2lf (%s)\n", x->key, color_strings[x->color]);
        }
        if (tree->root != tree->nill && x == tree->nill) {
            fprintf(stdout, "NULL\n");
        }
    }
}

NODE* rbtSearch(TREE *tree, double key, NODE *x) {
    if (x == tree->nill) {
        return NULL;
    }
    if (x == NULL || x->key == key) {
        return x;
    }
    if (key < x->key) {
        return rbtSearch(tree, key, x->L);
    }
    else {
        return rbtSearch(tree, key, x->R);
    }
}

NODE* rbtMaximum(TREE *tree, NODE *x) {
    while (x != NULL && x->R != tree->nill) {
        x = x->R;
    }
    return x;
}

NODE* rbtMinimum(TREE *tree, NODE *x) {
    while (x != NULL && x->L != tree->nill) {
        x = x->L;
    }
    return x;
}

void rbtLeftRotate(TREE *tree, NODE *x) {
    NODE *y = x->R;
    x->R = y->L;
    if (y->L != tree->nill) {
        y->L->P = x;
    }
    y->P = x->P;
    if (x->P == tree->nill) {
        tree->root = y;
    }
    else if (x == x->P->L) {
        x->P->L = y;
    }
    else {
        x->P->R = y;
    }
    y->L = x;
    x->P = y;
}

void rbtRightRotate(TREE *tree, NODE *x) {
    NODE *y = x->L;
    x->L = y->R;
    if (y->R != tree->nill) {
        y->R->P = x;
    }
    y->P = x->P;
    if (x->P == tree->nill) {
        tree->root = y;
    }
    else if (x == x->P->R) {
        x->P->R = y;
    }
    else {
        x->P->L = y;
    }
    y->R = x;
    x->P = y;
}

void rbtInsertFixup(TREE *tree, NODE *z) {
    NODE *y = tree->nill;
    while (z->P->color == RED) {
        if (z->P == z->P->P->L) {
            y = z->P->P->R;
            if (y->color == RED) {
                z->P->color = BLACK;
                y->color = BLACK;
                z->P->P->color = RED;
                z = z->P->P;
            }
            else {
                if (z == z->P->R) {
                    z = z->P;
                    rbtLeftRotate(tree, z);
                }
                z->P->color = BLACK;
                z->P->P->color = RED;
                rbtRightRotate(tree, z->P->P);
            }
        }
        else {
            y = z->P->P->L;
            if (y->color == RED) {
                z->P->color = BLACK;
                y->color = BLACK;
                z->P->P->color = RED;
                z = z->P->P;
            }
            else {
                if (z == z->P->L) {
                    z = z->P;
                    rbtRightRotate(tree, z);
                }
                z->P->color = BLACK;
                z->P->P->color = RED;
                rbtLeftRotate(tree, z->P->P);
            }
        }
    }
    tree->root->color = BLACK;
}

void rbtInsert(TREE *tree, NODE *z) {
    tree->size++;
    NODE *y = tree->nill;
    NODE *x = tree->root;
    while (x != tree->nill) {
        y = x;
        if (z->key < x->key) {
            x = x->L;
        }
        else {
            x = x->R;
        }
    }
    z->P = y;
    if (y == tree->nill) {
        tree->root = z;
    }
    else if (z->key < y->key) {
        y->L = z;
    }
    else {
        y->R = z;
    }
    z->L = tree->nill;
    z->R = tree->nill;
    z->color = RED;
    rbtInsertFixup(tree, z);
}

void rbtTransplant(TREE *tree, NODE *u, NODE *v) {
    if (tree->root == tree->nill || u == tree->nill) {
        return;
    }
    if (u->P == tree->nill) {
        tree->root = v;
    }
    else if (u == u->P->L) {
        u->P->L = v;
    }
    else {
        u->P->R = v;
    }
    v->P = u->P;
}

void rbtDeleteFixup(TREE *tree, NODE *x) {
    NODE *w = (NODE *) calloc(1, sizeof(NODE));
    while (x != tree->root && x->color == BLACK) {
        if (x == x->P->L) {
            w = x->P->R;
            if (w->color == RED) {
                w->color = BLACK;
                x->P->color = RED;
                rbtLeftRotate(tree, x->P);
                w = x->P->R;
            }
            if (w->L->color == BLACK && w->R->color == BLACK) {
                w->color = RED;
                x = x->P;
            }
            else {
                if (w->R->color == BLACK) {
                    w->L->color = BLACK;
                    w->color = RED;
                    rbtRightRotate(tree, w);
                    w = x->P->R;
                }
                w->color = x->P->color;
                x->P->color = BLACK;
                w->R->color = BLACK;
                rbtLeftRotate(tree, x->P);
                x = tree->root;
            }
        }
        else {
            w = x->P->L;
            if (w->color == RED) {
                w->color = BLACK;
                x->P->color = RED;
                rbtRightRotate(tree, x->P);
                w = x->P->L;
            }
            if (w->R->color == BLACK && w->L->color == BLACK) {
                w->color = RED;
                x = x->P;
            }
            else {
                if (w->L->color == BLACK) {
                    w->R->color = BLACK;
                    w->color = RED;
                    rbtLeftRotate(tree, w);
                    w = x->P->L;
                }
                w->color = x->P->color;
                x->P->color = BLACK;
                w->L->color = BLACK;
                rbtRightRotate(tree, x->P);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}

void rbtDelete(TREE *tree, NODE *z) {
    tree->size--;
    NODE *y = z;
    NODE *x = (NODE *) calloc(1, sizeof(NODE));
    Color original = y->color;
    if (z->L == tree->nill) {
        x = z->R;
        rbtTransplant(tree, z, z->R);
    }
    else if (z->R == tree->nill) {
        x = z->L;
        rbtTransplant(tree, z, z->L);
    }
    else {
        y = rbtMinimum(tree, z->R);
        original = y->color;
        x = y->R;
        if (y->P == z) {
            x->P = y;
        }
        else {
            rbtTransplant(tree, y, y->R);
            y->R = z->R;
            y->R->P = y;
        }
        rbtTransplant(tree, z , y);
        y->L = z->L;
        y->L->P = y;
        y->color = z->color;
    }
    if (original == BLACK) {
        rbtDeleteFixup(tree, x);
    }
    //free(z);
}