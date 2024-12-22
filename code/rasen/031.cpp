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
    Node *z = (Node *)malloc(sizeof(Node));
    *z = { .key = key, .left = NIL, .right = NIL };
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

Node* find(int key) {
    Node *x = root;
    while (x != NIL) {
        if (key == x->key) return x;
        else if (key < x->key) x = x->left;
        else x = x->right;
    }
    return NIL;
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

Node* getMin(Node *x) {
    while (x->left != NIL) x = x->left;
    return x;
}

void treeDelete(Node *x) {
    // 子:0（leaf）の場合
    if (x->left == NIL && x->right == NIL) {
        if (x == x->parent->left) x->parent->left = NIL;
        else x->parent->right = NIL;
    }
    // 子:1つの場合
    else if (x->left == NIL || x->right == NIL) {
        Node *child;
        if (x->left != NIL) child = x->left;
        else child = x->right;

        child->parent = x->parent;
        if (x == x->parent->left) x->parent->left = child;
        else x->parent->right = child;
    }
    // 子:2つの場合
    else {
        Node *x_min = getMin(x->right);
        x->key = x_min->key;
        treeDelete(x_min);
        return;
    }

    free(x);
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
            else if (com == "find") {
                Node *x = find(k);
                if (x != NIL) cout << "yes" << endl;
                else cout << "no" << endl;
            } else {
                Node *x = find(k);
                treeDelete(x);
            }
        }
    }
}