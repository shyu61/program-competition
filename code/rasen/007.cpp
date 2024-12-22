#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

struct Node {
    int key;
    Node *prev, *next;
};

Node *nil;

void init() {
    nil = (Node *)malloc(sizeof(Node));
    nil->prev = nil;
    nil->next = nil;
}

void insert(int key) {
    Node *x = (Node *)malloc(sizeof(Node));
    x->key = key;
    x->next = nil->next;
    nil->next->prev = x;
    nil->next = x;
    x->prev = nil;
}

Node* listSearch(int key) {
    Node* cur = nil->next;
    while (cur != nil && cur->key != key) {
        cur = cur->next;
    }
    return cur;
}

void deleteNode(Node *node) {
    if (node == nil) return;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
}

void deleteKey(int key) {
    deleteNode(listSearch(key));
}

void deleteFirst() {
    deleteNode(nil->next);
}

void deleteLast() {
    deleteNode(nil->prev);
}

int main() {
    init();

    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        char fn[20];
        int key = -1;
        scanf("%s%d", fn, &key);

        if (fn[0] == 'i') {
            insert(key);
        } else if (strlen(fn) == 6) {
            deleteKey(key);
        } else if (fn[6] == 'F') {
            deleteFirst();
        } else if (fn[6] == 'L') {
            deleteLast();
        }
    }

    bool is_first = true;
    Node* cur = nil->next;
    while (cur != nil) {
        if (is_first) {
            cout << cur->key;
        } else {
            cout << " " << cur->key;
        }
        is_first = false;
        cur = cur->next;
    }
    cout << endl;

    return 0;
}