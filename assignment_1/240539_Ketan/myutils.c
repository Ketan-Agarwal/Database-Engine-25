#include "myutils.h"



int find_key_index(Node* node, int key) {
    int i = 0;
    while (i < node->numKeys && node->keys[i].key < key) {
        i++;
    }
    return i;
}


char* search_node(Node* node, int key){
    if (!node) return NULL;
    int i = find_key_index(node, key);

    if (i < node->numKeys && node->keys[i].key == key) return node->keys[i].name;

    if (node->isLeaf){
        return NULL;
    }
    else {
        return search_node(node->children[i], key);
    }

}




void split_child(Node* parent, int idx) {
    Node* fullChild = parent->children[idx];
    Node* newChild = createNode(fullChild->isLeaf);

    int mid = ORDER / 2;
    keyvalue median = fullChild->keys[mid];

    newChild->numKeys = fullChild->numKeys - mid - 1;
    for (int i = 0; i < newChild->numKeys; i++) {
        newChild->keys[i] = fullChild->keys[mid + 1 + i];
    }

    if (!fullChild->isLeaf) {
        for (int i = 0; i <= newChild->numKeys; i++) {
            newChild->children[i] = fullChild->children[mid + 1 + i];
        }
    }

    fullChild->numKeys = mid;

    for (int i = parent->numKeys; i > idx; i--) {
        parent->keys[i] = parent->keys[i - 1];
        parent->children[i + 1] = parent->children[i];
    }

    parent->keys[idx] = median;
    parent->children[idx + 1] = newChild;
    parent->numKeys++;
}


void insert_nonfull(Node* node, int key, const char* name) {
    int i = node->numKeys - 1;

    if (node->isLeaf) {
        while (i >= 0 && key < node->keys[i].key) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1].key = key;
        strcpy(node->keys[i + 1].name, name);
        node->numKeys++;
    } else {
        while (i >= 0 && key < node->keys[i].key) {
            i--;
        }
        i++;

        if (node->children[i]->numKeys == ORDER - 1) {
            split_child(node, i);
            if (key > node->keys[i].key) i++;
        }
        insert_nonfull(node->children[i], key, name);
    }
}


void freeNode(Node *node){
    if (node!=NULL){
        if (!node->isLeaf){
            for (int i = 0; i <= node->numKeys; i++){
                freeNode(node->children[i]);
            }
        }
        free(node->keys);
        free(node->children);
        free(node);
    }
}


keyvalue get_pre(Node* node){
    while(!node->isLeaf){
        node = node->children[node->numKeys];
    }
    return node->keys[node->numKeys - 1];
}

keyvalue get_suc(Node* node){
    while (!node->isLeaf){
        node = node->children[0];
    }
    return node->keys[0];
}



void merge(Node* node, int idx){
    Node* l = node->children[idx];
    Node* r = node->children[idx+1];
    l->keys[l->numKeys] = node->keys[idx];                                        

    for (int i = 0; i < r->numKeys; i++){
        l->keys[i + l->numKeys + 1] = r->keys[i];
    }

    if (!l->isLeaf){
        for (int i = 0; i <= r->numKeys; i++){
            l->children[i + l->numKeys + 1] = r->children[i];
        }
    }

    for (int i = idx + 1; i < node->numKeys; i++){
        node->keys[i-1] = node->keys[i];
        node->children[i] = node->children[i+1];
    }

    l->numKeys += r->numKeys + 1;
    freeNode(r);
    node->numKeys--;
}



void borrow_from_left(Node* node, int idx){
    if (idx <= 0 || idx >= node->numKeys) return;
    Node* l = node->children[idx];
    Node* r = node->children[idx+1];

    for (int i = r->numKeys; i > 0; i--){
        r->keys[i] = r->keys[i-1];
    }
    if (!r->isLeaf){
        for (int i = r->numKeys+1; i > 0; i--){
            r->children[i] = r->children[i-1];
        }
    }

    r->keys[0] = node->keys[idx-1];
    
    if (!r->isLeaf){
        r->children[0] = l->children[l->numKeys];
    }

    node->keys[idx-1] = l->keys[l->numKeys-1];

    l->numKeys--;
    r->numKeys++;
}

void borrow_from_right(Node* node, int idx){
    if (idx < 0 || idx >= node->numKeys) return;
    Node* l = node->children[idx];
    Node* r = node->children[idx+1];

    l->keys[l->numKeys] = node->keys[idx];
    
    if (!l->isLeaf){
        l->children[l->numKeys+1] = r->children[0];
    }

    node->keys[idx] = r->keys[0];

    for (int i = 1; i < r->numKeys; i++){
        r->keys[i-1] = r->keys[i];
    }

    if (!r->isLeaf){
        for (int i = 1; i <= r->numKeys; i++ ){
            r->children[i-1] = r->children[i];
        }
    }

    r->numKeys--;
    l->numKeys++;
}



void enqueue(Queue* q, Node* node) {
    QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
    temp->data = node;
    temp->next = NULL;
    if (!q->rear) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

Node* dequeue(Queue* q) {
    if (!q->front) return NULL;
    QueueNode* temp = q->front;
    Node* node = temp->data;
    q->front = q->front->next;
    if (!q->front) q->rear = NULL;
    free(temp);
    return node;
}

int is_empty(Queue* q) {
    return (q->front == NULL);
}
