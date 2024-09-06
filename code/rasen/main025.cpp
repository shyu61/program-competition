#include <iostream>
using namespace std;
const int MAX = 25;
const int NIL = -1;

struct Node {
    int parent, left, right, sib, degree, depth, height;
};

Node A[MAX];

// loopや再帰呼び出しは、最初で弾くか、呼び出し時に弾くか
// 戻り値がある場合は呼び出し時に弾くほうが直感的で、ない場合はfor文などに倣って最初に弾くほうが良い。
void setDepth(int id, int d) {
    if (id == NIL) return;
    A[id].depth = d;
    setDepth(A[id].left, d + 1);
    setDepth(A[id].right, d + 1);
}

int setHeight(int id) {
    int h, h1 = 0, h2 = 0;
    if (A[id].left != NIL) {
        h1 = setHeight(A[id].left) + 1;
    }
    if (A[id].right != NIL) {
        h2 = setHeight(A[id].right) + 1;
    }
    h = max(h1, h2);
    A[id].height = h;
    return h;
}

void print(int i) {
    cout << "node " << i << ": ";
    cout << "parent = " << A[i].parent << ", ";
    cout << "sibling = " << A[i].sib << ", ";
    cout << "degree = " << A[i].degree << ", ";
    cout << "depth = " << A[i].depth << ", ";
    cout << "height = " << A[i].height << ", ";

    if (A[i].parent == NIL) {
        cout << "root";
    } else if (A[i].height == 0) {
        cout << "leaf";
    } else {
        cout << "internal node";
    }
    cout << endl;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        A[i].parent = A[i].right = A[i].left = A[i].sib = A[i].height = NIL;
    }
    for (int i = 0; i < n; i++) {
        int id, left, right;
        cin >> id >> left >> right;

        A[id].left = left;
        A[id].right = right;

        if (left != NIL) {
            A[id].degree++;
            A[left].parent = id;
            A[left].sib = right;
        }
        if (right != NIL) {
            A[id].degree++;
            A[right].parent = id;
            A[right].sib = left;
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
    setHeight(root_node_id);

    for (int i = 0; i < n; i++) {
        print(i);
    }
}