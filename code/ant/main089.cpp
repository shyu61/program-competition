// データ構造を用いて高速化: p186
#include <bits/stdc++.h>
using namespace std;

// dpの立式自体は典型的なナップサック問題
// dpの計算量を減らすテクの一つに離散的にしか値を取り得ない場合にループをそれに合わせて実行する方法がある
// O(nm)で間に合わないからDPを高速化したい -> jは離散的でありt[i+1]だけ調べれば良い -> jのループをなくせる -> 最小値検索は区間の最小値なのでRMQでやればO(logn)で実行できる

// ループを回す時、全体を回してるのか、ある区間を回しているのかを意識しておくと良い。

const int INF = 5e5 + 1;
int n, m, sz = 1;
vector<int> s, t;
vector<int> dp, dat;

void init() {
    while (sz < n) sz *= 2;
    dat = vector<int>(sz * 2 - 1, INF);
}

void update(int k, int a) {
    int id = k + sz - 1;
    dat[id] = a;
    while (id > 0) {
        id = (id - 1) / 2;
        dat[id] = min(dat[id * 2 + 1], dat[id * 2 + 2]);
    }
}

int query(int a, int b, int id, int left, int right) {
    if (b <= left || right <= a) return INF;
    if (a <= left && right <= b) return dat[id];
    else {
        int vl = query(a, b, id * 2 + 1, left, (left + right) / 2);
        int vr = query(a, b, id * 2 + 2, (left + right) / 2, right);
        return min(vl, vr);
    }
}

int main() {
    cin >> n >> m;
    s = t = vector<int>(m + 1);
    for (int i = 1; i <= m; i++) cin >> s[i] >> t[i];

    dp = vector<int>(n + 1, INF);
    dp[0] = 0;
    init();
    update(1, 0);
    for (int i = 0; i < m; i++) {
        int v = min(dp[t[i + 1]], query(s[i + 1], t[i + 1] + 1, 0, 0, sz) + 1);
        dp[t[i + 1]] = v;
        update(t[i + 1], v);
    }
    cout << dp[n] << endl;
}

// int main() {
//     cin >> n >> m;
//     s = t = vector<int>(m + 1);
//     for (int i = 1; i <= m; i++) cin >> s[i] >> t[i];

//     // i番目までを考える時、値がjまでソート済みの時の最小個数
//     dp = vector<vector<int>>(m + 1, vector<int>(n + 1, INF));
//     dp[0][1] = 0;
//     for (int i = 0; i < m; i++) {
//         for (int j = 0; j <= n; j++) {
//             // i+1番目のsorterを使う時、最大値はt[i+1]に移動する
//             if (j == t[i + 1]) {
//                 int minv = INF;
//                 // i+1番目のsorterはs[i+1]からしか移動できないので、dp[i]の時点でそれ以上に最大値が移動している必要がある
//                 for (int k = s[i + 1]; k <= t[i + 1]; k++) {
//                     minv = min(minv, dp[i][k]);
//                 }
//                 dp[i + 1][j] = min(dp[i][j], minv + 1);
//             } else {
//                 dp[i + 1][j] = dp[i][j];
//             }
//         }
//     }

//     cout << dp[m][n] << endl;
// }
