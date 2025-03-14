#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
const int INF = 1001001001;
using uint = unsigned int;

// bitdpの場合、indexはpopcountで代用できる場合がある
// イレギュラーな添字の持ち方をした時は、どこまで初期化する必要があるか慎重に考える

void chmin(int& a, int b) { a = min(a, b); }

// O(n!)
int main() {
    int n; cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    rep(i, n) rep(j, n) cin >> a[i][j];
    int m; cin >> m;
    vector<vector<bool>> ng(n, vector<bool>(n, false));
    rep(i, m) {
        int x, y; cin >> x >> y, x--, y--;
        ng[x][y] = ng[y][x] = true;
    }

    vector<int> ord(n);
    rep(i, n) ord[i] = i;

    int ans = INF;
    do {
        bool ok = true;
        int res = 0;
        rep(i, n) {
            if (i < n - 1 && ng[ord[i]][ord[i + 1]]) ok = false;
            res += a[ord[i]][i];
        }
        if (ok) ans = min(ans, res);
    } while (next_permutation(ord.begin(), ord.end()));

    if (ans == INF) ans = -1;
    cout << ans << endl;
}

// O(n^2 * 2^n)
int main() {
    int n; cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    rep(i, n) rep(j, n) cin >> a[i][j];
    int m; cin >> m;
    vector<vector<bool>> ng(n, vector<bool>(n, false));
    rep(i, m) {
        int x, y; cin >> x >> y, x--, y--;
        ng[x][y] = ng[y][x] = true;
    }

    // dp[s][i]:=走った人の集合sについて、最後にiが走った時の最短時間
    int n2 = 1 << n;
    vector<vector<int>> dp(n2, vector<int>(n, INF));
    // 添え字に「最後にi」があるので初期化時に第一区まで計算する必要がある
    rep(i, n) dp[1 << i][i] = a[i][0];
    rep(s, n2) {
        rep(i, n) {
            // この条件で第一区の計算はスキップされてしまう
            if (~s >> i & 1) continue;
            rep(j, n) {
                if (s >> j & 1) continue;
                if (!ng[i][j]) {
                    chmin(dp[s | 1 << j][j], dp[s][i] + a[j][popcount(uint(s))]);
                }
            }
        }
    }

    int ans = INF;
    rep(i, n) chmin(ans, dp[n2 - 1][i]);
    if (ans == INF) ans = -1;
    cout << ans << endl;
}
