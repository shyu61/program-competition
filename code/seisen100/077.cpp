#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
const int M = 1e5;

// 🔷抑えるべき抽象論は？
// 累積和は半開区間
// "間の距離"は"スタートからの位置"と読み替える

int main() {
    int n, m; cin >> n >> m;
    vector<int> a(n);
    rep(i, n - 1) {
        int d; cin >> d;
        a[i + 1] = (a[i] + d) % M;
    }

    int ans = 0, pos = 0;
    rep(i, m) {
        int x; cin >> x;
        int l = pos, r = pos + x;
        if (l > r) swap(l, r);
        ans = (ans + a[r] - a[l] + M) % M;
        pos += x;
    }

    cout << ans << endl;
}
