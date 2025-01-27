#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // nCk
    {
        vector<int> xs;
        auto comb = [&](auto comb, int k, int s) -> void {
            if (xs.size() == k) {
                for (auto v : xs) cout << v << ' ';
                cout << '\n';
                return;
            }
            for (int i = s; i < n; i++) {
                xs.push_back(a[i]);
                comb(comb, k, i + 1);
                xs.pop_back();
            }
        };
    }

    // nPk
    {
        vector<int> xs;
        vector<bool> used(n);
        auto perm = [&](auto perm, int k) -> void {
            if (xs.size() == k) {
                for (auto v : xs) cout << v << ' ';
                cout << '\n';
                return;
            }
            for (int i = 0; i < n; i++) {
                if (used[i]) continue;
                used[i] = true;
                xs.push_back(a[i]);
                perm(perm, k);
                xs.pop_back();
                used[i] = false;
            }
        };
    }

    // nPn
    {
        auto perm2 = [&]() -> void {
            do {
                for (auto ai : a) cout << ai << ' ';
                cout << '\n';
            } while (next_permutation(a.begin(), a.end()));
        };
    }

    // pertition(bell)
    // ベル数: n個以下の非空集合に分割する。n個全てを選び切るまでcombを繰り返し実行する行為と同じで、combの拡張とみなせる
    // 集合全体をグループ分けしたい場合に有用
    {
        auto print = [&](const vector<vector<int>>& vs) -> void {
            for (auto sub : vs) {
                int m = sub.size();
                cout << '{';
                for (int i = 0; i < m; i++) {
                    cout << sub[i] << (i == m - 1 ? '}' : ',');
                }
            }
            cout << '\n';
        };

        vector<vector<int>> xs;
        auto dfs = [&](auto dfs, int s) -> void {
            if (s == n) {
                print(xs);
                return;
            }
            for (int i = 0; i < xs.size(); i++) {
                xs[i].push_back(a[s]);
                dfs(dfs, s + 1);
                xs[i].pop_back();
            }
            xs.push_back(vector<int>{a[s]});
            dfs(dfs, s + 1);
            xs.pop_back();
        };
    }

    // pertition(starling)
    // スターリング数: 丁度k個の非空集合に分割する
    // 包除原理を使って証明ができる
    // - 空集合を許容する場合、丁度k個に分割するパターンはk^n
    // - この内、少なくとも1つは空集合であるものを引けばよく、包除原理を使うと丁度1つが空集合, 丁度2つが空集合...となる。
    // - 丁度i個が非空集合とすると、i個のいずれかに割り当てれば良いので、kCi * i^n
    // -> https://manabitimes.jp/math/892
    {
        auto print = [&](const vector<vector<int>>& vs) -> void {
            for (auto sub : vs) {
                int m = sub.size();
                cout << '{';
                for (int i = 0; i < m; i++) {
                    cout << sub[i] << (i == m - 1 ? '}' : ',');
                }
            }
            cout << '\n';
        };

        vector<vector<int>> xs;
        auto dfs = [&](auto dfs, int k, int s) -> void {
            if (xs.size() > k) return;
            if (s == n) {
                if (xs.size() == k) print(xs);
                return;
            }
            for (int i = 0; i < xs.size(); i++) {
                xs[i].push_back(a[s]);
                dfs(dfs, k, s + 1);
                xs[i].pop_back();
            }
            xs.push_back(vector<int>{a[s]});
            dfs(dfs, k, s + 1);
            xs.pop_back();
        };
    }
}
