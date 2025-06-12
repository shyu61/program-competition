#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 🔷初見でどうやったら解けるか
// 制約条件から全探索あるいは半分全列挙を疑えるかが全て。
// また、総和のmodは必ずといって良いほど各項ごとにmodをとって考える

// 🔷抑えるべき抽象論は？
// modも単調性を利用すれば二分探索/尺取りできる
// - a+b<modとmod<=a+b<2*modで場合分けすれば良い
// 多少定数倍を払っても、処理しやすい形を作っておくことは重要

int main() {
    int n, m; cin >> n >> m;
    vector<vector<int>> mas(n, vector<int>(n));
    rep(i, n) rep(j, n) {
        cin >> mas[i][j];
        ll ten = 1;
        rep(k, n * 2 - (i + j) - 2) ten = ten * 10 % m;
        mas[i][j] = mas[i][j] * ten % m;
    }

    if (n == 1) {
        cout << mas[0][0] << endl;
        return 0;
    }

    auto f = [&](bool is_rev) {
        vector<vector<ll>> cand(n);
        auto dfs = [&](auto dfs, int i, int j, ll now) {
            now = (now + mas[i][j]) % m;
            if (i + j == n - 1) {
                cand[i].push_back(now);
                return;
            }
            dfs(dfs, is_rev ? i - 1 : i + 1, j, now);
            dfs(dfs, i, is_rev ? j - 1 : j + 1, now);
        };
        if (is_rev) dfs(dfs, n - 1, n - 1, 0);
        else dfs(dfs, 0, 0, 0);
        return cand;
    };
    auto a = f(false);
    auto b = f(true);

    ll ans = 0;
    rep(i, n) {
        sort(a[i].begin(), a[i].end());
        rep(j, b[i].size()) {
            b[i][j] = (b[i][j] - mas[i][n - i - 1] + m) % m;
        }
        sort(b[i].begin(), b[i].end());

        ans = max(ans, (a[i].back() + b[i].back()) % m);

        int pos = b[i].size() - 1;
        for (auto ai : a[i]) {
            while (pos >= 0 && ai + b[i][pos] >= m) pos--;
            if (pos < 0) break;
            ans = max(ans, (ai + b[i][pos]) % m);
        }
    }

    cout << ans << endl;
}
