#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    string s; cin >> s;
    int n = s.size();

    double ans = 0;
    rep(i, n) {
        if (s[i] != 't') continue;
        for (int j = i + 2; j < n; j++) {
            if (s[j] != 't') continue;
            int cnt = 0;
            for (int k = i + 1; k < j; k++) {
                if (s[k] == 't') cnt++;
            }
            ans = max(ans, double(cnt) / (j - i - 1));
        }
    }
    cout << fixed << setprecision(10) << ans << endl;
}
