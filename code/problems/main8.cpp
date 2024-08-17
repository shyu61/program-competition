// E - Tree and Hamilton Path 2
// https://atcoder.jp/contests/abc361/tasks/abc361_e
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Edge {
    int to, w;
    Edge(int to, int w): to(to), w(w) {}
};

const int NMAX = 2e5;
vector<Edge> A[NMAX + 1];
int n;
ll dist[NMAX + 1];

pair<int, ll> bfs(int id) {
    for (int i = 1; i <= n; i++) dist[i] = -1;

    queue<int> que;
    que.push(id);
    dist[id] = 0;

    ll maxv = 0;
    int farthest = -1;
    while (!que.empty()) {
        int v = que.front(); que.pop();
        for (auto adj : A[v]) {
            if (dist[adj.to] != -1) continue;
            dist[adj.to] = dist[v] + adj.w;

            if (dist[adj.to] > maxv) {
                maxv = dist[adj.to];
                farthest = adj.to;
            }
            que.push(adj.to);
        }
    }

    return make_pair(farthest, maxv);
}

int main() {
    ll csum = 0;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        A[a].emplace_back(b, c);
        A[b].emplace_back(a, c);
        csum += c;
    }

    int farthest = bfs(1).first;
    ll diameter = bfs(farthest).second;
    cout << 2 * csum - diameter << endl;
}
