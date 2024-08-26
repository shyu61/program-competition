// bit全探索
// 部分和問題: p34
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // 全てのパターンを列挙
    for (int bit = 0; bit < (1 << n); bit++) {
        int sum = 0;
        // 列挙されたパターンの内、1が立っている場所だけ加算
        for (int i = 0; i < n; i++) {
            if (bit & (1 << i)) sum += a[i];
        }
        if (sum == k) {
            cout << 1 << endl;
            return 0;
        }
    }

    cout << 0 << endl;
}
