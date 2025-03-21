#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// ポイント
// 逐次問題はイベントが発生する点のみを考えるという発想は重要

int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    vector<int> ch;  // 色が変化する点を保存
    int ans = 0;
    rep(i, n) {
        if (a[i] == 0) ans++;
        if (i == 0 || a[i - 1] == a[i]) continue;
        if (i % 2 == 1) {
            int pos = 0;
            if (!ch.empty()) {
                pos = ch.back();
                ch.pop_back();
            }
            if (a[i] == 0) ans += i - pos;
            else ans -= i - pos;
        } else ch.push_back(i);
    }
    cout << ans << endl;
}
