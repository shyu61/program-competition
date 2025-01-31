#include <bits/stdc++.h>
using namespace std;

// ジャンル
// ゲーム問題, bitdp

// 方針
// 最善の操作を行うゲーム問題は、後ろから更新し、相手を負かす操作が1つでもあれば勝ちという遷移を行う
// 更新は逆方向だが、遷移(評価)は順方向に考える

int main() {
    int n; cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i];

    int n2 = 1 << n;
    vector<bool> dp(n2);
    for (int s = 0; s < n2; s++) {
        bool res = false;
        for (int i = 0; i < n; i++) {
            if (!(s >> i & 1)) continue;
            if (res) break;
            for (int j = i + 1; j < n; j++) {
                if (!(s >> j & 1)) continue;
                if (a[i] == a[j] || b[i] == b[j]) {
                    if (!dp[s ^ (1 << i) ^ (1 << j)]) {
                        res = true;
                        break;
                    }
                }
            }
        }
        dp[s] = res;
    }

    cout << (dp[n2 - 1] ? "Takahashi" : "Aoki") << endl;
}
