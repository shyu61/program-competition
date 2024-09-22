// 貪欲法: 区間スケジューリング問題
// p43
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n; cin >> n;
    vector<pair<int, int>> ts(n);
    for (int i = 0; i < n; i++) cin >> ts[i].second >> ts[i].first;

    // 現在時刻より開始時刻が後 && 終了時刻が早いものを優先的に選択
    sort(ts.begin(), ts.end());
    int now = -1, ans = 0;
    for (auto [t, s] : ts) {
        if (s <= now) continue;
        ans++;
        now = t;
    }

    cout << ans << endl;
}
