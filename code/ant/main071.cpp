// Bribe the Prisoners: p121
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 棒切り問題の一種。典型的な逐次問題なのでDPで解く
// DPを考えるとき重要なのは、遷移式と小問題の設計
// 多くはどういう遷移をするから、どう小問題を設計すべき（どう状態を持つべき）かが決まる。
// 今回は、1人解放した時にコストはその囚人が属する連結成分（区間長）に依存することがわかる
// つまり状態も区間について持てば良く、ゴールはdp[0][q+1]を求めることだと気付ける

// 忘れがちだがdpは再帰構造を持っている。目的を達成するために分割して計算されそれが統治することで求解する。
// このイメージを忘れないこと

// またこの問題は棒切り問題の一種であり、
// 2分割を繰り返していく場合のコスト最小化問題はDPで区間コストに関する状態遷移を記述すれば良いと覚えておくと良い


int main() {
    int p, q; cin >> p >> q;
    vector<int> a(q + 2);
    a[0] = 0; a[q + 1] = p + 1;
    for (int i = 0; i < q; i++) cin >> a[i];

    sort(a.begin(), a.end());
    vector<vector<int>> dp(q + 2, vector<int>(q + 2));

    for (int w = 2; w <= q + 1; w++) {
        for (int i = 0; i + w <= q + 1; i++) {
            int minv = p;
            for (int k = i + 1; k < i + w; k++) {
                minv = min(minv, dp[i][k] + dp[k][i + w]);
            }
            dp[i][i + w] = minv + (a[i + w] - a[i] - 2);
        }
    }
    cout << dp[0][q + 1] << endl;
}
