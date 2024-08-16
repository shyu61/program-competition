// E - Tree and Hamilton Path 2
// https://atcoder.jp/contests/abc361/tasks/abc361_e
#include <bits/stdc++.h>
using namespace std;

const int NMAX = 2e5;
vector<array<int, 2>> A[NMAX + 1];  // {街, 距離}
int n;
long long dist[NMAX + 1];

pair<int, long long> bfs(int id) {
    for (int i = 1; i <= n; i++) dist[i] = -1;

    queue<int> que;
    que.push(id);
    dist[id] = 0;

    long long maxv = 0;
    int farthest = -1;
    while (!que.empty()) {
        int v = que.front(); que.pop();
        for (auto adj : A[v]) {
            if (dist[adj[0]] != -1) continue;
            dist[adj[0]] = dist[v] + adj[1];

            if (dist[adj[0]] > maxv) {
                maxv = dist[adj[0]];
                farthest = adj[0];
            }
            que.push(adj[0]);
        }
    }

    return make_pair(farthest, maxv);
}

int main() {
    long long csum = 0;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        A[a].push_back({b, c});
        A[b].push_back({a, c});
        csum += c;
    }

    int farthest = bfs(1).first;
    long long diameter = bfs(farthest).second;
    cout << 2 * csum - diameter << endl;
}
