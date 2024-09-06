// 全探索
// 部分和問題: p34
#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<int> a;

bool dfs(int i, int sum) {
    if (i == n) return sum == k;

    // 状態遷移を記述する
    // i番目を使う場合
    if (dfs(i + 1, sum + a[i])) return true;
    // i番目を使わない場合
    if (dfs(i + 1, sum)) return true;

    return false;
}

int main() {
    cin >> n >> k;
    a = vector<int>(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    cout << dfs(0, 0) << endl;
}
