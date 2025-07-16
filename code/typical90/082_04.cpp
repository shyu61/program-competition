#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 🔷抑えるべき抽象論は？
// 確率/期待値の問題は、dpか組み合わせ論か
// - 組み合わせ論
//   - 操作に時差がなく全て同時に実行される場合
// - dp
//   - 操作が逐次的で累積的に確率が変化する場合
//   - https://blog.hamayanhamayan.com/entry/2016/11/14/223727
//   - 使える知識
//     - 期待値の線形性: dp[i] = Σj(dp[j]*Pj + Cj*Pj)
//     - 有効なのが来るまでカードを引く期待値は、有効なカードを引く確率の逆数

int main() {
    int n; cin >> n;

    // 連結成分数をiとすると、有効なカード(連結でない頂点)を引く確率は (n-i)/n
    // 故に期待値は n/(n-i) より Σi=1_to_n-1 n / (n-i)
    double ans = 0;
    for (int i = 1; i < n; i++) {
        ans += double(n) / (n - i);
    }
    cout << fixed << setprecision(8) << ans << endl;
}
