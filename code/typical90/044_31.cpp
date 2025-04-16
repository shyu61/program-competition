#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<ll, ll>;

// 関連問題: https://atcoder.jp/contests/abc189/tasks/abc189_e
// やや特殊な解法

// 🔷初見でどうやったら解けるか
// クエリ問題で一回の操作で複数の要素を変換する必要があるタイプの問題
// 点同士の相対関係が保持されるかをまず確認し、保持されないが明らかに規則的に関係性が変化することが予想できる
// 故に代表値変換ではなく、一般項を求められないかの検討になる。線形変換のみからなることから変換行列を定義できそうと思いつける

// 🔷類問を考える
// p度回転,点対象,変換関数などの操作がある問題など: 全て線形変換なのでアフィン変換できる
// 60度回転操作が10^9回: 周期的な変換は剰余を取れば良い
// 同質変換が10^9回: 同じ変換行列で表せるなら行列累乗が使える

int main() {
    int n; cin >> n;
    vector<int> X(n), Y(n);
    rep(i, n) cin >> X[i] >> Y[i];

    int m; cin >> m;
    vector<P> org(m + 1), vec(m + 1);
    // 原点を基準に考えることで、ベクトルは符号とflip変化のみになる
    // -> 適当な2整数を使えば十分情報を保存できる
    vec[0] = {1, 2};
    rep(i, m) {
        int type, p = 0; cin >> type;
        if (type > 2) cin >> p;

        auto [x, y] = org[i];
        auto [vx, vy] = vec[i];
        if (type == 1) {
            org[i + 1] = {y, -x};
            vec[i + 1] = {vy, -vx};
        }
        if (type == 2) {
            org[i + 1] = {-y, x};
            vec[i + 1] = {-vy, vx};
        }
        if (type == 3) {
            org[i + 1] = {x + (p - x) * 2, y};
            vec[i + 1] = {-vx, vy};
        }
        if (type == 4) {
            org[i + 1] = {x, y + (p - y) * 2};
            vec[i + 1] = {vx, -vy};
        }
    }

    int q; cin >> q;
    while (q--) {
        int a, b; cin >> a >> b, b--;
        auto [x, y] = org[a];
        auto [vx, vy] = vec[a];

        if (abs(vx) == 1) {
            vx *= X[b];
            vy = vy / 2 * Y[b];
        } else {
            vx = vx / 2 * Y[b];
            vy *= X[b];
        }

        cout << x + vx << ' ' << y + vy << '\n';
    }
}
