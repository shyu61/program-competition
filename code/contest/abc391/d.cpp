#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;
const int INF = 1001001001;

// ジャンル
// クエリ問題, 逐次問題, グリッド問題

// 方針
// クエリ問題は何を事前計算するかが肝。静的クエリかつ、N<=2e5より全ブロックを事前計算する方針で考える
// 各列で見た時、最も下のブロックが次に消える候補でありこの順番が逆転することはない
// 故に列ごとに最も下のブロックがy=0になる時刻と、消える時刻が求まれば良い
// 列方向に同じ番号の要素をまとめた配列を用意し、「max(各配列の最大値+1,直前の行が消えた時刻+1)」がその行のブロックが消える時刻になる

// ポイント
// 1つの集合に対して1度しかsortしないならsetではなく普通にsortを使う
//   - 本問題は列ごとにsortするためsort回数自体は多いが、1つの集合に対して1度しかsortは行っていない

int main() {
    int n, w; cin >> n >> w;
    vector<int> x(n), y(n);
    rep(i, n) cin >> x[i] >> y[i], x[i]--, y[i]--;

    vector<vector<P>> cols(w);
    rep(i, n) cols[x[i]].emplace_back(y[i], i);
    rep(i, w) sort(cols[i].begin(), cols[i].end());

    vector<int> ans(n, INF);
    bool complete = false;
    rep(is, n) {
        int maxv = 0;
        rep(i, w) {
            if (is == cols[i].size()) {
                complete = true;
                break;
            }
            maxv = max(maxv, cols[i][is].first);
        }
        if (complete) break;
        rep(i, w) {
            ans[cols[i][is].second] = maxv + 1;
        }
    }

    int q; cin >> q;
    while (q--) {
        int t, ai; cin >> t >> ai; ai--;
        cout << (t < ans[ai] ? "Yes" : "No") << '\n';
    }
}
