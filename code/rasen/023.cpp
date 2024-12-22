#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
const int MAX = 100000;

struct Node {
    int p, d, k;
    vector<int> c;
};

int n;
Node A[MAX];

int getDepth(int id) {
    int d = 0;
    while (id != -1) {
        if (A[id].d == -1) {
            id = A[id].p;
            d++;
        } else {
            d += A[id].d;
            break;
        }
    }
    return d;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        A[i].p = A[i].d = -1;
    }
    for (int i = 0; i < n; i++) {
        int id, k;
        cin >> id >> k;
        A[id].k = k;
        for (int j = 0; j < A[id].k; j++) {
            int c;
            cin >> c;
            A[id].c.push_back(c);

            A[c].p = id;
        }
    }

    for (int i = 0; i < n; i++) {
        if (A[i].p == -1) {
            A[i].d = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        if (A[i].d == -1) {
            A[i].d = getDepth(i);
        }
    }

    for (int i = 0; i < n; i++) {
        cout << "node " << i << ": ";
        cout << "parent = " << A[i].p << ", ";
        cout << "depth = " << A[i].d << ", ";
        if (A[i].d == 0) {
            cout << "root, [";
        } else if (A[i].k == 0) {
            cout << "leaf, [";
        } else {
            cout << "internal node, [";
        }
        for (int j = 0; j < A[i].k; j++) {
            if (j > 0) cout << ", ";
            cout << A[i].c[j];
        }
        cout << "]" << endl;
    }
}