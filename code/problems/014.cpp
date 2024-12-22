// E - Reachability in Functional Graph
// https://atcoder.jp/contests/abc357/tasks/abc357_e
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n; cin >> n;
    vector<int> G(n);
    for (int i = 0; i < n; i++) {
        int u; cin >> u; u--;
        G[i] = u;
    }

    // サイクル検出
    vector<bool> seen(n);
    vector<int> ans(n), order, idx(n, -1);
    for (int i = 0; i < n; i++) {
        if (seen[i]) continue;
        // 閉路を検出するまで掘り続ける
        vector<int> vo;
        int v = i, cnt = 0;
        while (1) {
            if (seen[v]) break;
            // 閉路検知
            if (idx[v] != -1) {
                vector<int> cyc(vo.begin() + idx[v], vo.end());
                for (int u : cyc) ans[u] = cyc.size();
                break;
            }

            idx[v] = cnt++;
            vo.push_back(v);
            v = G[v];
        }
        for (int v : vo) seen[v] = true;
        // 辿ってきた頂点を逆順に保存
        order.insert(order.end(), vo.rbegin(), vo.rend());
    }

    for (int v : order) {
        if (ans[v] != 0) continue;
        ans[v] = ans[G[v]] + 1;
    }

    ll total = 0;
    for (int i = 0; i < n; i++) total += ans[i];
    cout << total << endl;
}
