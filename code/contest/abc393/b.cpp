#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    string s; cin >> s;
    int n = s.size(), ans = 0;
    rep(i, n) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                if (j - i != k - j) continue;
                if (s[i] == 'A' && s[j] == 'B' && s[k] == 'C') ans++;
            }
        }
    }
    cout << ans << endl;
}
