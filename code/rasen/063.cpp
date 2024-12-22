// 木の直径: bfs
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Edge {
    int to, w;
};

vector<vector<Edge>> G;
vector<int> D;
vector<bool> seen;
int n_node;

void bfs(int v) {
    queue<int> que;
    que.push(v); seen[v] = true;

    while (!que.empty()) {
        int v = que.front(); que.pop();

        for (auto adj : G[v]) {
            if (seen[adj.to]) continue;
            D[adj.to] = D[v] + adj.w;
            que.push(adj.to);
            seen[adj.to] = true;
        }
    }
}

int diameter() {
    bfs(0);
    // 0から最も遠い点
    int u = distance(D.begin(), max_element(D.begin(), D.end()));

    seen = vector<bool>(n_node, false);
    D = vector<int>(n_node, 0);
    bfs(u);
    return *max_element(D.begin(), D.end());
}


int main() {
    cin >> n_node;
    seen = vector<bool>(n_node, false);
    G = vector<vector<Edge>>(n_node);
    D = vector<int>(n_node, 0);

    for (int i = 0; i < n_node - 1; i++) {
        int u, v, w; cin >> u >> v >> w;
        G[u].push_back(Edge{v, w});
        G[v].push_back(Edge{u, w});
    }

    cout << diameter() << endl;
}
