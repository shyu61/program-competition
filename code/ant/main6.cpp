// Lake Counting: p35
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, m;
vector<vector<bool>> yard;
vector<vector<bool>> seen;
vector<vector<int>> r{{-1,-1},{0,-1},{1,-1},{-1,0},{1,0},{-1,1},{0,1},{1,1}};

void dfs(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m || seen[x][y]) return;
    seen[x][y] = true;

    if (!yard[x][y]) return;

    for (int j = 0; j < 8; j++) {
        dfs(x + r[j][0], y + r[j][1]);
    }
}

int main() {
    cin >> n >> m;
    yard = vector<vector<bool>>(n, vector<bool>(m, false));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c; cin >> c;
            yard[i][j] = c == 'W';
        }
    }

    int cnt = 0;
    seen = vector<vector<bool>>(n, vector<bool>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!seen[i][j] && yard[i][j]) {
                dfs(i, j);
                cnt++;
            }
        }
    }
    cout << cnt << endl;
}
