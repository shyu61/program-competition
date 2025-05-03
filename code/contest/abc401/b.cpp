#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;

int main() {
    int n; cin >> n;
    int ans = 0; bool is_login = false;
    rep(i, n) {
        string s; cin >> s;
        if (s == "login") is_login = true;
        if (s == "logout") is_login = false;
        if (s == "private" && !is_login) ans++;
    }
    cout << ans << endl;
}
