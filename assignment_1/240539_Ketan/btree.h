#ifndef BTREE_H
#define BTREE_H

#include <stdbool.h>
#include "myutils.h"


Node* createNode(bool isLeaf);
BTree* create_btree();
char* search(BTree* tree, int key);
Node* insert(BTree* tree, int key, const char* name);
void delete_key(Node* node, int key);
void level_order_traversal(Node* root);

#endif
