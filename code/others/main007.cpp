// Range Sum Query: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B&lang=jp
#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct BIT {
    vector<T> bit;
    const T n;
    BIT(T n_) : bit(n_ + 1, 0), n(n_) {};

    T sum(int i) {
        T s = 0;
        while (i > 0) {
            s += bit[i];
            i -= i & -i;
        }
        return s;
    };

    void add(int i, T x) {
        while (i <= n) {
            bit[i] += x;
            i += i & -i;
        }
    };
};

int main() {
    int n, q; cin >> n >> q;
    BIT<int> bit(n);
    for (int i = 0; i < q; i++) {
        int c, x, y; cin >> c >> x >> y;
        if (c == 0) bit.add(x, y);
        else {
            int s = bit.sum(y) - bit.sum(x - 1);
            cout << s << endl;
        }
    }
}
