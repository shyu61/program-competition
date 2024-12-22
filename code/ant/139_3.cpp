// ダブリング: p307
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 思考フロー
// 区間を貪欲的に辿った時、範囲内に幾つの区間があるかを数え上げる問題
// -> 貪欲的ということは遷移が確定的になるということなので、遷移配列を作れる
// -> 求めるものは「数え上げ」という累積構造を持っているので、ダブリングができる

// ダブンリングの検討シーン
// - 遷移を事前計算できる(遷移が確定的である)
// - 求めたいものが累積的である
//   - ダブリングは2の累乗ごとの塊ごとにまとめて計算するので、sumや数え上げなどの累積構造が必要

const int MAX_LOG = 32;

int main() {
    int N, M; cin >> N >> M;
    vector<int> s(N * 2), t(N * 2);
    for (int i = 0; i < N; i++) cin >> s[i] >> t[i];

    // 複製
    for (int i = 0; i < N; i++) {
        if (t[i] < s[i]) t[i] += M;
        s[N + i] = s[i] + M;
        t[N + i] = t[i] + M;
    }

    // 区間の端点をソート
    vector<pair<int, int>> ps(N * 4);
    for (int i = 0; i < N * 2; i++) {
        ps[i] = make_pair(t[i], i);
        ps[N * 2 + i] = make_pair(s[i], N * 2 + i);
    }
    sort(ps.begin(), ps.end());

    vector<vector<int>> next(MAX_LOG, vector<int>(N * 2, -1));  // next[k][i] := j, iの2^k先の区間がj
    int last = -1;
    for (int i = N * 4 - 1; i >= 0; i--) {
        int id = ps[i].second;
        if (id < N * 2) {  // idはtである
            next[0][id] = last;
        } else {  // idはsである
            id -= N * 2;
            if (last < 0 || t[last] > t[id]) last = id;
        }
    }

    for (int k = 0; k + 1 < MAX_LOG; k++) {
        for (int i = 0; i < N * 2; i++) {
            if (next[k][i] < 0) next[k+1][i] = -1;
            else next[k+1][i] = next[k][next[k][i]];
        }
    }

    int ans = 0;
    for (int i = 0; i < N; i++) {
        int res = 0, j = i;
        for (int k = MAX_LOG - 1; k >= 0; k--) {
            int j2 = next[k][j];
            if (j2 >= 0 && t[j2] <= s[i] + M) {
                j = j2;
                res += (1 << k);
            }
        }
        ans = max(ans, res + 1);
    }
    cout << ans << endl;
}
