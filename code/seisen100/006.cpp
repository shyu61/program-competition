#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// ポイント
// 全探索する時は、何について全探索するかをしっかり考える
// - 定数個対象がある時は、最後の1つは「残り」を考えることでskipできることも多い

// 全探索の対象を変える解法
int main() {
    int n; string s; cin >> n >> s;
    int ans = 0;
    rep(x, 1000) {
        string t = to_string(x);
        t.insert(0, 3 - t.size(), '0');
        int pos = 0;
        rep(i, n) {
            if (s[i] == t[pos]) pos++;
            if (pos >= 3) break;
        }
        if (pos >= 3) ans++;
    }
    cout << ans << endl;
}

// 1,2つ目は全探索する解法
int main() {
    int n; string s; cin >> n >> s;
    unordered_set<int> st;
    vector<int> a(n);
    for (int i = n - 1; i >= 0; i--) {
        st.insert(s[i]);
        a[i] = st.size();
    }

    int ans = 0;
    vector<bool> used(100);
    rep(i, n - 2) {
        for (int j = i + 1; j < n - 1; j++) {
            int num = (s[i] - '0') * 10 + (s[j] - '0');
            if (used[num]) continue;
            ans += a[j + 1];
            used[num] = true;
        }
    }
    cout << ans << endl;
}
