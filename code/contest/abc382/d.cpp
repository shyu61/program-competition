#include <bits/stdc++.h>
using namespace std;

// ジャンル
// 数列, 数え上げ, 全列挙

// 方針
// 全列挙問題なので全探索をする。依存関係がある全探索なので、再帰を書く

int main() {
    int N, M; cin >> N >> M;

    vector<vector<int>> ans;
    auto dfs = [&](auto dfs, int lb, vector<int> a) {
        int pos = a.size();
        if (pos == N) {
            ans.push_back(a);
            return;
        }
        for (int i = lb; i + 10 * (N - pos - 1) <= M; i++) {
            a.push_back(i);
            dfs(dfs, i + 10, a);
            a.pop_back();
        }
    };
    dfs(dfs, 1, vector<int>());

    cout << ans.size() << endl;
    for (auto a : ans) {
        for (auto v : a) cout << v << ' ';
        cout << '\n';
    }
}
