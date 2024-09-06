#include <algorithm>
#include <iostream>
using namespace std;
const int MAX = 100;

struct Node {
    int left, right;
};

int n, A[MAX], B[MAX], pos = 0, cnt = 0;

void solve(int left, int right) {
    if (left >= right) return;
    int root = A[pos++];
    int mid = find(B, B + n, root) - B;
    // 左部分木
    solve(left, mid);
    // 右部分木
    solve(mid + 1, right);
    if (cnt > 0) cout << " ";
    cout << root;
    cnt++;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> B[i];
    }
    solve(0, n);
    cout << endl;
}
