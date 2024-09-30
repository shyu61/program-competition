#include <bits/stdc++.h>
using namespace std;

// 重みなしの最短経路問題 -> bfsで解く
// bfsはサイクルを防ぐため頂点の再訪をチェックする必要がある。seenやdistでも良いし、今回のように訪問済みのマスをfalseに変更しても同じことが実現できる
// 要はすでに訪れたかどうかが判定できれば良い

vector<vector<int>> r{{-1,0},{0,-1},{0,1},{1,0}};

int main() {
    int n, m; cin >> n >> m;
    vector<vector<bool>> a(n, vector<bool>(m));

    pair<int, int> s, t;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c; cin >> c;
            if (c == '.') a[i][j] = true;
            if (c == 'S') s = make_pair(i, j);
            if (c == 'G') t = make_pair(i, j);
        }
    }

    vector<vector<int>> dist(n, vector<int>(m));
    queue<pair<int, int>> que; que.push(s);
    while (!que.empty()) {
        auto [y, x] = que.front(); que.pop();
        for (int i = 0; i < 4; i++) {
            int ny = y + r[i][0];
            int nx = x + r[i][1];
            if (ny >= 0 && ny < n && nx >= 0 && nx < m) {
                if (ny == t.first && nx == t.second) {
                    cout << dist[y][x] + 1 << endl;
                    return 0;
                }
                if (a[ny][nx]) {
                    a[ny][nx] = false;
                    dist[ny][nx] = dist[y][x] + 1;
                    que.emplace(ny, nx);
                }
            }
        }
    }
    cout << -1 << endl;
}
