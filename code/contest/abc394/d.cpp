#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// ジャンル
// 文字列問題, 逐次問題

// 方針
// 前から逐次的に処理していけば問題ないのでstackで管理しつつ削っていく
// substrは線形時間かかることに注意する

// ポイント
// erase操作を行う時は条件判定を特に気をつける
// - 配列外参照や終了判定が待ちがってないか注意する

int main() {
    string s; cin >> s;
    int n = s.size();

    auto is_ok = [&](string s) -> bool {
        return s == "()" || s == "[]" || s == "<>";
    };

    stack<char> st;
    rep(i, n) {
        if (!st.empty()) {
            string ns = {st.top(), s[i]};
            if (is_ok(ns)) st.pop();
            else st.push(s[i]);
        } else {
            st.push(s[i]);
        }
    }

    if (st.size() == 0) cout << "Yes" << endl;
    else cout << "No" << endl;
}

int main() {
    string s; cin >> s;
    int n = s.size();
    int i = 0;
    while (i < s.size() - 1 && s.size() > 1) {
        if (s.substr(i, 2) == "()" || s.substr(i, 2) == "[]" || s.substr(i, 2) == "<>") {
            if (i + 2 < n) s = s.substr(0, i) + s.substr(i + 2);
            else s = s.substr(0, i);
            if (i > 0) i--;
        } else i++;
    }

    if (s.size() == 0) cout << "Yes" << endl;
    else cout << "No" << endl;
}
