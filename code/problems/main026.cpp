// E - Last Train
// https://atcoder.jp/contests/abc342/tasks/abc342_e
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Edge {
    int to;
    ll l, d, k, c;
    Edge(int to, ll l, ll d, ll k, ll c): to(to), l(l), d(d), k(k), c(c) {};
};

const ll INF = numeric_limits<ll>::max();

int main() {
    int n, m; cin >> n >> m;
    vector<vector<Edge>> rg(n);
    for (int i = 0; i < m; i++) {
        int l, d, k, c, a, b;
        cin >> l >> d >> k >> c >> a >> b;
        a--; b--;
        rg[b].emplace_back(a, l, d, k, c);
    }

    // 各頂点において最大値を取りたいので、fは最小値で初期化, 始点は最大値で初期化
    vector<ll> f(n, -1);
    f[n - 1] = INF;

    // 逆順にダイクストラする
    priority_queue<pair<ll, int>> pq;
    pq.emplace(INF, n - 1);
    while (!pq.empty()) {
        auto [fv, v] = pq.top(); pq.pop();
        if (fv != f[v]) continue;
        for (auto adj : rg[v]) {
            ll nf = f[v] - adj.c;  // 次の駅vでの終電に間に合う最遅の出発時刻
            if (nf < adj.l) continue;  // 始発より早いなら到達不可能
            ll ltrain = adj.l + adj.d * (adj.k - 1);
            if (nf >= ltrain) nf = ltrain;  // 終電より遅いなら終電を使う
            else {
                // nfに乗れる最遅の電車を求める
                int k = (nf - adj.l) / adj.d;
                nf = adj.l + adj.d * k;
            }

            // f[adj.to]を更新
            if (f[adj.to] < nf) {
                f[adj.to] = nf;
                pq.emplace(f[adj.to], adj.to);
            }
        }
    }

    for (int i = 0; i < n - 1; i++) {
        if (f[i] == -1) cout << "Unreachable" << endl;
        else cout << f[i] << endl;
    }
}
