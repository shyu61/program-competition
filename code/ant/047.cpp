// 漸化式を工夫する(最長増加部分列問題): p63
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 1;

// 単調性があり各a[i]あたり更新は1回のみという性質から、二分探索で挿入位置を探索すれば良いことになる
// 単調性があるのはdpの設計上自明。各a[i]が1回ずつしか挿入されないことは、a[i]は自身より小さい要素の後でしか増加列を形成できず、自身より大きい要素の前でしか増加列を形成できないから。
int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> dp(n, INF);
    for (int i = 0; i < n; i++) {
        *lower_bound(dp.begin(), dp.end(), a[i]) = a[i];
    }

    int ans = lower_bound(dp.begin(), dp.end(), INF) - dp.begin();
    cout << ans << endl;
}

// dp[i]: 長さiの最小末尾
// これはLISの性質を活かしたdpの設計。基本はナップサックDPで考えるが、その問題の性質を活かした設計をすることで、より計算量を落とすことができる場合がある。
// LISが同じ長さなら末尾が小さい方が有利という発想に基づいているが、これは文字列や数列の問題ではあるあるで、貪欲的な考え方である。
int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> dp(n, INF);
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n; i++) {
            if (i == 0 || dp[i - 1] < a[j]) {
                dp[i] = min(dp[i], a[j]);
            }
        }
    }

    int ans = 1;
    for (int i = 0; i < n; i++) {
        if (dp[i] < INF) ans = i + 1;
    }

    cout << ans << endl;
}

// int main() {
//     int n; cin >> n;
//     vector<int> a(n);
//     for (int i = 0; i < n; i++) cin >> a[i];

//     vector<int> dp(n, 1);
//     int maxv = 0;
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < i; j++) {
//             if (a[j] < a[i]) {
//                 dp[i] = max(dp[i], dp[j] + 1);
//             }
//         }
//         maxv = max(maxv, dp[i]);
//     }

//     cout << maxv << endl;
// }
