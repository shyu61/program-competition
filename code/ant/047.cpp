// 漸化式を工夫する(最長増加部分列問題): p63
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
const int INF = 1001001001;

// ポイント
// 「要素が小さい方が有利」といった貪欲的視点をdpに組み込むアプローチは頻出
// 部分列などを作る時は、長さよりも「最終要素」を添え字に持つ方法をよく使う

// O(NlogN)
int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    // 同じ長さのLISなら最終要素が小さい方が有利
    // dp[i]:=長さがi+1のLISにおける最終要素の最小値
    vector<int> dp(n, INF);
    rep(i, n) {
        *lower_bound(dp.begin(), dp.end(), a[i]) = a[i];
    }

    // dp[i]<INFとなる最大のiに対してi+1が解
    int ans = lower_bound(dp.begin(), dp.end(), INF) - dp.begin();
    cout << ans << endl;
}

// O(N^2)
int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    // dp[i]:=最後がa[i]であるLISの長さ
    vector<int> dp(n, 1);
    rep(i, n) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }

    int ans = 0;
    rep(i, n) ans = max(ans, dp[i]);
    cout << ans << endl;
}
