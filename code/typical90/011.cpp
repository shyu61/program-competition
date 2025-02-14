#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// ジャンル
// 組合せ最適化, ジョブスケジューリング問題

// 方針
// ジョブスケジューリング問題なので貪欲的に処理できないか検討する
// 貪欲に考えることで、方向を定義することができるため集合管理せずともdpができる

// ポイント
// bitdpは考慮する集合に順序を規定できない場合に使うが、貪欲法と組合せることができれば、
// その瞬間瞬間で、その要素を使うかどうかを記述できれば十分なので、集合管理する必要がなくなる

void chmax(ll& a, ll b) { a = max(a, b); }

// 貪欲法+dp
int main() {
    int n; cin >> n;
    vector<tuple<int, int, int>> job(n);
    rep(i, n) {
        int d, c, s; cin >> d >> c >> s;
        job[i] = {d, c, s};
    }
    sort(job.begin(), job.end());

    const int DMAX = 5000;
    vector<vector<ll>> dp(n + 1, vector<ll>(DMAX + 1));
    rep(i, n) {
        auto [d, c, s] = job[i];
        rep(j, DMAX) {
            if (j + c <= d) {
                chmax(dp[i + 1][j + c], dp[i][j] + s);
            }
            chmax(dp[i + 1][j], dp[i][j]);
        }
    }

    ll ans = 0;
    rep(i, DMAX + 1) chmax(ans, dp[n][i]);
    cout << ans << endl;
}

// 貪欲法+bit全探索
int main() {
    int n; cin >> n;
    vector<tuple<int, int, int>> job(n);
    rep(i, n) {
        int d, c, s; cin >> d >> c >> s;
        job[i] = {d, c, s};
    }
    sort(job.begin(), job.end());

    int n2 = 1 << n; ll ans = 0;
    rep(i, n2) {
        int now = 0; ll res = 0;
        rep(j, n) {
            auto [d, c, s] = job[j];
            if ((i >> j & 1) && now + c <= d) {
                res += s;
                now += c;
            }
        }
        ans = max(ans, res);
    }
    cout << ans << endl;
}

// 全探索(順列の総当たり)
int main() {
    int n; cin >> n;
    vector<int> d(n), c(n), s(n);
    rep(i, n) cin >> d[i] >> c[i] >> s[i];

    vector<int> a(n);
    rep(i, n) a[i] = i;

    ll ans = 0;
    do {
        int now = 0; ll res = 0;
        for (auto i : a) {
            if (now + c[i] <= d[i]) {
                res += s[i];
                now += c[i];
            }
        }
        ans = max(ans, res);
    } while (next_permutation(a.begin(), a.end()));

    cout << ans << endl;
}
