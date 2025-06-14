#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    int ans = 0, pre = 0;
    set<int> st;
    unordered_map<int, vector<int>> mp;
    rep(i, n) {
        if (pre == 0 && a[i] > 0) ans++;
        mp[a[i]].push_back(i);
        st.insert(a[i]);
        pre = a[i];
    }

    int mx = 0;
    for (auto it = st.begin(); it != st.end(); it++) {
        for (auto i : mp[*it]) {
            a[i] = 0;
            if (i > 0 && i < n - 1 && a[i - 1] > 0 && a[    i + 1] > 0) ans++;
            if (i > 0 && i < n - 1 && a[i - 1] == 0 && a[i + 1] == 0) ans--;
            if (i == 0 && a[i + 1] == 0) ans--;
            if (i == n - 1 && a[i - 1] == 0) ans--;
        }
        mx = max(mx, ans);
    }
    cout << mx << endl;
}
