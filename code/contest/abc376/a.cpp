#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// ポイント
// 配列の前後比較系は番兵で対応する

int main() {
    int n, c; cin >> n >> c;
    vector<int> t(n);
    rep(i, n) cin >> t[i];
    int ans = 0, pre = -2000;
    rep(i, n) {
        if (t[i] - pre >= c) {
            ans++;
            pre = t[i];
        }
    }
    cout << ans << endl;
}
