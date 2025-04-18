#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct Segtree {
private:
    int n = 1;
    vector<int> dat;

public:
    Segtree() {}
    Segtree(const vector<int>& a) {
        int sz = a.size();
        while (n < sz) n *= 2;
        dat = vector<int>(n * 2 - 1, 0);

        for (int i = 0; i < sz; i++) dat[i + n - 1] = a[i];
        for (int i = n - 2; i >= 0; i--) {
            dat[i] = dat[i * 2 + 1] + dat[i * 2 + 2];
        }
    }

    int query(int a, int b, int id = 0, int l = 0, int r = -1) {
        if (r < 0) r = n;
        if (b <= l || r <= a) return 0;
        if (a <= l && r <= b) return dat[id];
        else {
            int vl = query(a, b, id * 2 + 1, l, (l + r) / 2);
            int vr = query(a, b, id * 2 + 2, (l + r) / 2, r);
            return vl + vr;
        }
    }

    // 元の配列でindex=kの要素をxに更新
    void update(int k, int x) {
        int id = k + n - 1;  // ノード番号に変換
        dat[id] = x;
        while (id > 0) {
            id = (id - 1) / 2;
            dat[id] = dat[id * 2 + 1] + dat[id * 2 + 2];
        }
    }

    // x以上となる最初の点
    int lower_bound(T x, T sum = 0, int id = 0, int l = 0, int r = -1) {
        if (l == r) return l;
        if (r < 0) r = n;
        if (dat[id] + sum < x) return n;
        T vl = lower_bound(x, sum, id * 2 + 1, l, (l + r) / 2);
        if (vl != n) return vl;
        return lower_bound(x, sum + dat[id * 2 + 1], id * 2 + 2, (l + r) / 2, r);
    }

    // xより大きくなる最初の点
    int upper_bound(T x, T sum = 0, int id = 0, int l = 0, int r = -1) {
        if (l == r) return l;
        if (r < 0) r = n;
        if (dat[id] + sum <= x) return n;
        T vr = upper_bound(x, sum + dat[id * 2 + 1], id * 2 + 2, (l + r) / 2, r);
        if (vr != n) return vr;
        return upper_bound(x, sum, id * 2 + 1, l, (l + r) / 2);
    }
};
