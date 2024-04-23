//Richard Matejka - 1221297844

#include "stdio.h"
#include "MM.h"

void printList(STORE *store, int count) {
    NODE *temp = store->head;
    for (int i = 0; i < count; i++) {
        if (temp != NULL) {
            fprintf(stdout, "%lf\n", temp->key);
            temp = temp->L;
        }
    }
}
