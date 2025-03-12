#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 想定解
// 閉路のみのfunctionalグラフに気付くこと
// ダブリング + 周期性 + 繰り返し二乗法

// 罠
// 同一配列内遷移よりfunctionalグラフであることは自明だが、順列なので木部分が存在しない点
// ダブリングだけじゃTLEする点 → 周期性使ってね

// ポイント
// 同一配列内遷移はfunctionalグラフ
// → 順列は木部分がない
// 二重遷移の形状はダブリング

ll pow(ll x, ll n, ll mod = 1) {
    ll res = 1;
    while (n > 0) {
        if (n & 1) res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

int main() {
    int n; ll k; cin >> n >> k;
    vector<int> p(n);
    rep(i, n) cin >> p[i], p[i]--;

    vector<int> ans(n, -1);
    rep(i, n) {
        if (ans[i] != -1) continue;

        vector<int> cyc;
        int cur = i;
        do {
            cyc.push_back(cur);
            cur = p[cur];
        } while (cur != i);

        int r = cyc.size();
        int step = pow(2, k, r);
        rep(j, r) {
            ans[cyc[j]] = cyc[(j + step) % r];
        }
    }

    rep(i, n) cout << ans[i] + 1 << ' ';
    cout << endl;
}
