// MST: プリム法 with priority_queue
#include <iostream>
#include <vector>
#include <limits>
#include <queue>
using namespace std;
const int INF = numeric_limits<int>::max();

struct Edge {
    int to, w;
    bool operator<(const Edge& other) const {
        return w > other.w;
    };
};

vector<vector<Edge>> G;
vector<int> W;
int n_node, n_edge;

int prim(int v) {
    priority_queue<Edge> pque;
    int total = 0;
    vector<bool> in_mst(n_node, false);
    vector<int> w(n_node, INF);
    w[v] = 0;
    pque.push(Edge{v, 0});

    while (!pque.empty()) {
        Edge edge = pque.top(); pque.pop();

        // 更新が複数回走った点の残存キューはここで弾かれる
        // if (in_mst[edge.to]) continue;
        if (w[edge.to] < edge.w) continue;

        in_mst[edge.to] = true;
        total += edge.w;

        // wの更新
        for (Edge adj : G[edge.to]) {
            if (!in_mst[adj.to] && adj.w < w[adj.to]) {
                w[adj.to] = adj.w;
                // 更新されたものが次の候補
                // すでにmstに含まれるものは必ず重みが最小になるので、更新されることはない
                pque.push(adj);
            }
        }
    }
    return total;
}

int main() {
    cin >> n_node >> n_edge;
    G = vector<vector<Edge>>(n_node);
    W = vector<int>(n_node);

    for (int i = 0; i < n_edge; i++) {
        int u, v, w; cin >> u >> v >> w;
        G[u].push_back(Edge{v, w});
        G[v].push_back(Edge{u, w});
    }

    cout << prim(0) << endl;
}
