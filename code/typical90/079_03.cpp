#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
const int INF = 1001001001;

// 🔷初見でどうやったら解けるか
// 組合せ最適化問題で最初に考えるのは解が決定的かどうか。操作は可換なのでほぼ決定的になる。(厳密には貪欲か)
// 自由度の低い端から順に考えると、最後の要素以外は必ず+にできることがわかる。ゆえにその時点で最後の要素が+ならそれが最大値、-なら、
// 絶対値が小さいものに-をなすりつけられるので、その要素を引いた値が最大値になる

// 🔷抑えるべき抽象論は？
// 組合せ最適化問題で、操作が可換なパターン(数え上げに近い貪欲組合せ最適化アプローチ)

int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    ll ans = 0;
    int mn = INF;
    rep(i, n) {
        ans += abs(a[i]);
        mn = min(mn, abs(a[i]));
    }
    rep(i, n - 1) {
        if (a[i] < 0) {
            a[i] *= -1;
            a[i + 1] *= -1;
        }
    }
    if (a[n - 1] >= 0) cout << ans << endl;
    else cout << ans - mn * 2 << endl;
}
