#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// https://atcoder.jp/contests/abc134/tasks/abc134_e

int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    multiset<int> st;
    for (auto v : a) {
        auto it = st.lower_bound(v);
        if (it != st.begin()) {
            it--;
            st.erase(it);
        }
        st.insert(v);
    }
    cout << st.size() << endl;
}
