#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using P = pair<int, int>;

// ジャンル
// - グリッド問題, 到達可能性問題, 最短経路問題

// 方針
// 最短経路問題なのでbfsで考える。進み方に制約があるので丁寧に実装する
// 縦横交互制約はdistの偶奇で分岐
// 再訪管理しつつ'G'にたどり着いた時点でreturnする

// ポイント
// 交互は偶奇で分岐

const int INF = 1e6 + 1;
int H, W;
vector<vector<char>> g;

int bfs(P s, bool vd) {
    queue<P> que; que.push(s);
    vector<vector<int>> dist(H, vector<int>(W, INF)); dist[s.first][s.second] = 0;
    while (!que.empty()) {
        auto [x, y] = que.front(); que.pop();
        if (g[x][y] == 'G') return dist[x][y];

        if (vd ? dist[x][y] % 2 == 0 : dist[x][y] % 2 == 1) {
            // 縦に進む
            for (auto v : {-1, 1}) {
                int nx = x + v;
                if (nx >= 0 && nx < H) {
                    if (g[nx][y] == 'G') return dist[x][y] + 1;
                    if (g[nx][y] == '.' && dist[nx][y] == INF) {
                        que.emplace(nx, y);
                        dist[nx][y] = dist[x][y] + 1;
                    }
                }
            }
        } else {
            // 横に進む
            for (auto v : {-1, 1}) {
                int ny = y + v;
                if (ny >= 0 && ny < W) {
                    if (g[x][ny] == 'G') return dist[x][y] + 1;
                    if (g[x][ny] == '.' && dist[x][ny] == INF) {
                        que.emplace(x, ny);
                        dist[x][ny] = dist[x][y] + 1;
                    }
                }
            }
        }
    }
    return INF;
}

int main() {
    cin >> H >> W;
    g = vector<vector<char>>(H, vector<char>(W));
    P s;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            char c; cin >> c;
            g[i][j] = c;
            if (c == 'S') s = make_pair(i, j);
        }
    }

    int res = min(bfs(s, true), bfs(s, false));
    cout << (res == INF ? -1 : res) << endl;
}
