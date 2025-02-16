#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

int main() {
    int n; string s; cin >> n >> s;

    // 中心を決める
    int ones = 0;
    rep(i, n) {
        if (s[i] == '1') ones++;
    }
    int center = ones / 2 + 1;
    int ix = 0;
    rep(i, n) {
        if (s[i] == '1') center--;
        if (center == 0) {
            ix = i;
            break;
        }
    }

    int sum = 0;
    vector<int> cnt(n);  // ある位置において前に0がいくつあるか
    rep(i, n) {
        if (s[i] == '0') sum++;
        cnt[i] = sum;
    }

    ll ans = 0;
    rep(i, ix) {
        if (s[i] == '1') {
            ans += cnt[ix] - cnt[i];
        }
    }
    for (int i = ix + 1; i < n; i++) {
        if (s[i] == '1') {
            ans += cnt[i] - cnt[ix];
        }
    }
    cout << ans << endl;
}
