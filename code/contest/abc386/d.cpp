#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using TP = tuple<int, int, char>;
const int INF = 1001001001;

// ジャンル
// グリッド問題, 階段状領域問題

// 方針
// グリッド問題で判定系なのでsortして片方を固定して考える
// sortして順にスキャンするという時点で、逐次問題に変化していることに注意
// つまりスキャンしつつ動的に何らかしらの情報を保存し、それを使って判定することを考えると、
// Wのyの最小値さえあれば十分であることがわかる
// これに区間などが絡むとfenwicktree、端点情報だけでなく全体を保持する必要があるならsetやmapなどが必要になるケースもある

// ポイント
// sortしてスキャンする行為は逐次操作である
// 逐次操作は動的に何らかしらの情報を伝播することが多い

int main() {
    int n, m; cin >> n >> m;
    vector<TP> a(m);
    rep(i, m) {
        int x, y; char c; cin >> x >> y >> c;
        a[i] = {--x, --y, c};
    }
    sort(a.begin(), a.end());

    int my = INF;
    for (auto [x, y, c] : a) {
        if (c == 'W') {
            my = min(my, y);
            continue;
        }
        if (my <= y) {
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
}
