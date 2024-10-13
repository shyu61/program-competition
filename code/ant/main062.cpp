// 応用問題(Layout): p104
#include <bits/stdc++.h>
using namespace std;

// いわゆる牛ゲーと呼ばれる問題。"""重みが固定値ではなく不等式制約下での、2点の最大値を求める問題は、最短経路問題に帰着できる"""というもの。
// 直感的に理解するのは非常に難しいので、有名問題として押さえておく。
// ポイントは、最短経路問題は本質的には不等式制約下の最大値問題であるということ。du <= dv + eとしたとき、v->uへの最短経路はvがuの最短経路上に存在するときであり、
// この時等式が成立する。これはdu - dv <= eの最大値を求めていることに他ならない。
// これが牛ゲーにも当てはまる。このdu - dv <= eの形に不等式制約を変形し、v->uへeのedgeを張ったグラフにおける最短経路問題を解けば良いことになる。
// 通常の最大経路問題は、重みに-1をかけてベルマンフォードを使うことで解ける。

// すごいところは線形計画問題が、よりシンプルに最短経路問題として求解できる点。単体法などよりも遥かに効率的。

// TODO: 直感的な意味を見出す

struct Edge {
    int from, to, cost;
    Edge (int from, int to, int cost) : from(from), to(to), cost(cost) {};
};

const int INF = 1e9 + 1;
int n;
vector<Edge> es;

int bellmanFord() {
    vector<int> dist(n, INF);
    dist[0] = 0;
    int cnt = 0;
    for (int i = 0; ; i++) {
        bool update = false;
        for (auto e : es) {
            if (dist[e.to] > dist[e.from] + e.cost) {
                dist[e.to] = dist[e.from] + e.cost;
                update = true;;
            }
        }
        if (!update) break;
        if (i == n - 1) {
            // 負の閉路検出
            return -1;
        }
    }
    if (dist[n - 1] == INF) return -2;
    return dist[n - 1];
}

int main() {
    int ml, md; cin >> n >> ml >> md;
    for (int i = 0; i < n; i++) es.emplace_back(i, i - 1, 0);
    for (int i = 0; i < ml; i++) {
        int al, bl, dl; cin >> al >> bl >> dl;
        es.emplace_back(--al, --bl, dl);
    }
    for (int i = 0; i < md; i++) {
        int al, bl, dl; cin >> al >> bl >> dl;
        es.emplace_back(--bl, --al, -dl);
    }

    cout << bellmanFord() << endl;
}
