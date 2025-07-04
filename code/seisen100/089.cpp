#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// https://atcoder.jp/contests/joi2013ho/tasks/joi2013ho1
// 🔷初見でどうやったら解けるか
// 組合せ最適化問題の内、操作系で1回操作の問題。故に全探索かエスパーを基本路線で考える。
// 全探索はO(n^2)なので間に合わない。エスパーする上でコツを押さえつつ考えていく。
// 具体的な操作を考えていくときは、実質的に影響がある部分のみに注目して考えるのが定石。
// 区間処理で、解に関係がある相対関係が変化するのは[l,r]でのlとrのみ。
// つまりは[,l-1]と[r+1,]の2つの区間と結合することによる影響を評価すれば良いことがわかる。これは部分長を事前に計算しておけばO(1)

int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    a.push_back(a.back());
    n = a.size();

    int cnt = 1;
    vector<int> c;
    for (int i = 1; i < n; i++) {
        if (a[i] == a[i - 1]) {
            c.push_back(cnt);
            cnt = 1;
        } else cnt++;
    }

    int m = c.size();
    c.push_back(0);
    int ans = c[0] + c[1];
    for (int i = 1; i < m; i++) {
        ans = max(ans, c[i - 1] + c[i] + c[i + 1]);
    }
    cout << ans << endl;
}
