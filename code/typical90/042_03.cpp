#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
const int INF = 1001001001;

// https://atcoder.jp/contests/abc182/tasks/abc182_c

// 🔷抑えるべき抽象論は？
// 条件に3の倍数が絡む時は、特殊なデータ構造を使わずとも、場合分けで解ける可能性を考える
// - 桁和で考えた時、剰余は3通りしかないので、十分場合分けで対応できる。

// 全探索による解法
int main() {
    string s; cin >> s;
    int n = s.size();
    int n2 = 1 << n;

    int ans = INF;
    for (int i = 1; i < n2; i++) {
        int sum = 0, cnt = 0;
        rep(j, n) {
            if (i >> j & 1) {
                sum += s[j] - '0';
                cnt++;
            }
        }
        if (sum % 3 == 0) ans = min(ans, n - cnt);
    }
    if (ans == INF) ans = -1;
    cout << ans << endl;
}

// 場合分けによる解法
int solve() {
    string s; cin >> s;
    int n = s.size();

    int sum = 0;
    vector<int> cnt(3);
    rep(i, n) {
        int c = s[i] - '0';
        sum += c;
        cnt[c % 3]++;
    }

    auto f = [&]() -> int {
        if (sum % 3 == 0) return 0;
        if (sum % 3 == 1) {
            if (cnt[1] >= 1) return 1;
            if (cnt[2] >= 2) return 2;
        }
        if (sum % 3 == 2) {
            if (cnt[2] >= 1) return 1;
            if (cnt[1] >= 2) return 2;
        }
        return -1;
    };

    int res = f();
    if (res >= n) return -1;
    return res;
}

int main() {
    cout << solve() << endl;
}
