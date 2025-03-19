// bit全探索
// 部分和問題: p34
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    // 全てのパターンを列挙
    int n2 = 1 << n;
    rep(s, n2) {
        int sum = 0;
        rep(i, n) {
            if (s >> i & 1) sum += a[i];
        }
        if (sum == k) {
            cout << 1 << endl;
            return 0;
        }
    }

    cout << 0 << endl;
}
