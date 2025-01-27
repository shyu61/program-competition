#include <bits/stdc++.h>
using namespace std;

// ジャンル
// 組合せ最適化, ナップサックdp, 最小の最大化

// 方針
// 最小の最大化とくれば二分探索、つまり判定問題で考える

// ポイント
// 複数同時最適化問題は直接解くのは難しい
// -> 部分問題間の依存性が弱い場合は判定問題で解けることが多い(判定問題にすることで独立に扱える)
// -> 最小値の最大化などは典型的に部分問題間の依存性が弱いことが多い
// 部分問題間の依存性が弱いとは: 合計値やリソース総量などの関係性のみの場合

int main() {
    int n, x; cin >> n >> x;
    vector<vector<int>> a(3), c(3);
    for (int i = 0; i < n; i++) {
        int v, ai, ci; cin >> v >> ai >> ci;
        a[--v].push_back(ai);
        c[v].push_back(ci);
    }

    vector<vector<int>> dp(3, vector<int>(x + 1));
    for (int r = 0; r < 3; r++) {
        for (int i = 0; i < a[r].size(); i++) {
            vector<int> old(x + 1);
            swap(dp[r], old);
            for (int j = 0; j <= x; j++) {
                if (j - c[r][i] >= 0) {
                    dp[r][j] = max(old[j - c[r][i]] + a[r][i], old[j]);
                } else dp[r][j] = old[j];
            }
        }
    }

    auto check = [&](int mid) -> bool {
        int sum = 0;
        for (int r = 0; r < 3; r++) {
            int i = lower_bound(dp[r].begin(), dp[r].end(), mid) - dp[r].begin();
            if (i == dp[r].size()) return false;
            sum += i;
        }
        return sum <= x;
    };

    // 全てのビタミンをlb以上にできるかを二分探索
    int lb = 0, ub = 1e9 + 1;
    while (ub - lb > 1) {
        int mid = (lb + ub) / 2;
        check(mid) ? lb = mid : ub = mid;
    }
    cout << lb << endl;
}
