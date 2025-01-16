#include <bits/stdc++.h>
using namespace std;

// ジャンル
// 逐次問題, グリッド問題

// 方針
// 逐次問題と見せかけてt=10^100なので、常に最終状態を出力すれば良い
// 自身の領域とかぶり、自身より下にある棒の本数をNから引けば答え
// 各行ごとに積み上がる棒の本数をカウントして、自身の領域内でのmaxを取れば良い
// 区間maxかつ、区間の一括更新なので遅延セグ木で実装する

template<typename T, auto op, T iv>
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
        dat = vector<T>(n * 2 - 1, iv);
        lazy = vector<T>(n * 2 - 1);
        flag = vector<bool>(n * 2 - 1);

        for (int i = 0; i < sz; i++) dat[i + n - 1] = a[i];
        for (int i = n - 2; i >= 0; i--) {
            dat[i] = op(dat[i * 2 + 1], dat[i * 2 + 2]);
        }
    }

    // [l,r)に対して遅延していた評価を実行
    void eval(int id, int l, int r) {
        if (flag[id]) {
            dat[id] = lazy[id];
            if (r - l > 1) {
                lazy[id * 2 + 1] = lazy[id * 2 + 2] = lazy[id];
                flag[id * 2 + 1] = flag[id * 2 + 2] = true;
            }
            flag[id] = false;
        }
    }

    // [a,b)の値を全てxに変更
    void update(int a, int b, int x, int id = 0, int l = 0, int r = -1) {
        if (r < 0) r = n;
        eval(id, l, r);
        if (b <= l || r <= a) return;
        if (a <= l && r <= b) {
            lazy[id] = x;
            flag[id] = true;
            eval(id, l, r);
        } else {
            update(a, b, x, id * 2 + 1, l, (l + r) / 2);
            update(a, b, x, id * 2 + 2, (l + r) / 2, r);
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
    int H, W, N; cin >> H >> W >> N;
    vector<tuple<int, int, int, int>> h(N);
    for (int i = 0; i < N; i++) {
        int r, c, l; cin >> r >> c >> l;
        h[i] = {--r, --c, l, i};
    }
    sort(h.begin(), h.end(), greater<>());

    vector<int> ans(N);
    LazySegtree<int, op, 0> rmq(vector<int>(W, 0));
    for (auto [r, c, l, i] : h) {
        ans[i] = rmq.query(c, c + l);
        rmq.update(c, c + l, ans[i] + 1);
    }

    for (auto v : ans) cout << H - v << '\n';
}
