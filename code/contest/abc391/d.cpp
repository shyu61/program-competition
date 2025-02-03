#include <bits/stdc++.h>
using namespace std;
using P = pair<int, int>;

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

const int INF = 1e9 + 1;

int main() {
    int n, w; cin >> n >> w;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i], x[i]--, y[i]--;

    vector<vector<P>> cols(w);
    for (int i = 0; i < n; i++) cols[x[i]].emplace_back(y[i], i);
    for (int i = 0; i < w; i++) sort(cols[i].begin(), cols[i].end());

    vector<int> ans(n, INF);
    bool complete = false;
    for (int is = 0; is < n; is++) {
        int maxv = 0;
        for (int i = 0; i < w; i++) {
            if (is == cols[i].size()) {
                complete = true;
                break;
            }
            maxv = max(maxv, cols[i][is].first);
        }
        if (complete) break;
        for (int i = 0; i < w; i++) {
            ans[cols[i][is].second] = maxv + 1;
        }
    }

    int q; cin >> q;
    while (q--) {
        int t, ai; cin >> t >> ai; ai--;
        cout << (t < ans[ai] ? "Yes" : "No") << '\n';
    }
}
