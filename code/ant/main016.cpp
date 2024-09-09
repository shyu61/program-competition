#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<vector<int>> routes{{0,1},{1,0},{0,-1},{-1,0}};

int main() {
    int n, m; cin >> n >> m;
    pair<int, int> s, g;
    vector<vector<bool>> a(n, vector<bool>(m, true));

    string is;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c; cin >> c;
            if (c == 'S') s = make_pair(i, j);
            else if (c == 'G') g = make_pair(i, j);
            else if (c == '#') a[i][j] = false;
        }
    }

    queue<pair<int, int>> que;
    vector<vector<int>> dist(n, vector<int>(m, -1));
    que.push(s);
    dist[s.first][s.second] = 0;
    while (!que.empty()) {
        auto [row, col] = que.front(); que.pop();
        if (row == g.first && col == g.second) break;
        for (auto r : routes) {
            int nr = row + r[0];
            int nc = col + r[1];
            if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                if (!a[nr][nc]) continue;
                if (dist[nr][nc] != -1) continue;
                que.emplace(nr, nc);
                dist[nr][nc] = dist[row][col] + 1;
            }
        }
    }

    cout << dist[g.first][g.second] << endl;
}
