#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 10000;
int A[MAX_N];
vector<int> B[MAX_N];

void unite(int x, int y) {
    // グループ番号の取得
    int a = A[x]; int b = A[y];
    int ming, maxg;
    if (a == b) return;
    else if (a > b) { ming = b; maxg = a; }
    else if (a < b) { ming = a; maxg = b; }

    // グループ番号が大きい方を、小さい方に統合する
    vector<int> vecmax = B[maxg];
    for (int i : vecmax) {
        A[i] = ming;
        B[ming].push_back(i);
    }
}

void same(int x, int y) {
    cout << (A[x] == A[y]) << endl;
}

int main() {
    int n, q; cin >> n >> q;
    for (int i = 0; i < n; i++) {
        A[i] = i;
        B[i] = vector<int>{i};
    }
    for (int i = 0; i < q; i++) {
        int com, x, y; cin >> com >> x >> y;
        if (com == 0) unite(x, y);
        else same(x, y);
    }
}