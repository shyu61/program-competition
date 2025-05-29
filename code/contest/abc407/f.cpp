#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;

int main() {
    int n; cin >> n;
    vector<P> a(n);
    rep(i, n) {
        cin >> a[i].first;
        a[i].second = i;
    }

    vector<int> L(n), R(n);
    {
        stack<P> st;
        rep(i, n) {
            while (!st.empty() && st.top().first <= a[i].first) st.pop();
            if (st.empty()) L[i] = i;
            else L[i] = i - st.top().second - 1;
            st.push(a[i]);
        }
    }
    {
        stack<P> st;
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && st.top().first < a[i].first) st.pop();
            if (st.empty()) R[i] = n - i - 1;
            else R[i] = st.top().second - i - 1;
            st.push(a[i]);
        }
    }

    vector<ll> res(n + 3);
    rep(i, n) {
        int minx = min(L[i], R[i]);
        int maxx = max(L[i], R[i]);
        res[1] += a[i].first;
        res[2 + minx] -= a[i].first;
        res[2 + maxx] -= a[i].first;
        res[3 + minx + maxx] += a[i].first;
    }

    vector<ll> res2(n + 1), ans(n + 1);
    rep(i, n) res2[i + 1] = res2[i] + res[i + 1];
    rep(i, n) ans[i + 1] = ans[i] + res2[i + 1];

    for (int i = 1; i <= n; i++) cout << ans[i] << '\n';
}
