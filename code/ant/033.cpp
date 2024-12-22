// 部分話問題: p34
#include <bits/stdc++.h>
using namespace std;

// 全探索の組み合わせ問題。nCrのrは不定のパターン
// なので使うと使わないの2つをdfs内で再帰すれば良い

int n, k;
vector<int> a;
vector<bool> seen;

bool dfs(int sum, int d) {
    if (d == n) return sum == k;
    if (dfs(sum, d + 1)) return true;
    if (dfs(sum + a[d], d + 1)) return true;
    return false;
}

int main() {
    cin >> n;
    a = vector<int>(n);
    seen = vector<bool>(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    cin >> k;

    if (dfs(0, 0)) cout << "Yes" << endl;
    else cout << "No" << endl;
}
