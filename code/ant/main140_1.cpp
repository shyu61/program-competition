// 枝刈り(探索する順番を工夫する): p311
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ナイーブな実装

int n = 9;
vector<vector<int>> grid(n, vector<int>(n));

bool is_safe(int v, int x, int y) {
    int sx = x / 3 * 3, sy = y / 3 * 3;
    // 同じ行,列,区画にvがないか確認
    for (int i = 0; i < n; i++) {
        if (i != x && grid[y][i] == v) return false;
        if (i != y && grid[i][x] == v) return false;

        int nx = sx + (i % 3), ny = sy + (i / 3);
        if ((nx != x || ny != y) && grid[ny][nx] == v) return false;
    }
    return true;
}

// 数字を配置することができるか判定
bool dfs(int x, int y) {
    if (y >= n) return true;

    int nx = (x + 1) % n, ny = y + (x + 1) / n;
    if (grid[y][x] != 0) return dfs(nx, ny);

    for (int i = 1; i <= n; i++) {
        if (is_safe(i, x, y)) {
            grid[y][x] = i;
            if (dfs(nx, ny)) return true;
            grid[y][x] = 0;
        }
    }
    return false;
}

int main() {
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < n; j++) {
            grid[i][j] = s[j] - '0';
        }
    }

    dfs(0, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }
}
