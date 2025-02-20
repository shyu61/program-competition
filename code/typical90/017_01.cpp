#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;
const int INF = 1001001001;

// ジャンル
// 数え上げ, 区間問題, 配置問題

// ポイント
// - 数え上げの条件式が複数ある場合は、補集合により簡単な条件に変換できないか考える
// - 位置関係問題は、sortやswapにより条件をシンプルにすることを考える
// - 区間や位置による数え上げは、fenwicktreeによる高速化ができないか検討する

// 全探索による解法
int main() {
    int n, m; cin >> n >> m;
    vector<P> s(m);
    rep(i, m) {
        int l, r; cin >> l >> r, l--, r--;
        s[i] = {l, r};
    }
    sort(s.begin(), s.end());

    auto is_intersect = [&](P& a, P& b) -> bool {
        auto [ls, rs] = a;
        auto [lt, rt] = b;
        return ls < lt && lt < rs && rs < rt;
    };

    int ans = 0;
    rep(i, m) {
        for (int j = i + 1; j < m; j++) {
            if (is_intersect(s[i], s[j])) ans++;
        }
    }
    cout << ans << endl;
}

// 一部を二分探索で高速化する解法
// R同士の比較が線形なので計算量は同じ。但し定数倍は小さくなる
int main() {
    int n, m; cin >> n >> m;
    vector<P> s(m);
    rep(i, m) {
        int l, r; cin >> l >> r, l--, r--;
        s[i] = {l, r};
    }
    sort(s.begin(), s.end());

    int ans = 0;
    rep(i, m) {
        // Ls<Lt
        int p1 = upper_bound(s.begin(), s.end(), make_pair(s[i].first, INF)) - s.begin();
        // Lt<Rs
        int p2 = lower_bound(s.begin() + p1, s.end(), make_pair(s[i].second, 0)) - s.begin();
        // Rs<Rt
        for (int j = p1; j < p2; j++) {
            if (s[i].second < s[j].second) ans++;
        }
    }
    cout << ans << endl;
}
