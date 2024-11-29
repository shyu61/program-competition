// Range Minimum Query (RMQ)
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A&lang=ja
#include <bits/stdc++.h>
using namespace std;

struct RMQ {
    vector<int> dat;
    int sz = 1;

    RMQ() {}
    // n: 要素数, a: 初期化時に利用する値
    RMQ(int n, const vector<int>& a) {
        while (sz < n) sz *= 2;
        dat = vector<int>(sz * 2 - 1);

        for (int i = 0; i < n; i++) dat[i + sz - 1] = a[i];
        for (int i = sz - 2; i >= 0; i--) {
            dat[i] = min(dat[i * 2 + 1], dat[i * 2 + 2]);
        }
    }

    // (value,index)
    pair<int, int> query(int a, int b, int k, int l, int r) {
        if (b <= l || r <= a) return make_pair(INF, -1);
        if (a <= l && r <= b) return make_pair(dat[k], k);
        else {
            auto [vl, il] = query(a, b, k * 2 + 1, l, (l + r) / 2);
            auto [vr, ir] = query(a, b, k * 2 + 2, (l + r) / 2, r);
            return vl < vr ? make_pair(vl, il) : make_pair(vr, ir);
        }
    }

    // k: 要素番号, a: 更新値
    void update(int k, int a) {
        k += sz - 1;
        dat[k] = a;
        while (k > 0) {
            k = (k - 1) / 2;
            dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
        }
    }
};

const int INF = numeric_limits<int>::max();

int main() {
    int n, q; cin >> n >> q;
    vector<int> a(n, INF);

    RMQ rmq(n, a);

    while (q--) {
        int c; cin >> c;
        if (c) {
            // find(s,t)
            int s, t; cin >> s >> t;
            cout << rmq.query(s, t + 1, 0, 0, rmq.sz).first << endl;
        } else {
            // update(i,x)
            int i, x; cin >> i >> x;
            rmq.update(i, x);
        }
    }
}
