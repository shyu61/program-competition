#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using TP = tuple<int, int, int>;
const int INF = 1001001001;

// 🔷初見でどうやったら解けるか
// 方向転換の回数の最小化問題 → 方向が変わる方向への遷移をコスト1,変わらない遷移をコスト0として最短路問題を解けばよい
// 01はダイクストラせずともbfsでO(V)で解ける

// 上下左右
const vector<int> dx = {1,-1,0,0,}, dy = {0,0,1,-1};

int main() {
    int h, w, si, sj, ti, tj;
    cin >> h >> w >> si >> sj >> ti >> tj;
    si--, sj--, ti--, tj--;
    vector<string> mas(h);
    rep(i, h) cin >> mas[i];

    deque<TP> deq;
    vector<vector<vector<int>>> dist(h, vector<vector<int>>(w, vector<int>(4, INF)));
    rep(r, 4) {
        dist[si][sj][r] = 0;
        deq.emplace_back(si, sj, r);
    }

    while (!deq.empty()) {
        auto [i, j, pre] = deq.front(); deq.pop_front();
        rep(r, 4) {
            int ni = i + dx[r], nj = j + dy[r];
            if (ni < 0 || ni >= h || nj < 0 || nj >= w) continue;
            if (mas[ni][nj] != '.') continue;
            int cost = (r == pre) ? 0 : 1;
            // dist[i][j][pre]の所を、dist[i][j][r]としないよう注意
            if (dist[ni][nj][r] > dist[i][j][pre] + cost) {
                dist[ni][nj][r] = dist[i][j][pre] + cost;
                if (r == pre) deq.emplace_front(ni, nj, r);
                else deq.emplace_back(ni, nj, r);
            }
        }
    }
    int ans = INF;
    rep(r, 4) ans = min(ans, dist[ti][tj][r]);
    cout << ans << endl;
}
