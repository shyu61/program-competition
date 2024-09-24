// デックの利用: スライド最小値: p300
// dequeを使わないプレーンな尺取り法での実装
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    set<pair<int, int>> s;
    for (int i = 0; i < k - 1; i++) s.emplace(a[i], i);

    vector<int> ans;
    int right = k - 1;
    for (int left = 0; left <= n - k; left++) {
        s.emplace(a[right], right);
        right++;

        auto [v, i] = *s.begin();
        ans.push_back(v);
        if (i == left) s.erase(s.begin());
    }

    for (auto x : ans) cout << x << " ";
    cout << endl;
}
