// トポロジカルソート: BFS
#include <iostream>
#include <queue>
#include <list>
#include <vector>
using namespace std;

const int MAX_NODE = 10000;

vector<vector<int> > G;
vector<int> InDeg;  // 入次数
list<int> OUT;
vector<bool> Used;

void tsort(int node_id) {
    if (Used[node_id] || InDeg[node_id] != 0) return;

    // bfs
    queue<int> Q;
    Q.push(node_id);
    OUT.push_back(node_id);
    Used[node_id] = true;
    while (!Q.empty()) {
        int v = Q.front(); Q.pop();

        for (int adj : G[v]) {
            if (Used[adj]) continue;
            InDeg[adj]--;
            if (InDeg[adj] == 0) {
                Q.push(adj);
                OUT.push_back(adj);
                Used[adj] = true;
            }
        }
    }
}

int main() {
    int n_node, n_edge; cin >> n_node >> n_edge;
    G = vector<vector<int> >(n_node);
    InDeg = vector<int>(n_node, 0);
    Used = vector<bool>(n_node, false);

    for (int i = 0; i < n_edge; i++) {
        int in, out; cin >> in >> out;
        G[in].push_back(out);
        InDeg[out]++;
    }

    for (int i = 0; i < n_node; i++) {
        tsort(i);
    }

    for (list<int>::iterator it = OUT.begin(); it != OUT.end(); it++) {
        cout << *it << endl;
    }
}