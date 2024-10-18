// 応用問題(Roadblocks): p102
#include <bits/stdc++.h>
using namespace std;

// 2番目の最短経路を求める問題。
// 1. SSSPのアルゴリズムを改変して解くか全く別のアプローチで解くかを考える。後者はコストが高いので一旦前者で行けると仮定して考える。
// 2. ダイクストラかベルマンフォードどちらでいくかを考えるが、負の重みがないので一旦ダイクストラで考えてみる。
// 3. まず最短経路を求めてから2番目の経路を求めるか、ダイクストラの実行中に一緒に2番目の経路も求めるかを考える。
// 最短経路木を元に2番目を導けるかを考えたときに、そう簡単には導けなさそうと思えれば、ダイクストラを実行しながら2番目の経路も同時の保持する方が良さそうだと思いつける。
// ハフマン木を使った2分割を繰り返していくコストの最小化問題でも、各ステップ内で最小と2番目に小さい要素を抽出していた。つまり逐次的なアルゴリズムにおいて、各ステップで2つの最小値を取り出すことは容易であるとわかる。
// 4. ダイクストラは最短距離を更新していくが、その際に同時に2番目も保持すればよい。ここで注意点は更新対象が2つになったということ。
// d2の更新時にpqにpushしないと正しいd2が導かれない。しかしこの要素はdの更新には影響を与えない(常にd2>=dが成立するため)。ゆえに早期return条件もd2に対して行う必要がある。

struct Edge {
    int to, cost;
    Edge(int to, int cost): to(to), cost(cost) {};
};

const int INF = 5e8 + 1;

int main() {
    int n, m; cin >> n >> m;
    vector<vector<Edge>> G(n);
    for (int i = 0; i < m; i++) {
        int u, v, cost; cin >> u >> v >> cost;
        u--; v--;
        G[u].emplace_back(v, cost);
        G[v].emplace_back(u, cost);
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, 0);
    vector<int> d(n, INF), d2(n, INF);  // 各頂点への2番目の最短路
    d[0] = d2[0] = 0;

    while (!pq.empty()) {
        auto [cost, v] = pq.top(); pq.pop();
        if (cost > d2[v]) continue;

        for (auto adj : G[v]) {
            int cand = d[v] + adj.cost;

            if (d[adj.to] > cand) {
                swap(d[adj.to], cand);
                pq.emplace(d[adj.to], adj.to);
            } else if (d2[adj.to] > cand) {
                d2[adj.to] = cand;
                pq.emplace(d2[adj.to], adj.to);
            }
        }
    }

    cerr << d[n - 1] << endl;
    cout << d2[n - 1] << endl;
}
