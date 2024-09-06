// E - Yet Another Sigma Problem
// https://atcoder.jp/contests/abc353/tasks/abc353_e
// ヒストグラムを使った解法
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n; cin >> n;
    vector<string> s(n);
    for (int i = 0; i < n; i++) cin >> s[i];

    sort(s.begin(), s.end());
    vector<int> a(n);
    // s[i]とs[i+1]のlcpを求める
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < s[i].size(); j++) {
            if (s[i][j] == s[i + 1][j]) a[i]++;
            else break;
        }
    }

    ll ans = 0;
    vector<pair<int, int>> st;  // (index, height)
    for (int i = 0; i < n; i++) {
        // 自身より低いbarに当たるまで取り出し続ける
        int left = i;
        while (!st.empty() && a[i] <= st.back().second) {
            left = st.back().first;
            st.pop_back();
        }

        st.emplace_back(left, a[i]);

        // stackに残ったものを加算する（階段状になっている）
        for (int j = 0; j < st.size() - 1; j++) {
            ans += ll(st[j].second) * (st[j + 1].first - st[j].first);
        }
        // 取り出した部分までの面積を加算
        ans += ll(a[i]) * (i - left + 1);
    }

    cout << ans << endl;
}
