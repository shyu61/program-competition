#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

struct UnionFind {
    int _n;
    vector<int> parents;
    UnionFind(int n) : _n(n), parents(n, -1) {}

    void init(int n) {
        parents.assign(n, -1);
    }

    int leader(int x) {
        return parents[x] < 0 ? x : parents[x] = leader(parents[x]);
    }

    bool same(int x, int y) {
        return leader(x) == leader(y);
    }

    int merge(int x, int y) {
        x = leader(x), y = leader(y);
        if (x == y) return x;
        if (parents[x] > parents[y]) swap(x, y);
        parents[x] += parents[y];
        parents[y] = x;
        return x;
    }

    int size(int x) {
        return -parents[leader(x)];
    }

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

int solve() {
    int n; string s, t; cin >> n >> s >> t;
    int m = 26;

    if (s == t) return 0;
    set<char> st(t.begin(), t.end());
    if (st.size() == m) return -1;

    vector<int> to(m, -1);
    rep(i, n) {
        int c1 = s[i] - 'a', c2 = t[i] - 'a';
        if (to[c1] != -1 && to[c1] != c2) return -1;
        to[c1] = c2;
    }

    int ans = 0;
    vector<int> in_deg(m);
    UnionFind uf(m);
    rep(i, m) {
        if (to[i] == -1) continue;
        if (i != to[i]) ans++;  // 自己ループ以外のedgeを数える
        uf.merge(i, to[i]);
        in_deg[to[i]]++;
    }

    for (const auto& g : uf.groups()) {
        if (g.size() == 1) continue;
        bool has_cycle = true, has_br = false;
        for (auto v : g) {
            if (in_deg[v] > 1) has_br = true;
            // 出次数で判定しても良い
            if (to[v] == -1) has_cycle = false;
        }
        if (has_cycle && !has_br) ans++;
    }
    return ans;
}

int main() {
    cout << solve() << endl;
}
