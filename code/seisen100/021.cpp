#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 想定解
// 組合せ最適化を判定問題帰着させる

// 罠
// 判定に必要なのは時間だが、二分探索は高さでする必要がある
// 0秒時点で上回ってしまう条件を除外する必要がある
// 0秒時点で1つ撃つ点

int main() {
    int n; cin >> n;
    vector<int> h(n), s(n);
    rep(i, n) cin >> h[i] >> s[i];

    auto check = [&](ll nh) -> bool {
        vector<int> cnt(n);
        rep(i, n) {
            if (h[i] > nh) return false;
            ll t = (nh - h[i]) / s[i];
            t = max(t, 0ll);
            if (t >= n - 1) continue;
            cnt[t]++;
        }
        int sum = 0;
        rep(i, n) {
            sum += cnt[i];
            if (sum > i + 1) return false;
        }
        return true;
    };

    ll ok = 1e15, ng = -1;
    while (abs(ok - ng) > 1) {
        ll mid = (ok + ng) / 2;
        check(mid) ? ok = mid : ng = mid;
    }

    cout << ok << endl;
}
