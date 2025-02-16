#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    string s; cin >> s;
    int ans = 0;
    rep(i, s.size()) {
        if (s[i] == 'A') {
            for (int j = i + 1; j < s.size(); j++) {
                if (s[j] == 'B') {
                    int d = j - i;
                    if (d < s.size() && s[j + d] == 'C') ans++;
                }
            }
        }
    }
    cout << ans << endl;
}
