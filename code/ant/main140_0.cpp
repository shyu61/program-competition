// 枝刈り(探索する順番を工夫する): p311
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 数独を満たしているかの判定をするプログラム

int n = 9;
vector<vector<int>> grid(n, vector<int>(n));

int main() {
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < n; j++) {
            grid[i][j] = s[j] - '0';
        }
    }

    // 横
    for (int i = 0; i < n; i++) {
        vector<bool> seen(n);
        for (int j = 0; j < n; j++) {
            if (seen[grid[i][j]]) {
                cout << "Invalid" << endl;
                return 0;
            }
            seen[grid[i][j]] = true;
        }
    }

    // 縦
    for (int i = 0; i < n; i++) {
        vector<bool> seen(n);
        for (int j = 0; j < n; j++) {
            if (seen[grid[j][i]]) {
                cout << "Invalid" << endl;
                return 0;
            }
            seen[grid[j][i]] = true;
        }
    }

    // 区画
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            int sx = x * 3, sy = y * 3;
            vector<bool> seen(n);
            for (int i = 0; i < n; i++) {
                int ny = sy + i / 3, nx = sx + i % 3;
                if (seen[grid[ny][nx]]) {
                    cout << "Invalid" << endl;
                    return 0;
                }
                seen[grid[ny][nx]] = true;
            }
        }
    }

    cout << "Valid" << endl;
}
