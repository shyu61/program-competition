#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<ll, int>;

// 🔷初見でどうやったら解けるか
// 組合せ最適化で、過去に選んだものに依存して次の選択肢が決定される形状なのでdpを基本路線とする
// 通常の01ナップサックdpとの違いは、選べる重さに幅があること。つまりmaxをri-li通りに対して取る必要がある点。
// これさえ高速に求まれば01ナップサックに帰着できる。区間maxなのでsegtreeをすれば良い

// 🔷抑えるべき抽象論は？
// 区間のmin/maxはsegtreeがセオリーだが、区間幅が固定ならスライドmin/maxが最速
// 区間ではなく動的配列のmin/maxはset/multiset

template<auto op, ll iv>
struct Segtree {
private:
    int n = 1;
    vector<ll> dat;

public:
    Segtree() {}
    Segtree(const vector<int>& a) {
        int sz = a.size();
        while (n < sz) n *= 2;
        dat = vector<ll>(n * 2 - 1, iv);

        for (int i = 0; i < sz; i++) dat[i + n - 1] = a[i];
        for (int i = n - 2; i >= 0; i--) {
            dat[i] = op(dat[i * 2 + 1], dat[i * 2 + 2]);
        }
    }

    ll query(int a, int b, int id = 0, int l = 0, int r = -1) {
        if (r < 0) r = n;
        if (b <= l || r <= a) return iv;
        if (a <= l && r <= b) return dat[id];
        else {
            ll vl = query(a, b, id * 2 + 1, l, (l + r) / 2);
            ll vr = query(a, b, id * 2 + 2, (l + r) / 2, r);
            return op(vl, vr);
        }
    }

    // 元の配列でindex=kの要素をxに更新
    void update(int k, ll x) {
        int id = k + n - 1;  // ノード番号に変換
        dat[id] = x;
        while (id > 0) {
            id = (id - 1) / 2;
            dat[id] = op(dat[id * 2 + 1], dat[id * 2 + 2]);
        }
    }
};

ll op(ll a, ll b) { return max(a, b); }

// segtreeによる解法
int main() {
    int w, n; cin >> w >> n;
    vector<int> l(n), r(n), v(n);
    rep(i, n) cin >> l[i] >> r[i] >> v[i];

    vector<vector<ll>> dp(n + 1, vector<ll>(w + 1));
    vector<int> ini(w + 1);
    vector<Segtree<op, 0>> seg(n + 1, Segtree<op, 0>(ini));

    rep(i, n) {
        rep(j, w + 1) {
            ll res = dp[i][j];
            if (j - l[i] >= 0) {
                ll mx = seg[i].query(max(j - r[i], 0), j - l[i] + 1);
                if (mx != 0 || j - r[i] <= 0) {
                    res = max(res, mx + v[i]);
                }
            }
            dp[i + 1][j] = res;
            seg[i + 1].update(j, res);
        }
    }

    if (dp[n][w] == 0) cout << -1 << endl;
    else cout << dp[n][w] << endl;
}

// スライド最大化による解法
int main() {
    int w, n; cin >> w >> n;
    vector<int> l(n), r(n), v(n);
    rep(i, n) cin >> l[i] >> r[i] >> v[i];

    vector<vector<ll>> dp(n + 1, vector<ll>(w + 1));

    rep(i, n) {
        deque<P> deq;
        rep(j, w + 1) {
            if (j - l[i] >= 0) {
                int ub = j - l[i];
                while (deq.size() && deq.back().first <= dp[i][ub]) deq.pop_back();
                deq.emplace_back(dp[i][ub], ub);
            }

            ll res = dp[i][j];
            if (deq.size()) {
                auto [mx, ix] = deq.front();
                if (mx != 0 || j - r[i] <= 0) {
                    res = max(res, mx + v[i]);
                }
                if (ix <= j - r[i]) deq.pop_front();
            }
            dp[i + 1][j] = res;
        }
    }

    if (dp[n][w] == 0) cout << -1 << endl;
    else cout << dp[n][w] << endl;
}
