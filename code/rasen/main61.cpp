// 関節点: low-link
#include <iostream>
#include <vector>
#include <set>
using namespace std;

const int NIL = -1;

vector<vector<int> > G;
vector<bool> visited;
vector<int> parent, prenum, lowest;
int num = 0;

void backedge(int node_id) {
    for (int &adj : G[node_id]) {
        if (adj != parent[node_id]) {
            lowest[node_id] = min(prenum[node_id], prenum[adj]);
        }
    }
}

void dfs(int node_id) {
    // 行きし
    visited[node_id] = true;
    prenum[node_id] = num++;
    lowest[node_id] = prenum[node_id];
    for (int adj : G[node_id]) {
        if (!visited[adj]) {
            parent[adj] = node_id;
            dfs(adj);
            // 枝探索後
            lowest[node_id] = min(lowest[adj], lowest[node_id]);
        } else if (adj != parent[node_id]) {
            // 親以外で訪問ずみノード = backedge
            // 未訪問のノードは必ずprenumが大きくなるのでバイパスにならない
            lowest[node_id] = min(lowest[node_id], prenum[adj]);
        }
    }
    // 全ての枝の訪問を終えての帰りし
}

int main() {
    int n_node, n_edge; cin >> n_node >> n_edge;
    G = vector<vector<int> >(n_node);
    visited = vector<bool>(n_node, false);
    parent = prenum = lowest = vector<int>(n_node);

    for (int i = 0; i < n_edge; i++) {
        int in, out; cin >> in >> out;
        G[in].push_back(out);
        G[out].push_back(in);
    }

    parent[0] = NIL;
    dfs(0);

    set<int> output;
    int root_child_cnt = 0;
    for (int i = 0; i < n_node; i++) {
        if (parent[i] == NIL) continue;
        if (parent[i] == 0) root_child_cnt++;
        else if (prenum[parent[i]] <= lowest[i]) {
            output.insert(parent[i]);
        }
    }
    if (root_child_cnt >= 2) output.insert(0);
    for (set<int>::iterator it = output.begin(); it != output.end(); it++) {
        cout << *it << endl;
    }
}
