#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 想定解
// 動くものが2つあるので一方は全探索, もう一方をO(logn)以下で処理できる方法を見つけること
// dpという発想と差分の高速評価にlazysegを使えるか

// 障壁
// dpを使うという発想が出てくるかどうか。差分構造は、注意深く観察すれば同じ数字のnext位置が関与するのは分かるので、
// そこから区間更新を思いつくのは難しくない。dpという発想を出せるかどうか。O(logn)に囚われすぎるとdpが出てこない。
// 前から逐次的に見ていくことになるので、逐次問題に適用できるアプローチを思い浮かべられたかどうか。

// ポイント
// uniqueは同じ数のnext位置配列が重要
// 意外と逐次操作を考えていることは多い。貪欲という選択肢が出てくる時点で逐次操作系なので、dpなども同時に検討する

// 区間min/max x RAQ
template<typename T, auto op, T iv>
struct LazySegtree {
private:
    int n = 1;
    vector<T> dat, lazy;

public:
    LazySegtree() {}
    LazySegtree(const vector<int>& a) {
        int sz = a.size();
        while (n < sz) n *= 2;
        dat = vector<T>(n * 2 - 1, iv);
        lazy = vector<T>(n * 2 - 1);

        for (int i = 0; i < sz; i++) dat[i + n - 1] = a[i];
        for (int i = n - 2; i >= 0; i--) {
            dat[i] = op(dat[i * 2 + 1], dat[i * 2 + 2]);
        }
    }

    // [l,r)に対して遅延していた評価を実行
    void eval(int id, int l, int r) {
        if (lazy[id] != 0) {
            dat[id] += lazy[id];
            if (r - l > 1) {
                lazy[id * 2 + 1] += lazy[id];
                lazy[id * 2 + 2] += lazy[id];
            }
            lazy[id] = 0;
        }
    }

    // [a,b)の値を全てxに変更
    void add(int a, int b, int x, int id = 0, int l = 0, int r = -1) {
        if (r < 0) r = n;
        eval(id, l, r);
        if (b <= l || r <= a) return;
        if (a <= l && r <= b) {
            lazy[id] = x;
            eval(id, l, r);
        } else {
            add(a, b, x, id * 2 + 1, l, (l + r) / 2);
            add(a, b, x, id * 2 + 2, (l + r) / 2, r);
            dat[id] = op(dat[id * 2 + 1], dat[id * 2 + 2]);
        }
    }

    T query(int a, int b, int id = 0, int l = 0, int r = -1) {
        if (r < 0) r = n;
        eval(id, l, r);
        if (b <= l || r <= a) return iv;
        if (a <= l && r <= b) return dat[id];
        T vl = query(a, b, id * 2 + 1, l, (l + r) / 2);
        T vr = query(a, b, id * 2 + 2, (l + r) / 2, r);
        return op(vl, vr);
    }
};

int op(int a, int b) { return max(a, b); }

int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i], a[i]--;

    // 右側のbarは全探索
    vector<int> nuniq1(n), nuniq2(n);
    {
        int num1 = 0, num2 = 0;
        vector<int> cnt1(n), cnt2(n);
        rep(i, n) {
            cnt1[a[i]]++;
            if (cnt1[a[i]] == 1) num1++;
            nuniq1[i] = num1;
        }
        for (int i = n - 1; i >= 0; i--) {
            cnt2[a[i]]++;
            if (cnt2[a[i]] == 1) num2++;
            nuniq2[i] = num2;
        }
    }

    // 左側のbarはdpで求める
    vector<int> pre(n);
    {
        vector<int> pos(n + 1, -1);
        rep(i, n) {
            pre[i] = pos[a[i]];
            pos[a[i]] = i;
        }
    }

    // dp[i][j]:=i番目まで見た時、barがjにある時の2区間のnuniqの和
    // dp[i]=max(dp[i][j]|0<j<i)
    vector<int> ini(n), dp(n);
    LazySegtree<int, op, 0> seg(ini);
    rep(i, n) {
        seg.add(max(pre[i], 0), i, 1);
        dp[i] = seg.query(0, i);
        seg.add(i, i + 1, nuniq1[i]);
    }

    int ans = 0;
    for (int i = 1; i < n - 1; i++) {
        ans = max(ans, dp[i] + nuniq2[i + 1]);
    }
    cout << ans << endl;
}
