// ダイクストラ法
#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
#include <queue>
using namespace std;

using Edge = pair<int, int>;

const int MAX_N = 10000;
const int INF = numeric_limits<int>::max();

int n, d[MAX_N];
vector<vector<Edge> > A(MAX_N);

void solve(int ini) {
    priority_queue<Edge, vector<Edge>, greater<Edge> > PQ;

    // initialize
    d[ini] = 0;
    PQ.push({0, ini});
    while (!PQ.empty()) {
        int w = PQ.top().first;
        int u = PQ.top().second;
        PQ.pop();

        // PQ内には更新前の古いqueueも含まれる
        if (w > d[u]) continue;

        // 距離更新ロジック
        for (const auto &pair : A[u]) {
            int adj_v = pair.first;
            int adj_w = pair.second;
            // すでにsstに含まれるadj_vは、すでに最小値を取っているので更新されることはない
            // 故に!in_sst[adj_v]のチェックは不要
            if (adj_w + w < d[adj_v]) {
                d[adj_v] = adj_w + w;
                PQ.push(make_pair(d[adj_v], adj_v));
            }
        }
    }
}

int main() {
    cin >> n;
    fill(d, d + n, INF);

    for (int i = 0; i < n; i++) {
        int id, k; cin >> id >> k;
        for (int j = 0; j < k; j++) {
            int v, w; cin >> v >> w;
            A[id].push_back(make_pair(v, w));
        }
    }
    solve(0);
    for (int i = 0; i < n; i++) {
        cout << i << " " << d[i] << endl;
    }
}