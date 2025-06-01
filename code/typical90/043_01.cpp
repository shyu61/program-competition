#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using TP = tuple<int, int, int, int>;
const int INF = 1001001001;

// 🔷抑えるべき抽象論は？
// 複雑な設定のグリッド問題は重みなどを使ってグラフに直せるかが重要
// 重みが01の最短路問題は01bfsを使う
// - bfsとの違いは、
//   - 常にpush_backするのではなく、0の時はpush_front, 1の時はpush_backとする
//   - 更新条件を、未訪問(dist[v]!=-1)ではなく、最短性(dist[v]>dist[u]+w)とする
// 距離問題において、遷移元情報を条件判定に使う時は、使う距離にも注意すること

// 上下左右
const vector<int> dx = {1,-1,0,0,}, dy = {0,0,1,-1};

int main() {
    int h, w, si, sj, ti, tj;
    cin >> h >> w >> si >> sj >> ti >> tj;
    si--, sj--, ti--, tj--;
    vector<string> mas(h);
    rep(i, h) cin >> mas[i];

    // dijkstra
    priority_queue<TP, vector<TP>, greater<TP>> pq;
    vector<vector<vector<int>>> dist(h, vector<vector<int>>(w, vector<int>(4, INF)));
    rep(r, 4) dist[si][sj][r] = 0;
    pq.emplace(0, si, sj, -1);

    while (!pq.empty()) {
        auto [d, i, j, pre] = pq.top(); pq.pop();
        if (d > dist[i][j][pre]) continue;
        rep(r, 4) {
            int ni = i + dx[r], nj = j + dy[r];
            if (ni < 0 || ni >= h || nj < 0 || nj >= w) continue;
            if (mas[ni][nj] != '.') continue;
            int cost = (pre == r || pre == -1) ? 0 : 1;
            int nd = d + cost;
            if (dist[ni][nj][r] > nd) pq.emplace(dist[ni][nj][r] = nd, ni, nj, r);
        }
    }
    int ans = INF;
    rep(r, 4) ans = min(ans, dist[ti][tj][r]);
    cout << ans << endl;
}
