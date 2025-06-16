#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 単純グラフ: 自己ループと多重辺を持たない。閉路は持つ可能性がある

// 🔷抑えるべき抽象論は？
// エッジの頂点への寄与度は2である
// - 頂点ごとに隣接頂点をなめる時、高々2Mにしかならない

int main() {
    int n, m; cin >> n >> m;
    vector<int> a(n);
    rep(i, m) {
        int u, v; cin >> u >> v;
        u--, v--;
        if (u > v) swap(u, v);
        a[v]++;
    }

    int ans = 0;
    rep(i, n) if (a[i] == 1) ans++;
    cout << ans << endl;
}
