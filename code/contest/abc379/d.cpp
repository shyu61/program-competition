#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<ll, ll>;

// ジャンル
// クエリ問題, 逐次問題, 区間更新

// 方針
// クエリの種類が複数ある場合は、何を高速化する必要があるのかをまず考える
// クエリ3は線形に走査してもO(Q)なので高速化の必要はない。故にクエリ2さえ高速に処理できれば良い
// クエリ2は区間更新だが、区間更新は更新区間が連続なら端点情報を持てば十分であることが多い。
// この問題では、trackするのは高さではなく現在時刻と見方を変えれば、更新対象は区間ではなくなる。
// 更新物が過去全てに渡る場合は逆に考えと更新の必要がなくなる。

// ポイント
// 二分探索の方法
//   - 昇順: lower_bound(a.begin(), a.end(), x);
//   - 降順: lower_bound(a.begin(), a.end(), x, greater<>())
//   - 昇順のままx以下を取りたい時: 結果がイコールが大きいか判定して一つ減らす
//       int p = lower_bound(a.begin(), a.end(), x) - a.begin();
//       if (p >= a.size()) p--;
//       if (a[p] > x) p--;
//       if (p < 0) return;

int main() {
    int q; cin >> q;

    vector<P> a;
    ll now = 0, cnt = 0, rm = 0, cur = 0;
    while (q--) {
        int type; cin >> type;
        if (type == 1) cnt++;
        else if (type == 2) {
            int t; cin >> t;
            a.emplace_back(now, cnt);
            now += t;
        } else {
            int h; cin >> h;
            int x = lower_bound(a.begin() + cur, a.end(), make_pair(now - h, 0ll)) - a.begin();
            if (x >= a.size()) x--;
            else if (a[x].first > now - h) x--;

            if (x < 0) {
                cout << 0 << '\n';
                continue;
            }

            int res = a[x].second - rm;
            rm = a[x].second;

            cout << res << '\n';
        }
    }
}

// queueを使った解法
int main() {
    int q; cin >> q;

    queue<ll> que;
    ll now = 0;
    while (q--) {
        int type; cin >> type;
        if (type == 1) que.push(now);
        else if (type == 2) {
            int t; cin >> t;
            now += t;
        } else {
            int h; cin >> h;
            int ans = 0;
            while (!que.empty() && now - que.front() >= h) {
                que.pop();
                ans++;
            }
            cout << ans << '\n';
        }
    }
}
