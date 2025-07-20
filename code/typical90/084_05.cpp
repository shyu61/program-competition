#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// https://atcoder.jp/contests/abc125/tasks/abc125_c

// 🔷初見でどうやったら解けるか
// 組合せ最適化問題だが、どの値に変えるのかは無数に選択肢があるので、最適な変更値を考えるところから始める。
// すると、削除する、あるいは他の任意の値に書き換えることが常に最適になることがわかる。
// 変更する値のスキャンはO(n)なので、残りn-1個のgcdをO(logn)以下で求められれば良い
// gcdは値のキャンセルが高速にできないので尺取り的にやるのは無理だが、こういった数字の場合は、両側累積和が有効
// もしくは区間同士の和と捉えて区間アルゴリズムを使っても良い。再帰的なき構造を考えてメモ化しても良い。
// メモ化再帰は繰り返し二乗法と近い考え方で汎用性が高い。結合則が成立する集約値において有効

// 🔷抑えるべき抽象論は？
// 配列内の特定の要素を除いた集計値の求め方
// - 尺取り法
// - 両側累積和
// - セグ木
// - メモ化再帰
//   - 繰り返し二乗法的考え方
//   - 結合則が成立する集約値において有効

// メモ化再帰による解法
int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    // メモ化再帰
    vector<int> memo(n * 2 - 1, -1);
    auto rec = [&](auto rec, int id) {
        if (memo[id] != -1) return memo[id];
        if (id >= n - 1) return memo[id] = a[id - n + 1];
        return memo[id] = gcd(rec(rec, id * 2 + 1), rec(rec, id * 2 + 2));
    };

    int ans = rec(rec, 0);
    rep(i, n) {
        auto reset = [&]() {
            memo[0] = -1;
            int ix = i + n - 1;
            while (ix > 0) {
                memo[ix] = -1;
                ix = (ix - 1) / 2;
            }
        };

        int tmp = a[i];
        a[i] = a[(i + 1) % n];
        reset();
        ans = max(ans, rec(rec, 0));

        a[i] = tmp;
        reset();
        rec(rec, 0);
    }
    cout << ans << endl;
}

// 累積和による解法
int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    vector<int> sl(n + 1), sr(n + 1);
    rep(i, n) sl[i + 1] = gcd(sl[i], a[i]);
    for (int i = n; i > 0; i--) sr[i - 1] = gcd(sr[i], a[i - 1]);

    int ans = 0;
    rep(i, n) {
        ans = max(ans, gcd(sl[i], sr[i + 1]));
    }
    cout << ans << endl;
}

// セグ木による解法
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

int op(int a, int b) { return gcd(a, b); }

int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    Segtree<op, 0> seg(a);

    int ans = 0;
    rep(i, n) {
        int res = gcd(seg.query(0, i), seg.query(i + 1, n));
        ans = max(ans, res);
    }
    cout << ans << endl;
}
