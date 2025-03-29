#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<ll, ll>;

int main() {
    string s; cin >> s;
    int n = s.size();

    ll ans = 0;
    vector<P> cnt(26);
    for (int i = n - 1; i >= 0; i--) {
        int c = s[i] - 'A';
        ans += cnt[c].second - cnt[c].first * (i + 1);
        cnt[c].first++;
        cnt[c].second += i;
    }

    cout << ans << endl;
}
