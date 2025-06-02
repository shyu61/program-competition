#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;

// 想定解
// グラフで考える
// &,|,^などrは桁ごとに独立という性質を使って全探索

// 罠
// 桁ごとに独立という性質を使わないと全探索できない点

// 方針
// 配列に対する数え上げや組合せ最適化において、条件が隣接でない2項間制約の場合はグラフを考えると良い。
// 連結成分ごとに独立に考えて良い。同じ連結成分内ではある1つの頂点の値を決めると、他の頂点の値も全て決まる。
// この関係に矛盾が生じる時に-1として良い。
// 次に総和が最小になるようなこの値を探索することを考える。取りうる値は無数にあるので全探索は不可能だが、xorが桁ごとに独立である性質を使うと、
// 桁ごとに0,1それぞれにした時、他の頂点の同桁の1の個数が少ない方を採用すれば良いことがわかる。
// zi<=1e9より、これ以上にする意味はないのでAの各要素もそれ以下と言える。故に30桁分調べれば十分。

// xorについて
// - 結合法則・交換法則を満たす
//   - a^b=c ならば a=b^c (方程式演算ができる)
//     - つまり2数が決まれば、3つ目は一意に決まる
// - 局所最適性が成立しない
// - &,|,^は桁ごとに独立
// - &,|,^の総和の大小は、桁ごとの1の個数で判定できる
// - a^b=x,a=0の時b=x
// - a+b = a^b + 2(a&b) : a^bは桁の値,2(a&b)は繰り上がりを表現している
// - a^b=xの時、常にa+b>=x (a+b<xとなる組合せは存在しない)
// - a^b=xの時にa+b=xとなる(a,b)の組はa&b=0を満たすような組を考えればよく、xのbit列を考えた時に、1が立ってる桁にa,bどちらか一方1を立て、0の桁は両方とも0にする(両方1にするとa&b=0を満たさない)

int main() {
    int n, m; cin >> n >> m;
    vector<vector<P>> g(n);
    rep(i, m) {
        int x, y, z; cin >> x >> y >> z;
        x--, y--;
        g[x].emplace_back(y, z);
        g[y].emplace_back(x, z);
    }

    vector<int> ans(n);
    rep(d, 30) {
        vector<int> a(n, -1);
        rep(i, n) {
            if (a[i] != -1) continue;

            vector<vector<int>> col(2);
            auto dfs = [&](auto dfs, int v, int xo) -> bool {
                if (a[v] != -1) return a[v] == xo;
                a[v] = xo;
                col[xo].push_back(v);
                for (auto [u, w] : g[v]) {
                    if (!dfs(dfs, u, xo ^ (w >> d & 1))) return false;
                }
                return true;
            };

            // 01どちらか一方の場合だけ調べれば十分
            // 01を変えても全て反転するだけで矛盾箇所は解消されない
            if (!dfs(dfs, i, 0)) {
                cout << -1 << endl;
                return 0;
            }

            if (col[0].size() > col[1].size()) {
                for (auto c : col[1]) ans[c] |= 1 << d;
            } else {
                for (auto c : col[0]) ans[c] |= 1 << d;
            }
        }
    }
    rep(i, n) cout << ans[i] << ' ';
    cout << endl;
}
