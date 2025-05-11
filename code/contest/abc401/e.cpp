#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;

int main() {
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n);
    rep(i, m) {
        int u, v; cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int i = 0;
    auto bfs = [&](int v) -> void {
        priority_queue<int, vector<int>, greater<int>> pq;
        vector<int> seen(n);
        pq.push(v); seen[v] = 1;

        int pos = 1;
        while (!pq.empty()) {
            int v = pq.top(); pq.pop();
            seen[v] = 2;
            for (auto u : g[v]) {
                if (seen[u]) continue;
                pq.push(u);
                seen[u] = 1;
            }
            while (pos < n && seen[pos] == 2) pos++;
            if (i < pos) cout << pq.size() << '\n';
            else cout << -1 << '\n';
            i++;
        }
    };
    bfs(0);

    for (int j = i; j < n; j++) cout << -1 << '\n';
}

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

    vector<vector<int>> groups() {
        vector<int> lds(_n);
        for (int i = 0; i < _n; i++) lds[i] = leader(i);
        vector<vector<int>> res(_n);
        for (int i = 0; i < _n; i++) res[lds[i]].push_back(i);
        res.erase(
            remove_if(
                res.begin(),
                res.end(),
                [&](const vector<int>& vec) { return vec.empty(); }
            ),
            res.end()
        );
        return res;
    }
};

int main() {
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n);
    rep(i, m) {
        int u, v; cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    UnionFind uf(n), uf_all(n);

    rep(i, n) {
        for (auto u : g[i]) {
            if (u < i) uf.merge(i, u);
            uf_all.merge(i, u);
        }
        if (uf.size(i) == i + 1) cout << uf_all.size(i) - i - 1 << '\n';
        else cout << -1 << '\n';
    }
}
