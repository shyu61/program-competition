#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;
using mint = atcoder::modint998244353;

// 期待値問題で、影響が累積的なので期待値dpを考える
// 期待値の基本戦略は、ある状態iに遷移する全パスについて 確率*値 を計算すること
// 確率は区間長で一様なのでO(1), 値は区間和, 更新は区間更新なので、lazysegでいける

// 区間和 x RUQ
template<typename T>
struct LazySegtree {
private:
    int n = 1;
    vector<T> dat, lazy;
    vector<bool> flag;

public:
    LazySegtree() {}
    LazySegtree(const vector<int>& a) {
        int sz = a.size();
        while (n < sz) n *= 2;
        dat = lazy = vector<T>(n * 2 - 1);
        flag = vector<bool>(n * 2 - 1);

        for (int i = 0; i < sz; i++) dat[i + n - 1] = a[i];
        for (int i = n - 2; i >= 0; i--) {
            dat[i] = dat[i * 2 + 1] + dat[i * 2 + 2];
        }
    }

    // [l,r)に対して遅延していた評価を実行
    void eval(int id, int l, int r) {
        if (flag[id]) {
            dat[id] = lazy[id];
            if (r - l > 1) {
                lazy[id * 2 + 1] = lazy[id * 2 + 2] = lazy[id] / 2;
                flag[id * 2 + 1] = flag[id * 2 + 2] = true;
            }
            flag[id] = false;
        }
    }

    // [a,b)の値を全てxに変更
    void update(int a, int b, mint x, int id = 0, int l = 0, int r = -1) {
        if (r < 0) r = n;
        eval(id, l, r);
        if (b <= l || r <= a) return;
        if (a <= l && r <= b) {
            lazy[id] = (r - l) * x;
            flag[id] = true;
            dat[id] = lazy[id];
        } else {
            update(a, b, x, id * 2 + 1, l, (l + r) / 2);
            update(a, b, x, id * 2 + 2, (l + r) / 2, r);
            dat[id] = dat[id * 2 + 1] + dat[id * 2 + 2];
        }
    }

    T query(int a, int b, int id = 0, int l = 0, int r = -1) {
        if (r < 0) r = n;
        eval(id, l, r);
        if (b <= l || r <= a) return 0;
        if (a <= l && r <= b) return dat[id];
        T vl = query(a, b, id * 2 + 1, l, (l + r) / 2);
        T vr = query(a, b, id * 2 + 2, (l + r) / 2, r);
        return vl + vr;
    }
};

int main() {
    int n, m; cin >> n >> m;
    vector<int> a(n), L(m), R(m);
    rep(i, n) cin >> a[i];
    rep(i, m) {
        cin >> L[i] >> R[i];
        L[i]--, R[i]--;
    }

    // E = 1/p * 1 + (p-1)/p * (1+E)
    // E = 1/p + (p-1)/p * (1+E)
    // E = 1/p + (p-1)/p * E + (p-1)/p
    // 1/p * E = 1
    // E = p;

    // 各皿が選ばれる確率 1/(R[i]-L[i]+1)
    // 皿に置かれる個数 Σ{k=L[i]_to_R[i]}(a[i])
    // 皿に置かれる個数の期待値 上記の掛け算
    // これをdpで累積的に評価していく => 区間和を高速に計算し、区間更新を高速に処理したい => lazyseg

    LazySegtree<mint> seg(a);
    rep(i, m) {
        mint p = mint(1) / (R[i] - L[i] + 1);
        mint v = seg.query(L[i], R[i] + 1);
        seg.update(L[i], R[i] + 1, p * v);
    }

    rep(i, n) cout << seg.query(i, i + 1).val() << " ";
    cout << endl;
}
