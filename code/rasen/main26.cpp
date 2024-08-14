#include <iostream>
using namespace std;
const int MAX = 25;
const int NIL = -1;

struct Node {
    int parent, left, right;
};

Node A[MAX];

void preorder(int id) {
    if (id == NIL) return;
    cout << " " << id;
    preorder(A[id].left);
    preorder(A[id].right);
}

void inorder(int id) {
    if (id == NIL) return;
    inorder(A[id].left);
    cout << " " << id;
    inorder(A[id].right);
}

void postorder(int id) {
    if (id == NIL) return;
    postorder(A[id].left);
    postorder(A[id].right);
    cout << " " << id;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        A[i].parent = A[i].left = A[i].right = NIL;
    }
    for (int i = 0; i < n; i++) {
        int id, left, right;
        cin >> id >> left >> right;

        A[id].left = left;
        A[id].right = right;
        if (left != NIL) {
            A[left].parent = id;
        }
        if (right != NIL) {
            A[right].parent = id;
        }
    }

    int root_node_id;
    for (int i = 0; i < n; i++) {
        if (A[i].parent == NIL) {
            root_node_id = i;
            break;
        }
    }

    cout << "Preorder" << endl;
    preorder(root_node_id);
    cout << endl;

    cout << "Inorder" << endl;
    inorder(root_node_id);
    cout << endl;

    cout << "Postorder" << endl;
    postorder(root_node_id);
    cout << endl;
}