#include <cstring>
#include <iostream>
using namespace std;
const int MAX = 100000;
const int NIL = -1;

struct Node {
    int parent, left, right, d, k;
};

Node A[MAX];

void setDepth(int id, int d) {
    A[id].d = d;
    if (A[id].right != NIL) {
        setDepth(A[id].right, d);
    }
    if (A[id].left != NIL) {
        setDepth(A[id].left, d + 1);
    }
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        A[i].parent = A[i].right = A[i].left = NIL;
    }
    for (int i = 0; i < n; i++) {
        int id;
        cin >> id >> A[id].k;

        int prev;
        for (int j = 0; j < A[id].k; j++) {
            int c;
            cin >> c;
            if (j == 0) {
                A[id].left = c;
            } else {
                A[prev].right = c;
            }
            A[c].parent = id;
            prev = c;
        }
    }

    int root_node_id;
    for (int i = 0; i < n; i++) {
        if (A[i].parent == NIL) {
            root_node_id = i;
            break;
        }
    }

    setDepth(root_node_id, 0);

    for (int i = 0; i < n; i++) {
        cout << "node " << i << ": ";
        cout << "parent = " << A[i].parent << ", ";
        cout << "depth = " << A[i].d << ", ";
        if (A[i].d == 0) {
            cout << "root, [";
        } else if (A[i].k == 0) {
            cout << "leaf, [";
        } else {
            cout << "internal node, [";
        }

        int id = A[i].left;
        for (int j = 0; j < A[i].k; j++) {
            if (j == 0) {
                cout << id;
            } else {
                id = A[id].right;
                cout << ", " << id;
            }
        }
        cout << "]" << endl;
    }
}