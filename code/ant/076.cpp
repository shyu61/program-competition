// しゃくとり法: p135
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 尺取り法のコアは、重複部分を再利用しつつキャンセルと追加部分だけ再計算すること。
// キャンセルと追加部分だけの再計算で済むのは、配列に単調性がある場合のみ
// また、重複部分が再利用できるようなものである必要があり、総和はその典型。min/maxはそのままでは再利用でいないのでdequeuなど特殊な構造体を使う必要がある

// 外側のforでleftを進めつつ、内側のwhileでrightを勧めるのが定番の書き方

// 区間和では累積和も選択肢に入るが、累積和は求めたい区間が明確な場合に限る。本問題でも求める区間を二分探索で求めて渡すことで計算できなくはない。
// 本問題のように、"条件を満たす区間"を求めつつその区間和を求めたい場合（つまり求めたい区間が不明確）は尺取り法が適している。

int main() {
    int n, S; cin >> n >> S;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int right = 0, sum = 0, ans = n;
    for (int left = 0; left < n; left++) {
        while (right < n && sum < S) sum += a[right++];

        if (sum >= S) {
            ans = min(ans, right - left);
            // 左端をキャンセル
            sum -= a[left];
        } else break;
    }

    cout << ans << endl;
}
