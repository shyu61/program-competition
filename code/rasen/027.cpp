#include <algorithm>
#include <iostream>
using namespace std;
const int MAX = 100;
const int NIL = -1;

struct Node {
    int left, right;
};

int n, A[MAX], B[MAX], pos = 0, cnt = 0;
Node C[MAX];

void solve(int left, int right) {
    int root = A[pos++];
    int mid = find(B, B + n, root) - B;

    if (left < mid) {
        C[root].left = A[pos];
        solve(left, mid);
    }
    if (mid + 1 < right) {
        C[root].right = A[pos];
        solve(mid + 1, right);
    }
}

void postorder(int id) {
    if (id == NIL) return;
    postorder(C[id].left);
    postorder(C[id].right);
    if (cnt > 0) cout << " ";
    cout << id;
    cnt++;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        C[i + 1].left = C[i + 1].right = NIL;
    }
    for (int i = 0; i < n; i++) {
        cin >> B[i];
    }
    solve(0, n);
    postorder(A[0]);
    cout << endl;
}
