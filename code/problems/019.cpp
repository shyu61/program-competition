// E - Remove Pairs
// https://atcoder.jp/contests/abc354/tasks/abc354_e
#include <bits/stdc++.h>
using namespace std;

/* ========================== メモ化再帰を使った解法
int n;
vector<int> a, b, dp;

int rec(int s) {
    if (dp[s] != -1) return dp[s];

    int res = 1;
    for (int i = 0; i < n - 1; i++) {
        if (s >> i & 1) continue;
        if (res == 0) break;

        for (int j = i + 1; j < n; j++) {
            if (s >> j & 1) continue;
            if (res == 0) break;

            if (a[i] == a[j] || b[i] == b[j]) {
                // 最適な操作 => 枝を辿った時最終自分が勝つ枝を選択 => 深さが奇数の枝が存在しているか
                res = (rec(s | (1 << i) | (1 << j)) + 1) % 2;
                // `res == 0`なら自分が勝つ枝が存在しているのでbreak
            }
        }
    }
    // 自分が勝つ枝がない場合は`res == 1`となる
    return dp[s] = res;
}

int main() {
    cin >> n;
    a = b = vector<int>(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        a[i]--; b[i]--;
    }

    dp = vector<int>(1 << n, -1);
    int ans = rec(0);
    if (!ans) cout << "Takahashi" << endl;
    else cout << "Aoki" << endl;
}
========================== */

// 別解: 漸化式を使った解法

int main() {
    int n; cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        a[i]--; b[i]--;
    }

    // dpテーブルが後ろから埋まる場合、集合を"残り"とすることで順方向にループを回せる
    vector<bool> dp(1 << n);
    for (int s = 0; s < (1 << n); s++) {
        bool now = false;
        for (int i = 0; i < n - 1; i++) {
            if (!(s >> i & 1)) continue;
            if (now) break;

            for (int j = i + 1; j < n; j++) {
                if (!(s >> j & 1)) continue;
                if (now) break;

                if (a[i] == a[j] || b[i] == b[j]) {
                    // 遷移先に一つでもfalseがあればtrue
                    if (!dp[s ^ (1 << i) ^ (1 << j)]) now = true;
                }
            }
        }
        dp[s] = now;
    }

    if (dp[(1 << n) - 1]) cout << "Takahashi" << endl;
    else cout << "Aoki" << endl;
}
