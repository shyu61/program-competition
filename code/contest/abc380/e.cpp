#include <bits/stdc++.h>
using namespace std;

// ジャンル
// 逐次問題, クエリ問題

struct Dsu {
    vector<int> par;
    Dsu(int n) : par(n, -1) {}
    void init(int n) { par.assign(n, -1); }
    int root(int x) { return par[x] < 0 ? x : par[x] = root(par[x]); }
    bool same(int x, int y) { return root(x) == root(y); }
    bool merge(int x, int y) {
        x = root(x), y = root(y);
        if (x == y) return false;
        if (par[x] > par[y]) swap(x, y);
        par[x] += par[y];
        par[y] = x;
        return true;
    }
    int size(int x) { return -par[root(x)]; }
};

int main() {
    int n, q; cin >> n >> q;
    vector<int> l(n), r(n), color(n), cnt(n, 1);
    for (int i = 0; i < n; i++) l[i] = r[i] = color[i] = i;
    Dsu dsu(n);
    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int x, c; cin >> x >> c; x--; c--;
            x = dsu.root(x);
            int size = dsu.size(x);
            if (color[x] == c) continue;

            cnt[c] += size;
            cnt[color[x]] -= size;

            int left = l[x], right = r[x];
            int xl = l[x] - 1, xr = r[x] + 1;
            if (xl >= 0) {
                xl = dsu.root(xl);
                if (color[xl] == c) {
                    left = l[xl];
                    dsu.merge(x, xl);
                }
            }
            if (xr < n) {
                xr = dsu.root(xr);
                if (color[xr] == c) {
                    right = r[xr];
                    dsu.merge(x, xr);
                }
            }

            x = dsu.root(x);
            l[x] = left; r[x] = right; color[x] = c;
        } else {
            int c; cin >> c; c--;
            cout << cnt[c] << endl;
        }
    }
}
