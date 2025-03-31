#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;

// エッジケースが難しい問題は、考慮する必要があるエッジケースを減らす実装を心がける
// テクニック
// - 前後の考慮はswapか絶対値を使う
// - ng条件を事前計算できるならしておく方が良い

int main() {
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        int n2 = n * 2;
        vector<int> a(n2);
        rep(i, n2) cin >> a[i], a[i]--;

        vector<int> nx(n2);
        {
            vector<int> pos(n2 + 1, -1);
            for (int i = n2 - 1; i >= 0; i--) {
                nx[i] = pos[a[i]];
                pos[a[i]] = i;
            }
        }

        vector<bool> ng(n);
        rep(i, n2 - 1) {
            if (a[i] == a[i + 1]) ng[a[i]] = true;
        }

        int ans = 0;
        rep(i, n2 - 1) {
            if (ng[a[i]] || ng[a[i + 1]]) continue;
            if (nx[i] == -1 || nx[i + 1] == -1) continue;
            if (abs(nx[i] - nx[i + 1]) == 1) ans++;
        }
        cout << ans << '\n';
    }
}
