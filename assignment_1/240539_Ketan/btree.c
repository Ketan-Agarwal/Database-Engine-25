
#include <stdio.h>
#include <stdlib.h>
#include "btree.h"
#include <stdbool.h>

Node *createNode(bool isLeaf){
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->keys = (keyvalue *)malloc(ORDER * sizeof(keyvalue)); 
    newNode->children = (Node **)malloc((ORDER+1)* sizeof(Node *));
    newNode->numKeys = 0;
    newNode->isLeaf = isLeaf;
    return newNode;
}


BTree* create_btree() {
    BTree* tree = malloc(sizeof(BTree));
    tree->root = createNode(1);
    return tree;
}


char* search(BTree* tree, int key){
    if (!tree || !tree->root) return NULL;
    return search_node(tree->root, key);
}

Node* insert(BTree* tree, int key, const char* name) {
    Node* root = tree->root;

    if (root->numKeys == ORDER - 1) {
        Node* newRoot = createNode(false);
        newRoot->children[0] = root;
        split_child(newRoot, 0);
        insert_nonfull(newRoot, key, name);
        tree->root = newRoot;
        return newRoot;
    } else {
        insert_nonfull(root, key, name);
        return root;
    }
}


void delete_key(Node* node, int key) {
    int idx = find_key_index(node, key);

    if (idx < node->numKeys && node->keys[idx].key == key) {
        if (node->isLeaf) {
            
            for (int i = idx; i < node->numKeys - 1; i++) {
                node->keys[i] = node->keys[i + 1];
            }
            node->numKeys--;
        } else {
            
            Node* left = node->children[idx];
            Node* right = node->children[idx + 1];
            int minKeys = (ORDER + 1) / 2 - 1;

            if (left->numKeys > minKeys) {
                keyvalue pred = get_pre(left);
                node->keys[idx] = pred;
                delete_key(left, pred.key);
            } else if (right->numKeys > minKeys) {
                keyvalue succ = get_suc(right);
                node->keys[idx] = succ;
                delete_key(right, succ.key);
            } else {
                merge(node, idx);
                delete_key(left, key);
            }
        }
    }

    else {
        if (node->isLeaf) return;

        Node* child = node->children[idx];
        int minKeys = (ORDER + 1) / 2 - 1;

        if (child->numKeys == minKeys) {
            Node* left = (idx > 0) ? node->children[idx - 1] : NULL;
            Node* right = (idx < node->numKeys) ? node->children[idx + 1] : NULL;

            if (left && left->numKeys > minKeys) {
                borrow_from_left(node, idx);
            } else if (right && right->numKeys > minKeys) {
                borrow_from_right(node, idx);
            } else {
                if (right) {
                    merge(node, idx);
                    child = node->children[idx];
                } else {
                    merge(node, idx - 1);
                    child = node->children[idx - 1];
                }
            }
        }

        delete_key(child, key);
    }
}



void level_order_traversal(Node* root) {
    if (!root) return;

    Queue q = {NULL, NULL};
    enqueue(&q, root);
    enqueue(&q, NULL);

    while (!is_empty(&q)) {
        Node* curr = dequeue(&q);

        if (curr == NULL) {
            printf("\n");
            if (!is_empty(&q)) enqueue(&q, NULL);
            continue;
        }

        printf("[");
        for (int i = 0; i < curr->numKeys; i++) {
            printf("[%d, %s]", curr->keys[i].key, curr->keys[i].name);
            if (i < curr->numKeys - 1) printf(" ");
        }
        printf("]     ");

        if (!curr->isLeaf) {
            for (int i = 0; i <= curr->numKeys; i++) {
                enqueue(&q, curr->children[i]);
            }
        }
    }
}