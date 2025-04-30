#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;
const int INF = 1001001001;

// 🔷抑えるべき抽象論は？
// dpでは区間min/maxが頻出だが、必ずしもスライド最小化やセグ木が使える訳ではないことに注意
// - 重複区間の結果が変化しないことが前提
// - 例えば本問題ではi→i+1でコストの基準が変化するので重複区間の結果も変化してしまう
// 遷移コストの単調性支配
// - 配るdpで考えた時、遷移先が区間など複数ある場合に、下記の条件を満たせば同一方向に対してO(1)で遷移できる
//   - コストが加法的かつ、絶対値や平方などの「距離」である
//   - 報酬によらず最もコストが小さくなる点に遷移すれば良い
// - 「少し高いが先に進める」候補があっても方向が同じでコストが加法的であれば経由しても合計コストは同じ

int main() {
    int n, k; cin >> n >> k;
    vector<int> h(n);
    rep(i, n) cin >> h[i];

    vector<int> dp(n, INF);
    dp[0] = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= min(k, i); j++) {
            dp[i] = min(dp[i], dp[i - j] + abs(h[i] - h[i - j]));
        }
    }

    cout << dp[n - 1] << endl;
}

// https://www.mathenachia.blog/harder-edpc/#toc2
void chmin(int& a, int b) { a = min(a, b); }

int main() {
    int n, k; cin >> n >> k;
    vector<int> h(n);
    rep(i, n) cin >> h[i];

    set<P> st;
    for (int i = 1; i <= min(k, n - 1); i++) st.emplace(h[i], i);

    vector<int> dp(n, INF);
    dp[0] = 0;
    rep(i, n - 1) {
        if (i + k < n) st.emplace(h[i + k], i + k);
        st.erase({h[i], i});

        auto it = st.lower_bound({h[i], -1});
        if (it != st.end()) chmin(dp[it->second], dp[i] + abs(it->first - h[i]));
        if (it != st.begin()) {
            it--;
            chmin(dp[it->second], dp[i] + abs(it->first - h[i]));
        }
    }

    cout << dp[n - 1] << endl;
}
