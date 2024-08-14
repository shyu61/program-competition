// 木の直径: dfs
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Edge { int to, w; };

vector<vector<Edge>> G;
vector<int> D;
int n_node;

void dfs(int v, int p) {
    for (auto adj : G[v]) {
        if (adj.to == p) continue;
        D[adj.to] = D[v] + adj.w;
        dfs(adj.to, v);
    }
}

int diameter() {
    dfs(0, -1);
    // 0から最も遠い点
    int u = distance(D.begin(), max_element(D.begin(), D.end()));

    D = vector<int>(n_node, 0);
    dfs(u, -1);
    return *max_element(D.begin(), D.end());
}


int main() {
    cin >> n_node;
    G = vector<vector<Edge>>(n_node);
    D = vector<int>(n_node, 0);

    for (int i = 0; i < n_node - 1; i++) {
        int u, v, w; cin >> u >> v >> w;
        G[u].push_back(Edge{v, w});
        G[v].push_back(Edge{u, w});
    }

    cout << diameter() << endl;
}
