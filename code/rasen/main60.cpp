// 関節点
#include <iostream>
#include <vector>
using namespace std;

const int NIL = -1;

vector<vector<int> > G;
vector<bool> Visited;
int cnt;

void solve(int apoint, int node_id) {
    if (Visited[node_id] || apoint == node_id) return;

    Visited[node_id] = true;
    for (int adj : G[node_id]) {
        solve(apoint, adj);
    }
    cnt++;
}

int main() {
    int n_node, n_edge; cin >> n_node >> n_edge;
    G = vector<vector<int> >(n_node);
    Visited = vector<bool>(n_node, false);

    for (int i = 0; i < n_edge; i++) {
        int in, out; cin >> in >> out;
        G[in].push_back(out);
        G[out].push_back(in);
    }

    vector<int> output;
    if (n_node > 1) {
        for (int i = 0; i < n_node; i++) {
            cnt = 0;
            Visited = vector<bool>(n_node, false);
            if (i == 0) solve(i, i + 1);
            else solve(i, i - 1);
            if (cnt != n_node - 1) output.push_back(i);
        }
    }

    for (int apoint : output) cout << apoint << endl;
}
