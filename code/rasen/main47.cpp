#include <iostream>
#include <vector>
using namespace std;
const int INF = 100 * 2000 + 1;

int n;
vector<vector<int> > A;

int prim(int ini) {
    int total = 0;
    vector<int> in_mst(n, 0);
    vector<int> min_w(n, INF); min_w[ini] = 0;

    while (true) {
        int most_min = INF;
        int u = -1;

        for (int i = 0; i < n; i++) {
            if (!in_mst[i] && min_w[i] < most_min) {
                most_min = min_w[i];
                u = i;
            }
        }

        if (u == -1) break;

        in_mst[u] = 1;
        for (int i = 0; i < n; i++) {
            // uに接続していないノードiはA[u][i] == INFとなるため更新されない
            if (!in_mst[i] && A[u][i] < min_w[i]) {
                min_w[i] = A[u][i];
            }
        }

        total += min_w[u];
    }
    return total;
}

int main() {
    cin >> n;
    vector<int> vec(n);
    A = vector<vector<int> >(n, vector<int>(n, INF));
    for (int i = 0; i < n; i++) {
        vec[i] = i;
        for (int j = 0; j < n; j++) {
            int a; cin >> a;
            if (a != -1) A[i][j] = a;
        }
    }

    int ans = prim(0);
    cout << ans << endl;
}