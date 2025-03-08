#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 想定解
// 右区間を固定して尺取り法

// 罠
// 各区間の終点に注目すればいいことは簡単に思いつけるが、それでループすると実装が複雑になる点
// → 位置配列として記録しmについてループする必要がある点

// ポイント
// 求めるものの種類によってループ対象を変えるとよい
// - 数え上げの場合は連続的に走査すると考えやすい

int main() {
    int n, m; cin >> n >> m;
    vector<int> maxl(m + 1, -1);
    rep(i, n) {
        int l, r; cin >> l >> r;
        maxl[r] = max(maxl[r], l);
    }

    int l = 1; ll ans = 0;
    for (int r = 1; r <= m; r++) {
        if (l <= maxl[r]) l = maxl[r] + 1;
        ans += r - l + 1;
    }
    cout << ans << endl;
}
