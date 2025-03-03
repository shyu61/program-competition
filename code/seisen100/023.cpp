#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 想定解
// 半分全列挙 + 二分探索
// 矢の本数は常に4本という点から半分全列挙を連想できるかが鍵

// 罠
// 得点自体の二分探索はできない点。離散的で単調性が成立しない

int main() {
    int n, m; cin >> n >> m;
    vector<int> s(n);
    rep(i, n) cin >> s[i];

    vector<int> s1;
    rep(i, n) {
        s1.push_back(s[i]);
        for (int j = i; j < n; j++) {
            s1.push_back(s[i] + s[j]);
        }
    }
    s1.push_back(0);
    sort(s1.begin(), s1.end());
    s1.erase(unique(s1.begin(), s1.end()), s1.end());

    vector<int> s2 = s1;

    int ans = 0;
    rep(i, s1.size()) {
        int x = upper_bound(s2.begin(), s2.end(), m - s1[i]) - s2.begin();
        if (x == 0) continue;
        x--;
        ans = max(ans, s1[i] + s2[x]);
    }
    cout << ans << endl;
}
