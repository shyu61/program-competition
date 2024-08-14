#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

const int MAX_N = 100;
const int INF = numeric_limits<int>::max();

int n, A[MAX_N][MAX_N], d[MAX_N];

void solve(int ini) {
    int in_sst[n];
    fill(in_sst, in_sst + n, 0);

    // initialize
    int u = 0; d[u] = 0;
    for (int sst_size = 0; sst_size < n; sst_size++) {
        in_sst[u] = 1;
        // 距離更新ロジック
        for (int i = 0; i < n; i++) {
            int w = A[u][i];
            // uに隣接している && まだsstに含まれていない
            if (w == INF || in_sst[i]) continue;
            if (w + d[u] < d[i]) {
                d[i] = w + d[u];
            }
        }

        // 最小距離のノードをSSTに追加する
        int mind = INF;
        for (int i = 0; i < n; i++) {
            if (!in_sst[i] && (d[i] < mind)) {
                mind = d[i];
                u = i;
            }
        }
    }
}

int main() {
    cin >> n;
    fill(d, d + n, INF);
    for (int i = 0; i < n; i++) fill(A[i], A[i] + n, INF);

    for (int i = 0; i < n; i++) {
        int id, k; cin >> id >> k;
        for (int j = 0; j < k; j++) {
            int v, w; cin >> v >> w;
            A[id][v] = w;
        }
    }
    solve(0);
    for (int i = 0; i < n; i++) {
        cout << i << " " << d[i] << endl;
    }
}