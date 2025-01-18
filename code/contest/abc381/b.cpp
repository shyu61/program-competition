#include <bits/stdc++.h>
using namespace std;

// ポイント
// 数式を数式だけで見ないこと。必ず意味を考えること
// -> `s[i*2-1]==s[i*2]`とは単に偶数ごとに隣接文字が等しいということだけ
// -> 「ちょうど2個現れる」も隣接が等しいので、bool値で管理可能

int main() {
    string s; cin >> s;
    int n = s.size();

    bool ok = true;
    if (n % 2 != 0) ok = false;

    vector<bool> seen(n);
    for (int i = 0; i + 1 < n; i += 2) {
        if (s[i] != s[i + 1]) ok = false;
        if (seen[s[i]]) ok = false;
        seen[s[i]] = true;
    }

    cout << (ok ? "Yes" : "No") << endl;
}
