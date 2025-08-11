#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;

// https://atcoder.jp/contests/abc038/tasks/abc038_d

// 🔷抑えるべき抽象論は？
// 2つを同時に最適化したい場合
// - Aでsortして順に見ていきつつ、Bをデータ構造に入れて処理する。つまりデータ構造を検索するとき、条件Aを満たしたBしか入ってない状態を作る。
// - 判定問題で解く

template<auto op, int iv>
struct Segtree {
private:
    int n = 1;
    vector<int> dat;

public:
    Segtree() {}
    Segtree(const vector<int>& a) {
        int sz = a.size();
        while (n < sz) n *= 2;
        dat = vector<int>(n * 2 - 1, iv);

        for (int i = 0; i < sz; i++) dat[i + n - 1] = a[i];
        for (int i = n - 2; i >= 0; i--) {
            dat[i] = op(dat[i * 2 + 1], dat[i * 2 + 2]);
        }
    }

    int query(int a, int b, int id = 0, int l = 0, int r = -1) {
        if (r < 0) r = n;
        if (b <= l || r <= a) return iv;
        if (a <= l && r <= b) return dat[id];
        else {
            int vl = query(a, b, id * 2 + 1, l, (l + r) / 2);
            int vr = query(a, b, id * 2 + 2, (l + r) / 2, r);
            return op(vl, vr);
        }
    }

    // 元の配列でindex=kの要素をxに更新
    void update(int k, int x) {
        int id = k + n - 1;  // ノード番号に変換
        dat[id] = x;
        while (id > 0) {
            id = (id - 1) / 2;
            dat[id] = op(dat[id * 2 + 1], dat[id * 2 + 2]);
        }
    }
};

int op(int a, int b) { return max(a, b); }

int main() {
    int n; cin >> n;
    vector<P> a(n);
    int maxh = 0;
    rep(i, n) {
        cin >> a[i].first >> a[i].second;
        maxh = max(maxh, a[i].second);
    }
    sort(a.begin(), a.end());

    vector<int> ini(maxh + 1, -1);
    Segtree<op, -1> seg(ini);

    // dp[i]:=i番目の箱を最も外側にしたときの個数
    vector<int> dp(n);
    int pre = 0, ans = 0;
    rep(i, n) {
        if (i > 0) dp[i] = seg.query(0, a[i].second) + 1;
        if (i < n - 1 && a[i].first < a[i + 1].first) {
            for (int j = pre; j <= i; j++) seg.update(a[j].second, dp[j]);
            pre = i + 1;
        }
        ans = max(ans, dp[i]);
    }
    cout << ans + 1 << endl;
}
