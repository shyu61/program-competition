#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int n, k; string s; cin >> n >> k >> s;
    int ans = 0;
    rep(i, n - k + 1) {
        if (s.substr(i, k) == string(k, 'O')) {
            ans++;
            i += k - 1;
        }
    }
    cout << ans << endl;
}
