// 枝刈り(探索する順番を工夫する): p311
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 探索順を工夫した解法

int n = 9;
vector<vector<int>> grid(n, vector<int>(n));
vector<int> rows(n), cols(n);  // 各行列での0の個数

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

// 最も候補数が少ない行,列に属する位置を特定する: O(n)
pair<int, int> get_next() {
    int k = -1, minv = n + 1;  // 0の個数が少ない行列を選択する
    for (int i = 0; i < n; i++) {
        if (rows[i] > 0 && minv > rows[i]) {
            minv = rows[i];
            k = i;
        }
        if (cols[i] > 0 && minv > cols[i]) {
            minv = cols[i];
            k = i + n;
        }
    }
    if (k == -1) return make_pair(-1, -1);

    for (int i = 0; i < n; i++) {
        if (k >= n) {
            if (grid[i][k - n] == 0) return make_pair(k - n, i);
        } else {
            if (grid[k][i] == 0) return make_pair(i, k);
        }
    }
    return make_pair(-1, -1);
}

// 数字を配置することができるか判定
bool dfs(int x, int y) {
    if (x == -1 && y == -1) return true;

    for (int i = 1; i <= n; i++) {
        if (is_safe(i, x, y)) {
            grid[y][x] = i;
            rows[y]--; cols[x]--;

            // 候補数が少ない箇所から探索する
            auto [nx, ny] = get_next();
            if (dfs(nx, ny)) return true;

            grid[y][x] = 0;
            rows[y]++; cols[x]++;
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

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 0) rows[i]++;
            if (grid[j][i] == 0) cols[i]++;
        }
    }

    auto [x, y] = get_next();
    dfs(x, y);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }
}
