#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;
using uint = unsigned int;

// https://atcoder.jp/contests/abc018/tasks/abc018_4

// 🔷初見でどうやったら解けるか
// 結論は半分全列挙だが、実際全探索するのは片方のみで、もう一方は貪欲に決められる問題
// 考え方としては、全組み合わせの探索は無理だが制約的に半分は探索できるので半分全列挙で考える。
// しかし男女それぞれの組み合わせ同士を、単調アルゴリズムを使って高速にマッチングするのは無理。
// この時点で典型的な半分全列挙の解法ではなくなったが、片方全探索できるのは大きいので、一方を固定して考える。
// すると貪欲にもう一方を決められることがわかる

// 🔷抑えるべき抽象論は？
// 半分全列挙でも、全探索するのは一方のみというケースもある

int main() {
    int n, m, p, q, r; cin >> n >> m >> p >> q >> r;
    vector<vector<P>> x(n);
    rep(i, r) {
        int xi, yi, zi; cin >> xi >> yi >> zi;
        xi--, yi--;
        x[xi].emplace_back(yi, zi);
    }

    int ans = 0;
    rep(s, 1 << n) {
        if (popcount(uint(s)) != p) continue;
        vector<int> score(m);
        rep(i, n) {
            if (s >> i & 1) {
                for (auto [y, z] : x[i]) score[y] += z;
            }
        }

        sort(score.begin(), score.end(), greater());
        int res = 0;
        rep(i, q) res += score[i];
        ans = max(ans, res);
    }
    cout << ans << endl;
}
