#ifndef BST_H
#define BST_H

#include "node.h"

tree *newtree();
void freewrapper(wrapper *w);
void freenodes(node *n);
void freetree(tree *n);
void delnode(node *n);
node *minnode(node *n);
void insert(tree *t, int k, wrapper *w);
void deletekey(tree *t, int k);
wrapper *getinfo(tree *t, int k);
void printnodes(node *n);
void printtree(tree *t);
void debugnode(node *n);
void debugtree(tree *t);

#endif
