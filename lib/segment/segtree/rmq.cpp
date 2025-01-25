#include <bits/stdc++.h>
using namespace std;

// op: 区間merge関数, iv: 初期値
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

    // x以上(以下)となる最初の点
    int lower_bound(T x, int id = 0, int l = 0, int r = -1) {
        if (l == r) return l;
        if (r < 0) r = n;
        if (dat[id] != x && op(dat[id], x) == x) return n;
        T vl = lower_bound(x, id * 2 + 1, l, (l + r) / 2);
        if (vl != n) return vl;
        return lower_bound(x, id * 2 + 2, (l + r) / 2, r);
    }

    // xより大きく(小さく)なる最初の点
    int upper_bound(T x, int id = 0, int l = 0, int r = -1) {
        if (l == r) return l;
        if (r < 0) r = n;
        if (dat[id] == x || op(dat[id], x) == x) return n;
        T vr = upper_bound(x, id * 2 + 2, (l + r) / 2, r);
        if (vr != n) return vr;
        return upper_bound(x, id * 2 + 1, l, (l + r) / 2);
    }
};
