#include <bits/stdc++.h>
#include <lib/union_find.cpp>
using namespace std;
using P = pair<int, int>;

// MSTアルゴリズム
// - プリム法: O(ElogV)
//   - 一つの木を成長させていく戦略
//   - 適当な点から始めて、現在の木に隣接するedgeのうち最小のものを木に加えることを繰り返す
// - クラスカル法: O(ElogE)
//   - それぞれ木を成長させmergeしていく戦略
//   - 重みが小さいedgeから順に見ていき、閉路を形成しない限りmstに加えていく

int prim(int s, int n, const vector<vector<P>>& G) {
    priority_queue<P, vector<P>, greater<P>> pq;
    vector<bool> in_mst(n);
    pq.emplace(0, s);

    int total = 0;
    while (!pq.empty()) {
        auto [c, v] = pq.top(); pq.pop();
        if (in_mst[v]) continue;
        in_mst[v] = true;
        total += c;
        for (auto [to, cost] : G[v]) {
            if (in_mst[to]) continue;
            pq.emplace(cost, to);
        }
    }
    return total;
}


int kruskal(int n, const vector<tuple<int, int, int>>& edges) {
    sort(edges.begin(), edges.end());

    UnionFind uf(n);
    int total = 0;
    for (auto [c, u, v] : edges) {
        if (uf.same(u, v)) continue;
        uf.unite(u, v);
        total += c;
    }
    return total;
}
