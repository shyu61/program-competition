#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;

// https://atcoder.jp/contests/joi2019yo/tasks/joi2019_yo_d

// 🔷初見でどうやったら解けるか
// 座標圧縮してsortして順に見ていけば良さそう。前後の大小関係の場合分けで増減が決められる。あとは丁寧に実装するだけ。

// 🔷抑えるべき抽象論は？
// 座標圧縮
// - 実際に座標圧縮する
// - mapを使う
// - sortして見ていく時に値の変化を検知する

int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    // 同じ高さの連続部分は縮約しておく
    int pos = 0;
    rep(i, n) {
        if (a[i] != a[pos]) a[++pos] = a[i];
    }
    n = pos + 1;

    vector<P> vs(n);
    rep(i, n) vs[i] = {a[i], i};
    sort(vs.begin(), vs.end());

    // 初期値の計算
    int cnt = a[0] > 0 ? 1 : 0;
    for (int i = 1; i < n; i++) {
        if (a[i] > 0 && a[i - 1] == 0) cnt++;
    }

    int ans = cnt;
    rep(j, n) {
        auto [h, i] = vs[j];
        if (h == 0) continue;
        if (i == 0) {
            if (n > 1 && a[i + 1] < h) cnt--;
        } else if (i == n - 1) {
            if (a[i - 1] < h) cnt--;
        } else {
            if (a[i - 1] < h && a[i + 1] < h) cnt--;
            if (a[i - 1] > h && a[i + 1] > h) cnt++;
        }
        if (j == n - 1 || h != vs[j + 1].first) ans = max(ans, cnt);
    }
    cout << ans << endl;
}
