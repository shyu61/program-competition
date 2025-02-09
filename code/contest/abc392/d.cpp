#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// ジャンル
// 確率, sparse配列

// 方針
// 本問題は状態遷移を伴わず各操作を完全に独立に行えるシンプルな問題
// 求めるものは独立なもの同士の同時確率なので積を取ればよいだけ

// ポイント
// 確率の問題は「独立性」を考えることが最重要
//   - どの操作とどの操作が独立なのか、状態に依存するのか、その状態はどう遷移するのか
// 確率の基礎
// - 確率の総和は1
// - 加法定理: 互いに排反な事象はP(A∪B)=P(A)+P(B)
// - 独立性: 事象A,Bが独立の時P(A∩B)=P(A)*P(B), いわゆる同時確率
// - 条件付き確率: P(A|B)=P(A∩B)/P(B)
// - ベイズの定理: P(A∩B)=P(A|B)*P(B)
// - 期待値: E[X]=Σx*P(X=x)
//   - 確率による加重平均とも捉えられる
// - 期待値の線形性: E[X+Y]=E[X]+E[Y], 独立に限らない

int main() {
    int n; cin >> n;
    vector<ll> k(n);
    vector<unordered_map<int, ll>> a(n);
    rep(i, n) {
        cin >> k[i];
        rep(j, k[i]) {
            int x; cin >> x;
            a[i][x]++;
        }
    }

    double ans = 0;
    rep(i, n) {
        rep(j, i) {
            ll res = 0;
            if (a[i].size() < a[j].size()) {
                for (auto [ki, vi] : a[i]) res += vi * a[j][ki];
            } else {
                for (auto [ki, vi] : a[j]) res += vi * a[i][ki];
            }
            ans = max(ans, double(res) / (k[i] * k[j]));
        }
    }

    cout << fixed << setprecision(12) << ans << endl;
}
