#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    string s; cin >> s;
    int n = s.size();

    auto is_ok = [&](char c) -> bool {
        return c == 'A' || c == 'T' || c == 'G' || c == 'C';
    };

    int ans = 0;
    rep(i, n) {
        if (!is_ok(s[i])) continue;
        int j = i;
        while (j < n && is_ok(s[j])) j++;
        ans = max(ans, j - i);
    }
    cout << ans << endl;
}
