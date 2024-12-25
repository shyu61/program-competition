#include <bits/stdc++.h>
using namespace std;

int main() {
    int N; cin >> N;
    vector<vector<int>> G(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    int ans = N;
    for (int c = 0; c < N - 1; c++) {
        int m = G[c].size();
        vector<int> xs(m);
        for (int i = 0; i < m; i++) {
            int ch = G[c][i];
            xs[i] = G[ch].size();
        }
        sort(xs.rbegin(), xs.rend());

        for (int i = 0; i < m; i++) {
            int x = i + 1;
            int y = xs[i] - 1;
            ans = min(ans, N - (x + x * y + 1));;
        }
    }
    cout << ans << endl;
}
