#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// ポイント
// unordered_mapのkeyはintやstringは使えるが、pairやtupleは使えない

int main() {
    int n; cin >> n;
    vector<string> s(n);
    rep(i, n) cin >> s[i];

    unordered_map<string, bool> mp;
    rep(i, n) {
        if (mp[s[i]]) continue;
        mp[s[i]] = true;
        cout << i + 1 << '\n';
    }
}
