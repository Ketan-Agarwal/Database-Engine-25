#ifndef UTILS_H
#define UTILS_H
#define ORDER 3

#include <stdlib.h>
#include <stdbool.h>


typedef struct keyvalue{
    int key;
    char name[100];
} keyvalue;
typedef struct Node Node;
typedef struct Node{
    keyvalue *keys ;
    Node **children ;
    int numKeys;
    bool isLeaf;
} Node;

typedef struct {
    Node* root;
} BTree;


typedef struct QueueNode {
    Node* data;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

#include "btree.h"
#include <string.h>

int find_key_index(Node* node, int key);
char* search_node(Node* node, int key);
void split_child(Node* parent, int idx);
void insert_nonfull(Node* node, int key, const char* name);
void freeNode(Node* node);
keyvalue get_pre(Node* node);
keyvalue get_suc(Node* node);
void merge(Node* node, int idx);
void borrow_from_left(Node* node, int idx);
void borrow_from_right(Node* node, int idx);
void enqueue(Queue* q, Node* node);
Node* dequeue(Queue* q);
int is_empty(Queue* q);





#endif