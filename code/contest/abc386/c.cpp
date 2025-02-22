#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// ジャンル
// 文字列, 編集距離

// ポイント
// Yes/No問題で条件が複数ある時はsolve関数を使うと良い
// 対称な条件がある場合は、swapで省略できないか考える
//   - 挿入と削除など
// substrについて
//   - 0から見る時は半開区間になる
//   - [l,r)を取りたい時は、substr(l,r-l)

bool solve() {
    int k; string s, t; cin >> k >> s >> t;
    int n = s.size(), m = t.size();

    if (s == t) return true;
    if (abs(n - m) > 1) return false;
 
    // 置換
    if (n == m) {
        int cnt = 0;
        rep(i, n) if (s[i] != t[i]) cnt++;
        return cnt <= 1;
    }
    // 削除
    if (n < m) {
        swap(s, t);
        swap(n, m);
    }
    int p = m;
    rep(i, m) if (s[i] != t[i]) {
        p = i;
        break;
    }
    s = s.substr(0, p) + s.substr(p + 1);
    return s == t;
}

int main() {
    if (solve()) cout << "Yes" << endl;
    else cout << "No" << endl;
}
