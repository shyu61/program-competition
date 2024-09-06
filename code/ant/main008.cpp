// ナップサック問題: p52
// メモ化再帰
#include <bits/stdc++.h>
using namespace std;

int n, W;
vector<int> v, w;
vector<vector<int>> memo;

int rec(int i, int wc) {
    // メモ化テーブルがどっちから埋まっていくかを意識する
    // i==nから埋まっていくのでreturn 0
    if (i == n) return 0;
    if (memo[i][wc] != -1) return memo[i][wc];

    int maxv = -1;
    if (wc + w[i] > W) {
        maxv = max(maxv, rec(i + 1, wc));
    } else {
        maxv = max(
            rec(i + 1, wc + w[i]) + v[i],
            rec(i + 1, wc)
        );
    }

    return memo[i][wc] = maxv;
}

int main() {
    cin >> n >> W;
    v = w = vector<int>(n);
    memo = vector<vector<int>>(n + 1, vector<int>(W + 1, -1));
    for (int i = 0; i < n; i++) cin >> v[i] >> w[i];

    int maxv = rec(0, 0);
    cout << maxv << endl;
}
