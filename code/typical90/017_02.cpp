#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;

template <typename T=int>
struct FenwickTree {
    vector<T> bit;
    const T n;
    FenwickTree(T n_) : bit(n_ + 1, 0), n(n_) {};

    void add(int i, T x) {
        assert(0 <= i && i < n);
        i++;
        while (i <= n) {
            bit[i - 1] += x;
            i += i & -i;
        }
    }

    T sum(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        return sum(r) - sum(l);
    }

    private:
        T sum(int i) {
            T s = 0;
            while (i > 0) {
                s += bit[i - 1];
                i -= i & -i;
            }
            return s;
        }
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<P> s(m);
    rep(i, m) {
        int l, r;
        cin >> l >> r, l--, r--;
        s[i] = {l, r};
    }
    sort(s.begin(), s.end(), [](const P &a, const P &b) {
        return a.first == b.first ? a.second > b.second : a.first < b.first;
    });

    FenwickTree<ll> ft(n), ft2(n);
    rep(i, m) {
        ft.add(s[i].first, 1);
        ft2.add(s[i].second, 1);
    }

    ll ans = 0;
    rep(i, m) {
        ft.add(s[i].first, -1);
        ft2.add(s[i].second, -1);
        // 補集合を考える
        ans += m - i - 1;
        ans -= ft.sum(s[i].second, n);
        ans -= ft2.sum(0, s[i].second + 1);
    }
    cout << ans << endl;
}
