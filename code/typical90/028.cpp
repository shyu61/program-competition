#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int n; cin >> n;
    int m = 1000;
    vector<vector<int>> mas(m + 1, vector<int>(m + 1));
    rep(i, n) {
        int lx, ly, rx, ry; cin >> lx >> ly >> rx >> ry;
        mas[lx][ly]++;
        mas[lx][ry]--;
        mas[rx][ly]--;
        mas[rx][ry]++;
    }

    rep(i, m + 1) rep(j, m) mas[i][j + 1] += mas[i][j];
    rep(i, m) rep(j, m + 1) mas[i + 1][j] += mas[i][j];

    vector<int> ans(n + 1);
    rep(i, m + 1) rep(j, m + 1) ans[mas[i][j]]++;

    for (int i = 1; i <= n; i++) cout << ans[i] << '\n';
}
