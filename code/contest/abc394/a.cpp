#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    string s; cin >> s;
    int n = s.size();
    string ans = "";
    rep(i, n) {
        if (s[i] == '2') ans += s[i];
    }
    cout << ans << endl;
}
