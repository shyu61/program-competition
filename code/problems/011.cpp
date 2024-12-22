// E - Water Tank
// https://atcoder.jp/contests/abc359/tasks/abc359_e
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n; cin >> n;
    vector<ll> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];

    stack<pair<ll, int>> st;
    ll now = 0;
    for (int i = 0; i < n; i++) {
        int w = 1;
        while (!st.empty() && st.top().first <= h[i]) {
            auto [nh, nw] = st.top(); st.pop();
            now -= nh * nw;
            w += nw;
        }
        st.emplace(h[i], w);
        now += h[i] * w;
        cout << now + 1 << " ";
    }
    cout << endl;
}
