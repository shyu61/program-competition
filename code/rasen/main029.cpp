#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

struct Node {
    int key;
    Node *parent, *left, *right;
};

Node *root, *NIL;

void insert(int key) {
    Node *y = NIL;
    Node *x = root;
    Node *z;

    z = (Node *)malloc(sizeof(Node));
    z->key = key;
    z->left = NIL;
    z->right = NIL;
    while (x != NIL) {
        y = x;
        if (z->key < x->key) x = x->left;
        else x = x->right;
    }
    z->parent = y;

    if (y == NIL) root = z;
    else if (z->key < y->key) y->left = z;
    else y->right = z;
}

void preorder(Node *x) {
    if (x == NIL) return;
    cout << " " << x->key;
    preorder(x->left);
    preorder(x->right);
}

void inorder(Node *x) {
    if (x == NIL) return;
    inorder(x->left);
    cout << " " << x->key;
    inorder(x->right);
}

void print() {
    inorder(root);
    cout << endl;
    preorder(root);
    cout << endl;
}

int main() {
    int n;
    string com;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> com;
        if (com == "insert") {
            int k;
            cin >> k;
            insert(k);
        } else {
            print();
        }
    }
}
