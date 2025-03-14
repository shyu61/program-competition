#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// ポイント
// grundy数は常に非負整数で持つ必要がある
// grundy数は一つのサブゲームに対して全状態を走査できる必要がある
// grundy数は状態を一意に決める値である必要はなく、grundy数=0がゲームの終了条件となるような値であれば良い

int main() {
    int n; cin >> n;
    vector<int> w(n), b(n);
    rep(i, n) cin >> w[i];
    rep(i, n) cin >> b[i];

    int maxw = 50, maxb = 50 + maxw * (maxw + 1) / 2;
    vector<vector<int>> grundy(maxw + 1, vector<int>(maxb + 1));
    for (int i = 0; i <= maxw; i++) {
        for (int j = 0; j <= maxb; j++) {
            vector<int> mex(maxw + maxb + 1);
            if (i >= 1) {
                if (j + i <= maxb) mex[grundy[i - 1][j + i]]++;
            }
            if (j >= 2) {
                for (int k = 1; k <= j / 2; k++) {
                    mex[grundy[i][j - k]]++;
                }
            }
            rep(k, maxw + maxb + 1) {
                if (mex[k] == 0) {
                    grundy[i][j] = k;
                    break;
                }
            }
        }
    }

    int res = 0;
    rep(i, n) res ^= grundy[w[i]][b[i]];

    if (res) cout << "First" << endl;
    else cout << "Second" << endl;
}
