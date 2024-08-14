// トポロジカルソート: DFS with recursive
#include <iostream>
#include <list>
#include <vector>
using namespace std;

const int MAX_NODE = 10000;

vector<vector<int> > G;
list<int> OUT;
vector<bool> Used;

void tsort(int node_id) {
    if (Used[node_id]) return;

    // dfs
    for (int adj : G[node_id]) {
        tsort(adj);
    }
    OUT.push_front(node_id);
    Used[node_id] = true;
}

int main() {
    int n_node, n_edge; cin >> n_node >> n_edge;
    G = vector<vector<int> >(n_node);
    Used = vector<bool>(n_node, false);

    for (int i = 0; i < n_edge; i++) {
        int in, out; cin >> in >> out;
        G[in].push_back(out);
    }

    for (int i = 0; i < n_node; i++) {
        tsort(i);
    }

    for (list<int>::iterator it = OUT.begin(); it != OUT.end(); it++) {
        cout << *it << endl;
    }
}
