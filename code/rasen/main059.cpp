// トポロジカルソート: DFS with stack
#include <iostream>
#include <stack>
#include <list>
#include <vector>
using namespace std;

const int NIL = -1;

vector<vector<int> > G;
list<int> OUT;
vector<bool> Used;

int next(int node_id) {
    for (int adj : G[node_id]) {
        if (!Used[adj]) return adj;
    }
    return NIL;
}

void tsort(int node_id) {
    if (Used[node_id]) return;

    // dfs
    stack<int> S;
    S.push(node_id);
    while (!S.empty()) {
        int v = S.top();

        int adj = next(v);
        if (adj != NIL) {
            S.push(adj);
        } else {
            S.pop();
            OUT.push_front(v);
            Used[v] = true;
        }
    }
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
