#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 🔷初見でどうやったら解けるか
// 組合せ最適化問題だが、明らかに法則性がありそうな形をしている
// いくつか実験して法則を見つける

int main() {
    string s; cin >> s;
    int n = s.size();
    int ans = n;

    rep(i, n - 1) {
        int now = s[i] - '0';
        int nx = s[i + 1] - '0';
        int c = (now - nx + 10) % 10;
        ans += c;
    }
    ans += s[n - 1] - '0';

    cout << ans << endl;
}
