// MST: プリム法
#include <iostream>
#include <vector>
#include <limits>
using namespace std;
const int INF = numeric_limits<int>::max();

struct Edge { int to, w; };

vector<vector<Edge>> G;
vector<int> W;
int n_node, n_edge;

int prim(int v) {
    int total = 0;
    vector<bool> in_mst(n_node, false);
    vector<int> w(n_node, INF);
    w[v] = 0;

    while (true) {
        int minv = INF; int u = -1;
        for (int i = 0; i < n_node; i++) {
            if (in_mst[i]) continue;
            if (w[i] < minv) {
                minv = w[i]; u = i;
            }
        }

        if (u == -1) break;

        in_mst[u] = 1;
        total += minv;

        // wの更新
        for (auto adj : G[u]) {
            if (adj.w < w[adj.to]) {
                w[adj.to] = adj.w;
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
