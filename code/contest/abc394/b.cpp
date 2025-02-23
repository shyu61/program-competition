#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int n; cin >> n;
    vector<string> sa(n);
    rep(i, n) cin >> sa[i];

    sort(sa.begin(), sa.end(), [](const string& a, const string& b) {
        return a.size() < b.size();
    });
    string ans = "";
    rep(i, n) {
        ans += sa[i];
    }
    cout << ans << endl;
}
