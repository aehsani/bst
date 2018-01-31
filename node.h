#ifndef NODE_H
#define NODE_H

typedef struct {
    //Insert contained info here
} wrapper;

typedef struct Node {
    int key;
    wrapper *info;
    struct Node *lchild;
    struct Node *rchild;
    struct Node *parent;
    
} node;

typedef struct {
    node *head;
} tree;

#endif
