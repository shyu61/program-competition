#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<ll, ll>;

// https://atcoder.jp/contests/joi2015yo/tasks/joi2015yo_f

// 🔷初見でどうやったら解けるか
// 組合せ最適化問題で最初に検討するのは全探索だが、半分全探索の可能性も同時に考慮するのが良い。
// 制約条件的に半分は全探索ができるので、sortして単調性を使いつつ二分探索や尺取り/スライド最小化などを使って求解できないか検討する

// 🔷抑えるべき抽象論は？
// 全探索と同時に半分全探索も考慮する
// - 半分全探索は、sortして単調性を導出し、二分探索や尺取り法,スライド最小化などを使うことを考える
// スライド最小化
// - 新しくpushする要素は、制約条件に対して最も有利である必要がある
// - pushの際のpop_back条件は目的関数に基づく
// - 先頭は解の必要条件だが十分条件ではない。push時とは逆側の制約条件が存在する場合は、取り出した先頭が制約条件を満たすのか検証が必要

int main() {
    int n; ll D; cin >> n >> D;
    vector<P> a(n);
    rep(i, n) cin >> a[i].first >> a[i].second;
    int n2 = n / 2;

    auto dfs = [&](auto dfs, vector<P>& vec, ll w, ll v, int d, int last) -> void {
        if (d == last) {
            vec.emplace_back(w, v);
            return;
        }
        dfs(dfs, vec, w + a[d].first, v + a[d].second, d + 1, last);
        dfs(dfs, vec, w - a[d].first, v - a[d].second, d + 1, last);
        dfs(dfs, vec, w, v, d + 1, last);
    };
    vector<P> L, R;
    dfs(dfs, L, 0, 0, 0, n2);
    dfs(dfs, R, 0, 0, n2, n);

    sort(L.rbegin(), L.rend());
    sort(R.begin(), R.end());

    deque<P> deq;
    ll ans = 0; int pos = 0;
    for (auto [lw, lv] : L) {
        while (pos < R.size() && R[pos].first + lw <= D) {
            while (deq.size() && deq.back().second <= R[pos].second) deq.pop_back();
            deq.push_back(R[pos]);
            pos++;
        }
        // 典型的なスライド最小化と違い、キャンセルされる先頭の要素数は固定ではない
        // 典型では1つスライドすると先頭1つだけキャンセルされるが、範囲制約ではなく値に関する制約なので、幾つキャンセルするかはループする必要がある
        while (deq.size() && deq.front().first + lw < -D) deq.pop_front();
        if (deq.size()) {
            ans = max(ans, lv + deq.front().second);
        }
    }
    cout << ans << endl;
}
