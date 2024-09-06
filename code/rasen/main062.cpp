// 木の直径: dfs
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<vector<pair<int, int>>> G;
vector<int> D;
vector<bool> seen;
int n_node;

void dfs(int v) {
    seen[v] = true;

    for (auto adj : G[v]) {
        if (seen[adj.first]) continue;
        D[adj.first] = D[v] + adj.second;
        dfs(adj.first);
    }
}

int diameter() {
    dfs(0);
    // 0から最も遠い点
    int u = distance(D.begin(), max_element(D.begin(), D.end()));

    seen = vector<bool>(n_node, false);
    D = vector<int>(n_node, 0);
    dfs(u);
    return *max_element(D.begin(), D.end());
}


int main() {
    cin >> n_node;
    seen = vector<bool>(n_node, false);
    G = vector<vector<pair<int, int>>>(n_node);
    D = vector<int>(n_node, 0);

    for (int i = 0; i < n_node - 1; i++) {
        int u, v, w; cin >> u >> v >> w;
        G[u].push_back(make_pair(v, w));
        G[v].push_back(make_pair(u, w));
    }

    cout << diameter() << endl;
}
