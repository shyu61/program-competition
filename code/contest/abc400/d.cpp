#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;
const int INF = 1001001001;

// 初見でどうやったら解けるか
// 到達可能性問題だが、本質的には最短距離を問われているので、最短路問題として考える
// そうすると、壊す壁の個数を重みとしたedgeを持つグラフとしてグリッドを表現すれば良いことが思いつける
// 常に「最終的に求めるものは何か？」を考えると本質的な問題の性質が見える

const vector<int> dh = {1,-1,0,0}, dw = {0,0,-1,1};

int main() {
    int h, w; cin >> h >> w;
    vector<string> mas(h);
    rep(i, h) cin >> mas[i];
    int a, b, c, d; cin >> a >> b >> c >> d;
    a--, b--, c--, d--;

    vector<vector<P>> g(h * w);
    rep(i, h) rep(j, w) {
        int id = i * w + j;
        rep(r, 4) {
            int ni = i + dh[r], nj = j + dw[r];
            int nid = ni * w + nj;
            if (ni < 0 || ni >= h || nj < 0 || nj >= w) continue;
            if (mas[ni][nj] == '.') g[id].emplace_back(nid, 0);
            else {
                g[id].emplace_back(nid, 1);
                ni += dh[r], nj += dw[r];
                if (ni < 0 || ni >= h || nj < 0 || nj >= w) continue;
                g[id].emplace_back(ni * w + nj, 1);
            }
        }
    }

    vector<int> dist(h * w, INF);
    auto dijkstra = [&](int s) -> void {
        priority_queue<P, vector<P>, greater<P>> pq;
        pq.emplace(0, s);
        dist[s] = 0;
        while (!pq.empty()) {
            auto [c, v] = pq.top(); pq.pop();
            if (c > dist[v]) continue;
            for (auto [to, nc] : g[v]) {
                int nd = dist[v] + nc;
                if (nd < dist[to]) pq.emplace(dist[to] = nd, to);
            }
        }
    };

    dijkstra(a * w + b);
    cout << dist[c * w + d] << endl;
}
