#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using TP = tuple<int, int, int>;

// https://atcoder.jp/contests/abc383/tasks/abc383_e
// 🔷初見でどうやったら解けるか
// グラフのボトルネック最小化問題なので、mstを検討する。
// この手の問題はクラスカル法でmstを構築しつつ処理していくのが定番
// uf.merge(u,v)する時に、作れるだけペアリングすれば良い。注意点は作るペアは(u,v)だけじゃなく、
// merge前のu,vそれぞれのサブグラフの頂点の全ペアに対するペアリングをする必要がある点。
// これはO(n^2)かかるが、mergeのたびにleaderに情報を集約しておけばO(1)で実行できる。

// 🔷抑えるべき抽象論は？
// union-findを使う問題で、merge時に連結成分同士でなんらかの処理をする場合、leaderに情報を集約しておくと便利
// - いちいち連結成分内の要素を見ずとも、leaderだけ見れば良くなる

struct UnionFind {
    int _n;
    vector<int> parents;
    UnionFind(int n) : _n(n), parents(n, -1) {}

    void init(int n) { parents.assign(n, -1); }
    int leader(int x) { return parents[x] < 0 ? x : parents[x] = leader(parents[x]); }
    bool same(int x, int y) { return leader(x) == leader(y); }

    int merge(int x, int y) {
        x = leader(x), y = leader(y);
        if (x == y) return x;
        if (parents[x] > parents[y]) swap(x, y);
        parents[x] += parents[y];
        parents[y] = x;
        return x;
    }

    int size(int x) { return -parents[leader(x)]; }
};

int main() {
    int n, m, k; cin >> n >> m >> k;
    vector<TP> es(m);
    rep(i, m) {
        int u, v, w; cin >> u >> v >> w;
        u--, v--;
        es[i] = {w, u, v};
    }
    vector<int> a(n), b(n);
    rep(i, k) { int ai; cin >> ai, ai--; a[ai]++; }
    rep(i, k) { int bi; cin >> bi, bi--; b[bi]++; }

    sort(es.begin(), es.end());

    ll ans = 0;
    UnionFind uf(n);
    for (auto [c, u, v] : es) {
        if (uf.same(u, v)) continue;

        u = uf.leader(u);
        v = uf.leader(v);

        if (a[v] > 0 && b[u] > 0) swap(u, v);
        if (a[u] > 0 && b[v] > 0) {
            int mn = min(a[u], b[v]);
            a[u] -= mn;
            b[v] -= mn;
            ans += ll(mn) * c;
            k -= mn;
        }
        uf.merge(u, v);

        int lead = uf.leader(u);
        a[lead] = a[u] + a[v];
        b[lead] = b[u] + b[v];
        // a[v] = b[v] = 0;

        if (k <= 0) break;
    }

    cout << ans << endl;
}
