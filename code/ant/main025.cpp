// 貪欲法: Saruman's Army: p47
#include <bits/stdc++.h>
using namespace std;

// 区間スケジューリング問題で貪欲法が使えることを知っていると、類問なので貪欲法が思いつける
// 貪欲法は、逐次問題の各ステップに対して行う操作を明確に定義できる場合である
// 逐次問題なのでいくつか実験することと、繰り返し単位を見抜くことが重要

int main() {
    int n, r; cin >> n >> r;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());

    // 2ステップからなる繰り返し構造を持つ
    int i = 0, ans = 0;
    while (i < n) {
        int s = a[i++];
        while (i < n && a[i] <= s + r) i++;

        int p = a[i - 1];
        while (i < n && a[i] <= p + r) i++;
        ans++;
    }

    cout << ans << endl;
}
