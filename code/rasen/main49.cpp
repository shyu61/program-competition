#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

const int MAX_N = 10000;
const int INF = numeric_limits<int>::max();

int n, d[MAX_N];
vector<vector<pair<int, int> > > A(MAX_N);

void solve(int ini) {
    int in_sst[n];
    fill(in_sst, in_sst + n, 0);

    // initialize
    int u = 0; d[u] = 0;
    for (int sst_size = 0; sst_size < n; sst_size++) {
        in_sst[u] = 1;
        // 距離更新ロジック
        for (int i = 0; i < A[u].size(); i++) {
            int id = A[u][i].first;
            int w = A[u][i].second;
            if (w + d[u] < d[id]) {
                d[id] = w + d[u];
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