// 個数制限付きナップサック
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 2の累乗和で任意の整数が表せるという性質はいろんなところで出てくる
// 使える条件は、問題構造的に分割して良いこと。

int main() {
    int n; cin >> n;
    vector<int> w(n), v(n), m(n);
    for (int i = 0; i < n; i++) cin >> w[i] >> v[i] >> m[i];
    int W; cin >> W;

    vector<int> dp(W + 1);
    for (int i = 0; i < n; i++) {
        int num = m[i];
        // i番目について、2の累乗ごとに複製する
        for (int k = 1; num > 0; k <<= 1) {
            int mul = min(k, num);  // 残りの個数numを超えないよう調整
            // 同じ配列を再利用するときは後ろから走査する
            // <- 前の項に依存する場合、前の項は更新前である必要があるので、後ろから更新していく必要がある
            for (int j = W; j >= w[i] * mul; j--) {
                dp[j] = max(dp[j], dp[j - w[i] * mul] + v[i] * mul);
            }
            num -= mul;
        }
    }
    cout << dp[W] << endl;
}
