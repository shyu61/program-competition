#include <bits/stdc++.h>
using namespace std;

// ジャンル
// subseq問題

// 方針
// まず異常に制約が小さい変数があるので、全探索,集合走査を念頭に置く
// sebseqで累積性の考慮が必要なタイプの問題なので、dpを基本戦略とする
// 過去選んだ値が遷移に関わるので、集合走査が可能という観点からもbitdpの可能性が高い

// 集合sは最終状態でフルになるように定義するのが定石なので、使った要素の集合をsとする
// 遷移は集合が増える方向に記述すれば良いので、新たに部分列に要素を加える遷移を書けば良い
// 最も正直な立式は、「dp[s][i]:=i番目まで見て、部分列に使った集合がsの時の最長部分列」だがTLEする
// 冗長な情報はないか考えると、部分列長はsのpopcountで求められるのでdpの値情報が冗長だとわかる。位置情報は必ず必要なので、
// dpの値に位置情報を持たせることを考える。
// 前提として、dpの値には結局は代表値しか持たせられない(複数値持たせると一気に状態数が爆発する)ので、どう情報を圧縮するかが鍵だが、
// 最良の位置、つまり貪欲に考えて最も小さい位置を持たせれば良いことがわかる
// 故に「dp[s]:=部分列をなす要素の集合がsの時の最小位置」とする

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i], a[i]--;

    int m = 20, m2 = 1 << m;
    vector<vector<int>> is(m);
    for (int i = 0; i < n; i++) is[a[i]].push_back(i);

    const int INF = 2e5 + 1;
    // 位置iから値cをd個取る時のd個目の最小の位置を返却
    auto get_next = [&](int c, int i, int d) -> int {
        if (d == 0) return 1;
        int p = lower_bound(is[c].begin(), is[c].end(), i) - is[c].begin();
        p += d - 1;
        if (p < is[c].size()) return is[c][p] + 1;
        return INF;
    };

    // dp[s]:=今まで使った数の集合がsの時、貪欲で取った時の添字のmin
    vector<int> dp(m2, INF); dp[0] = 0;
    int ans = 0;
    // 取りうる集合を全て試す
    for (int s = 0; s < m2; s++) {
        int pc = __builtin_popcount(s);
        if (dp[s] != INF) ans = max(ans, pc);
        for (int c = 0; c < m; c++) {
            if (s >> c & 1) continue;
            // 位置dp[s]からcを2個貪欲に取る
            dp[s | 1 << c] = min(dp[s | 1 << c], get_next(c, dp[s], 2));
        }
    }

    cout << ans * 2 << endl;
}

// TLEするが最も素直な実装
int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i], a[i]--;

    int m = 20, m2 = 1 << m;
    vector<vector<int>> is(m);
    for (int i = 0; i < n; i++) is[a[i]].push_back(i);

    const int INF = 2e5 + 1;
    // 位置iから値cをd個取る時のd個目の最小の位置を返却
    auto get_next = [&](int c, int i, int d) -> int {
        if (d == 0) return 1;
        int p = lower_bound(is[c].begin(), is[c].end(), i) - is[c].begin();
        p += d - 1;
        if (p < is[c].size()) return is[c][p] + 1;
        return INF;
    };

    vector<vector<int>> dp(m2, vector<int>(n + 1));
    dp[0][0] = 0;
    for (int s = 0; s < m2; s++) {
        for (int i = 0; i < n; i++) {
            if (s >> a[i] & 1) continue;
            int nxt = get_next(a[i], i, 2);
            if (nxt <= n) {
                dp[s | 1 << a[i]][nxt] = max(dp[s | 1 << a[i]][nxt], dp[s][i] + 1);
            }
        }
    }

    int ans = 0;
    for (int s = 0; s < m2; s++) ans = max(ans, dp[s][n]);
    cout << ans * 2 << endl;
}
