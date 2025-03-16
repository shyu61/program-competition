#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 文字列の挿入はinsertを使う

int main() {
    string s; cin >> s;

    int ans = 0;
    bool ev = true;
    for (auto c : s) {
        // 条件を満たす時だけ偶奇を入れ替える
        if ((ev && c == 'i') || (!ev && c == 'o')) ev = !ev;
        else ans++;
    }
    if (!ev) ans++;
    cout << ans << endl;
}

int main() {
    string s; cin >> s;

    int ans = 0;
    rep(i, s.size()) {
        if (i % 2 == 0) {
            if (s[i] == 'o') {
                ans++;
                s.insert(i, "i");
            }
        } else {
            if (s[i] == 'i') {
                ans++;
                s.insert(i, "o");
            }
        }
    }
    if (s.size() % 2 != 0) ans++;
    cout << ans << endl;
}
