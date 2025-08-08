#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// https://atcoder.jp/contests/abc006/tasks/abc006_4

// 🔷初見でどうやったら解けるか
// ソートするための操作を、補集合を考えて動かさないカードの最大化と考えると、LISを求める問題に帰着する

// 🔷抑えるべき抽象論は？
// LISはソートと相性が良い

int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    const int INF = 1001001001;
    vector<int> dp(n + 1, INF);
    rep(i, n) {
        *lower_bound(dp.begin(), dp.end(), a[i]) = a[i];
    }
    int lis = lower_bound(dp.begin(), dp.end(), INF) - dp.begin();
    cout << n - lis << endl;
}
