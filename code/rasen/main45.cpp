#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int NIL = -1;

vector<vector<int> > A;
vector<int> visited;
int n;

int next(int v) {
    for (int k = 0; k < A[v].size(); k++) {
        int id = A[v][k];
        if (visited[id] == 0) return id;
    }
    return NIL;
}

void bfs(int v, int group_num) {
    queue<int> Q;
    Q.push(v); visited[v] = group_num;

    while (!Q.empty()) {
        int prev = Q.front();
        v = next(prev);
        if (v != NIL) {
            Q.push(v);
            visited[v] = group_num;
        } else {
            Q.pop();
        }
    }
}


int main() {
    int m; cin >> n >> m;
    A = vector<vector<int> >(n);
    visited = vector<int>(n);
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        A[a].push_back(b);
        A[b].push_back(a);
    }

    int graph_number = 1;
    for (int i = 0; i < n; i++) {
        if (visited[i] == 0) bfs(i, graph_number++);
    }

    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        if (visited[a] == visited[b]) cout << "yes" << endl;
        else cout << "no" << endl;
    }
}