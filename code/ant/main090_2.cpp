// ビットDP(ドミノ敷き詰め): p177
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 10007;

int main() {
    int n, m; cin >> n >> m;
    vector<vector<bool>> T(n, vector<bool>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c; cin >> c;
            if (c == 'x') T[i][j] = true;
        }
    }

    vector<vector<int>> dp(2, vector<int>(1 << m));

    // 現在地i,jについては2項間漸化式なので添え字は省略できる
    vector<int> &crt = dp[0], &next = dp[1];
    // vector<int> crt(1 << m), next(1 << m);  // こう書いてもOK
    crt[0] = 1;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            // 依存範囲である最終行の状態をループする
            for (int used = 0; used < 1 << m; used++) {
                // ブロックを置かない場合
                if ((used >> j & 1) || T[i][j]) {
                    next[used] = crt[used & ~(1 << j)];  // 現列の一つ下の行には何も配置されない
                } else {  // ブロックを置く場合
                    int res = 0;
                    // 横向き
                    if (j + 1 < m && !(used >> (j + 1) & 1) && !T[i][j + 1]) {
                        res += crt[used | 1 << (j + 1)];  // 隣にも配置
                    }
                    // 縦向き
                    if (i + 1 < n && !T[i + 1][j]) {
                        res += crt[used | 1 << j];  // 現列の一つ下の行に配置
                    }
                    next[used] = res % M;
                }
            }
            swap(crt, next);
        }
    }
    cout << crt[0] << endl;
}
