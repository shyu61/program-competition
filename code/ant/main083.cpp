// 座標圧縮: p150
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 座標圧縮を検討するポイント
// 1. 探索がsparseであること: 探索領域に対して、なんらかの処理をしたいものがsparseである場合
// 2. 区間/領域問題であること: 構造上圧縮しても本質を損なわないことが多い

// 初めから座標圧縮を検討するのではなく、考えた解法が計算量的に厳しい時に検討する。
// 領域の個数の問題 -> 到達可能性問題 -> dfsすれば良い -> O(V+E)はTLEする -> 線分があるタイルは非常にsparse(10^6に対して高々500しかない)
// -> 座標圧縮したいなぁ -> 領域の問題であり本質を損なわないように圧縮できそう

int W, H, N;
vector<int> dx = {0,1,0,-1};
vector<int> dy = {1,0,-1,0};

int compress(vector<int> &x1, vector<int> &x2, int maxd) {
    vector<int> nx;

    // 必要な行/列を抽出
    for (int i = 0; i < N; i++) {
        for (int d = -1; d <= 1; d++) {
            int tx1 = x1[i] + d, tx2 = x2[i] + d;
            if (tx1 >= 0 && tx1 < maxd) nx.push_back(tx1);
            if (tx2 >= 0 && tx2 < maxd) nx.push_back(tx2);
        }
    }
    // 重複を削除
    sort(nx.begin(), nx.end());
    nx.erase(unique(nx.begin(), nx.end()), nx.end());

    // 各要素の値を圧縮
    for (int i = 0; i < N; i++) {
        x1[i] = find(nx.begin(), nx.end(), x1[i]) - nx.begin();
        x2[i] = find(nx.begin(), nx.end(), x2[i]) - nx.begin();
    }

    return nx.size();
}

int main() {
    cin >> W >> H >> N;
    vector<int> x1(N), x2(N), y1(N), y2(N);
    for (int i = 0; i < N; i++) {
        cin >> x1[i] >> x2[i] >> y1[i] >> y2[i];
        x1[i]--; x2[i]--; y1[i]--; y2[i]--;
    }

    // 座標圧縮
    W = compress(x1, x2, W);
    H = compress(y1, y2, H);

    // タイルの作成
    vector<vector<bool>> tile(H, vector<bool>(W));
    for (int i = 0; i < N; i++) {
        for (int y = y1[i]; y <= y2[i]; y++) {
            for (int x = x1[i]; x <= x2[i]; x++) {
                tile[y][x] = true;
            }
        }
    }

    // bfs
    ll ans = 0;
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            if (tile[y][x]) continue;
            ans++;

            queue<pair<int, int>> que;
            que.emplace(x, y);
            tile[y][x] = true;
            while (!que.empty()) {
                auto [tx, ty] = que.front(); que.pop();

                for (int r = 0; r < 4; r++) {
                    int nx = tx + dx[r];
                    int ny = ty + dy[r];
                    if (nx >= 0 && nx < W && ny >= 0 && ny < H && !tile[ny][nx]) {
                        tile[ny][nx] = true;
                        que.emplace(nx, ny);
                    }
                }
            }
        }
    }

    cout << ans << endl;
}
