#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 方針
// 全探索

// ポイント
// 集合数が固定の全探索は、「残り」を考えることで全探索対象の集合を減らせる
// コイン問題で貪欲性が成立するのは、自身のコインより小さいコインで自身を必ず作ることができる場合である

int main() {
    vector<ll> coins(3);
    int n; cin >> n;
    rep(i, 3) cin >> coins[i];
    
    const int MAX = 10000;
    int ans = MAX;
    rep(i, MAX) rep(j, MAX - i) {
        ll now = n - i * coins[0] - j * coins[1];
        if (now < 0) break;
        if (now % coins[2] == 0) {
            ans = min(ans, int(i + j + now / coins[2]));
        }
    }
    cout << ans << endl;
}
