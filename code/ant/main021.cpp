// 尺取り法: p135
#include <bits/stdc++.h>
using namespace std;

// 尺取り法の本質は、重複部分の結果は使い回し、範囲外になった部分はキャンセル、新規に範囲になる部分は追加計算する。
// 連続区間に対するもので、全体で単調性が成立する時のみ使える
// 最小/最大個数, 合計値, 最大/最小値(最大/最小になる値のindexが単調増加する)

int main() {
    int n, S; cin >> n >> S;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int ans = n + 1;
    int sum = 0, right = 0;
    for (int left = 0; left < n; left++) {
        while (sum < S && right < n) sum += a[right++];

        if (sum >= S) {
            ans = min(ans, right - left);
            sum -= a[left];
        } else break;
    }

    if (ans > n) ans = -1; // 解なし
    cout << ans << endl;
}
