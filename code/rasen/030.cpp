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

int find(int key) {
    Node *x = root;

    while (x != NIL) {
        if (key == x->key) return 1;
        else if (key < x->key) x = x->left;
        else x = x->right;
    }
    return 0;
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
        if (com == "print") {
            print();
        } else {
            int k;
            cin >> k;
            if (com == "insert") insert(k);
            else {
            if (find(k)) cout << "yes" << endl;
            else cout << "no" << endl;
            }
        }
    }
}