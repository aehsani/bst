#include <stdio.h>
#include <stdlib.h>
#include "node.h"

//Returns a new tree
tree *newtree() {
    tree *t;
    t = (tree *) malloc(sizeof(tree));
    if (!t) {
        printf("Error allocating memory\n");
        return NULL;
    }
    t->head = NULL;
    return t;
}

//Frees wrapper and all content stored in wrapper
void freewrapper(wrapper *w) {
    if (!w)
        return;
    //free all content stored in the wrapper
    free(w);
}

//Recursive function to free nodes in the tree
void freenodes(node *n) {
    if (n->lchild)
        freenodes(n->lchild);
    if (n->rchild)
        freenodes(n->rchild);
    freewrapper(n->info);
    free(n);
}

//Frees the tree memory and calls freenodes
void freetree(tree *t) {
    if (!t)
        return;
    if (t->head) {
        freenodes(t->head);
        free(t);
    }
}

//Removes and frees a node from a tree
void delnode(node *n) {
    if (n->lchild || n->rchild) {
        printf("Won't delete node - has children\n");
    }
    else {
        freewrapper(n->info);
        free(n);
    }
}

//Returns a pointer to a node with the minimum key in a subtree
node *minnode(node *curr) {
    while (curr->lchild)
        curr = curr->lchild;
    return curr;
}

//Creates a new node given a key and wrapper and inserts it
void insert(tree *t, int k, wrapper *w) {
    node *n, *curr;
    n = (node *) malloc(sizeof(node));
    n->key = k;
    n->lchild = NULL;
    n->rchild = NULL;
    n->parent = NULL;
    n->info = w;
    if (!t->head)
        t->head = n;
    else {
        curr = t->head;
        while (1) {
            if (k < curr->key && curr->lchild)
                curr = curr->lchild;
            else if (k > curr->key && curr->rchild)
                curr = curr->rchild;
            else
                break;
        }
        if (k < curr->key) {
            curr->lchild = n;
            n->parent = curr;
        }
        else if (k > curr->key) {
            curr->rchild = n;
            n->parent = curr;
        }
        else {
            wrapper *old;
            old = curr->info;
            curr->info = w;
            freewrapper(old);
        }
    }
}

//Removes node with a specified key and changes structure
void deletekey(tree *t, int k) {
    if (!t->head)
        return;
    node *curr, *oldnode;
    wrapper *oldwrap;
    curr = t->head;
    while (1) {
        if (curr->key == k) {
            if (curr->lchild && curr->rchild) {
                oldnode = minnode(curr->rchild);
                if (oldnode->key < oldnode->parent->key) {
                    oldnode->parent->lchild = oldnode->rchild;
                }
                else {
                    oldnode->parent->rchild = oldnode->rchild;
                }
                if (oldnode->rchild)
                    oldnode->rchild->parent = oldnode->parent;
                curr->info = oldnode->info;
                curr->key = oldnode->key;
                oldnode->lchild = NULL;
                oldnode->rchild = NULL;
                delnode(oldnode);
            }
            else if (!curr->lchild && !curr->rchild) {
                if (curr->parent) {
                    if (curr->parent->key > curr->key)
                        curr->parent->lchild = NULL;
                    else
                        curr->parent->rchild = NULL;
                }
                else {
                    t->head = NULL;
                }
                delnode(curr);
            }
            else {
                if (curr->lchild)
                    oldnode = curr->lchild;
                else
                    oldnode = curr->rchild;
                curr->key = oldnode->key;
                curr->info = oldnode->info;
                curr->lchild = oldnode->lchild;
                curr->rchild = oldnode->rchild;
                if (curr->lchild)
                    curr->lchild->parent = curr;
                if (curr->rchild)
                    curr->rchild->parent = curr;
                oldnode->lchild = NULL;
                oldnode->rchild = NULL;
                delnode(oldnode);
            }
            break;
        }
        else if (k < curr->key && curr->lchild)
            curr = curr->lchild;
        else if (k > curr->key && curr->rchild)
            curr = curr->rchild;
        else
            break;
    }
}


//Returns the info container in a tree if a given key
//is in the tree
wrapper *getinfo(tree *t, int k) {
    if (!t->head)
        return NULL;
    node *curr;
    curr = t->head;
    while (1) {
        if (curr->key == k)
            return curr->info;
        else if (k < curr->key && curr->lchild)
            curr = curr->lchild;
        else if (k > curr->key && curr->rchild)
            curr = curr->rchild;
        else
            break;
    }
    return NULL;
}

//Prints keys of the nodes
void printnodes(node *n) {
    if (n->lchild)
        printnodes(n->lchild);
    printf("%d ", n->key);
    if (n->rchild)
        printnodes(n->rchild);
}

//Calls printnodes to print the Tree
void printtree(tree *t) {
    if (!t->head)
        printf("Empty Tree");
    else
        printnodes(t->head);
    printf("\n");
}

//Recursively prints summary of stored pointers in nodes
void debugnode(node *n) {
    printf("Key: %d\n", n->key);
    if (n->lchild)
        printf("Lchild: %d\t", n->lchild->key);
    else
        printf("No lchild\t");
    if (n->rchild)
        printf("Rchild: %d\t", n->rchild->key);
    else
        printf("No rchild\t");
    if (n->parent)
        printf("Parent: %d\t", n->parent->key);
    else
        printf("No parent\t");
    printf("\n");
    if (n->lchild)
        debugnode(n->lchild);
    if (n->rchild)
        debugnode(n->rchild);

}

//Prints detailed summary of tree
void debugtree(tree *t) { 
    if (!t->head) 
        puts("Empty Tree");
    else
        debugnode(t->head);
    printf("\n");
}

