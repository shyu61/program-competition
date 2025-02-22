#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    string s; cin >> s;
    int n = s.size();
    int ans = 0;
    int cur = 0;
    while (cur < n) {
        if (cur < n - 1 && s.substr(cur, 2) == "00") cur += 2;
        else cur++;
        ans++;
    }
    cout << ans << endl;
}
