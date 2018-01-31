#include <stdlib.h>
#include <stdio.h>
#include "bst.h"


int main() {
    wrapper *x;
    printf("hello from main\n");
    tree *t = newtree();
    int A[] = {15, 13, 30, 17, 32, 18};

    for (int j = 0; j < 6; j++) {
        x = (wrapper *) malloc(sizeof(wrapper));
        insert(t, A[j], x);
        printf("Inserting %d\n",A[j]);
    }
    printtree(t);
    freetree(t);
    return 0;
}

