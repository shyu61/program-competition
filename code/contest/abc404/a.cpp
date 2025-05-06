#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;

int main() {
    string s; cin >> s;
    vector<bool> a(26);
    for (auto c : s) a[c - 'a'] = true;
    rep(i, 26) {
        if (!a[i]) {
            cout << char(i + 'a') << endl;
            return 0;
        }
    }
}

int main() {
    string s; cin >> s;
    sort(s.begin(), s.end());
    s.erase(unique(s.begin(), s.end()), s.end());

    int n = s.size();
    rep(i, n) {
        char c = i + 'a';
        if (s[i] != c) {
            cout << c << endl;
            return 0;
        }
    }
    cout << char(n + 'a') << endl;
}
