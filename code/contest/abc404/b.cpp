#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;
const int INF = 1001001001;

// 🔷初見でどうやったら解けるか
// 🔷抑えるべき抽象論は？
// 操作順や配列順を変更することの影響をまず最初に考察する
// - 操作順によらないなら考えやすい操作を先にするなど
// - 配列順によらないならsortしておくなど
// 回転操作は覚えておく
// - 90度: s[i][j] -> s[j][w-1-i]
// - 任意の角度: 回転行列
//   - (x,y) -> (xcos-ysin,xsin+ycos)
// - 回転+平行移動: アフィン変換

// 🔷類問を考える

int main() {
    int n; cin >> n;
    vector<string> s(n), t(n);
    rep(i, n) cin >> s[i];
    rep(i, n) cin >> t[i];

    auto rotate90 = [&](vector<string> ns) -> vector<string> {
        vector<string> res = ns;
        rep(i, n) rep(j, n) res[j][n - 1 - i] = ns[i][j];
        return res;
    };

    int ans = INF;
    rep(r, 4) {
        int res = r;
        if (r > 0) s = rotate90(s);
        rep(i, n) rep(j, n) {
            if (s[i][j] != t[i][j]) res++;
        }
        ans = min(ans, res);
    }
    cout << ans << endl;
}
