#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
const ll INF = numeric_limits<ll>::max();

// 🔷初見でどうやったら解けるか
// 組合せ最適化問題なので、全探索/貪欲を考える。貪欲っぽいが、要素数が2以上の集合を高速にmergeできない。
// N<=15から何らかの全探索系を使うと予想する。素直な全探索は間に合わないので、半分全列挙やbitdpを検討する。
// また、最大値の最小化なので判定問題を考えて、その判定にbitdpが必要と考えても良い。
// いずれにせよ高速に集合をmergeできない時点でbitdpで集合を舐めることを思いつけることが重要。bitdpの遷移条件として、部分集合の部分集合を使う類の問題なので、O(3^n)で解ける。

// 🔷抑えるべき抽象論は？
// bitdpの遷移は部分集合の部分集合を考えるタイプのものが存在する
// - 部分集合の部分集合
//  - https://kenkoooo.hatenablog.com/entry/2021/01/03/215401
//  - `(sub-1)&s`により部分集合を列挙できる
//    - `sub-1`で最も右にある1を取り除く
//    - `&s`で元の集合に含まれる要素のみを取り出すことを保証
// 制約が小さい時に検討すべき全探索系
// - 全探索
// - 半分全探索
// - bitdp

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y) : x(x), y(y) {}
};

int main() {
    int n, k; cin >> n >> k;
    vector<Point> a(n);
    rep(i, n) cin >> a[i].x >> a[i].y;

    int n2 = 1 << n;
    vector<ll> cost(n2);  // cost[i] := 集合がiのクラスターの最遠点距離
    rep(s, n2) {
        ll mx = 0;
        vector<Point> c;
        rep(i, n) {
            if (s >> i & 1) {
                for (auto p : c) {
                    ll dx = p.x - a[i].x;
                    ll dy = p.y - a[i].y;
                    mx = max(mx, dx * dx + dy * dy);
                }
                c.push_back(a[i]);
            }
        }
        cost[s] = mx;
    }

    // dp[s][i]:=選んだ頂点集合sで、クラスターをi個作る時の最小スコア
    vector<vector<ll>> dp(n2, vector<ll>(k + 1, INF));
    dp[0][0] = 0;
    rep(s, n2) {
        for (int i = 1; i <= k; i++) {
            for (int sub = s; sub > 0; sub = (sub - 1) & s) {
                dp[s][i] = min(dp[s][i], max(dp[s ^ sub][i - 1], cost[sub]));
            }
        }
    }
    cout << dp[n2 - 1][k] << endl;
}
