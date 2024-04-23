//Richard Matejka - 1221297844

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "RBT.h"
#include "MM.h"


int main(int argc, char **argv){
    FILE *fp;
    STORE *store;
    TREE *tree;
    NODE *nill;
    double key;
    int returnV, n;
    char Word[100];
    char key2[100];

    if (argc != 1){
        fprintf(stderr, "Usage: %s\n", argv[0]);
        exit(0);
    }

    store = (STORE *) calloc(1, sizeof(STORE));
    if (!store) {
        fprintf(stderr, "Error: calloc failed\n");
        exit(0);
    }
    tree = (TREE *) calloc(1, sizeof(TREE));
    if (!tree) {
        fprintf(stderr, "Error: calloc failed\n");
        exit(0);
    }
    tree->size = 0;
    nill = (NODE *) calloc(1, sizeof(NODE));
    if (!nill) {
        fprintf(stderr, "Error: calloc failed\n");
        exit(0);
    }
    nill->color = BLACK;
    nill->L = NULL;
    nill->R = NULL;
    tree->nill = nill;
    tree->root = nill;

    while (1){
        returnV = nextInstruction(Word, &key, key2);

        if (returnV == 0) {
            fprintf(stderr, "Warning: Invalid instruction\n");
            continue;
        }

        if (strcmp(Word, "Stop")==0){
            return 0;
        }

        if (strcmp(Word, "PreOrder")==0){
            preOrder(tree, (int)key, tree->root, false, fp);
            continue;
        }

        if (strcmp(Word, "InOrder")==0){
            inOrder(tree, (int)key, tree->root);
            continue;
        }

        if (strcmp(Word, "PostOrder")==0){
            postOrder(tree, (int)key, tree->root);
            continue;
        }

        if (strcmp(Word, "Read")==0){
            if (tree->size > 0) {
                fprintf(stderr, "Error: Reading into non-empty tree\n");
                continue;
            }
            fp = fopen(key2, "r");
            if (!fp){
                fprintf(stdout, "Reading unsuccessful\n");
            }
            else {
                fscanf(fp, "%d", &n);
                for (int i = 0; i < n; i++) {
                    double keyi;
                    fscanf(fp, "%lf", &keyi);
                    NODE *z = (NODE *) calloc(1, sizeof(NODE));
                    z->key = keyi;
                    rbtInsert(tree, z);
                }
                fprintf(stdout, "Reading successful\n");
                fclose(fp);
            }
            continue;
        }
        
        if (strcmp(Word, "Write")==0){
            fp = fopen(key2, "w");
            if (!fp){
                fprintf(stdout, "Writing unsuccessful\n");
            }
            else {
                fprintf(fp, "%d\n", tree->size);
                preOrder(tree, 0, tree->root, true, fp);
                fprintf(stdout, "Writing successful\n");
                fclose(fp);
            }
            continue;
        }

        if (strcmp(Word, "Search")==0){
            if (rbtSearch(tree, key, tree->root) != NULL) {
                fprintf(stdout, "%lf found\n", key);
            }
            else {
                fprintf(stdout, "%lf not found\n", key);
            }
            continue;
        }

        if (strcmp(Word, "Insert")==0){
            if (rbtSearch(tree, key, tree->root) != NULL) {
                fprintf(stdout, "%lf already in tree, no insertion\n", key);
            }
            else {
                if (store->size == 0) {
                    NODE *z = (NODE *) calloc(1, sizeof(NODE));
                    z->key = key;
                    rbtInsert(tree, z);
                }
                else {
                    NODE *temp = store->head;
                    temp->key = key;
                    store->head = store->head->L;
                    store->size--;
                    temp->L = tree->nill;
                    temp->R = tree->nill;
                    rbtInsert(tree, temp);
                }
                fprintf(stdout, "%lf inserted\n", key);
            }
            continue;
        }

        if (strcmp(Word, "Maximum")==0){
            if (rbtMaximum(tree, tree->root) != NULL) {
                fprintf(stdout, "Maximum = %lf\n", rbtMaximum(tree, tree->root)->key);
            }
            continue;
        }

        if (strcmp(Word, "Minimum")==0){
            if (rbtMinimum(tree, tree->root) != NULL) {
                fprintf(stdout, "Minimum = %lf\n", rbtMinimum(tree, tree->root)->key);
            }
            continue;
        }

        if (strcmp(Word, "Delete")==0){
            NODE *z = rbtSearch(tree, key, tree->root);
            if (z == NULL) {
                fprintf(stdout, "%lf not in tree, no deletion\n", key);
            }
            else {
                rbtDelete(tree, z);
                NODE *temp = store->head;
                store->head = z;
                store->head->L = temp;
                store->size++;
                fprintf(stdout, "%lf deleted\n", key);
            }
            continue;
        }

        if (strcmp(Word, "PrintList")==0){
            fprintf(stdout, "Key values on local list:\n");
            printList(store, (int)key);
            continue;
        }
    }

    free(store);
    free(tree);
    free(nill);

    return 1;
}
