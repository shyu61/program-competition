#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 🔷初見でどうやったら解けるか
// 後ろから削っていき、初めて条件を満たさなくなる点 -> 前から見ていき初めて条件を満たす点
// 故に頻度配列を求めればO(N)で解ける

// 🔷抑えるべき抽象論は？
// 対偶となる操作を考えることは有効
// - 後ろから操作 → 前から逆の操作
// - 除外していく → 0から加えて構築していく

int main() {
    int n, m; cin >> n >> m;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    vector<bool> c(m + 1);
    int cnt = 0, pos = n;
    rep(i, n) {
        if (!c[a[i]]) {
            c[a[i]] = true;
            cnt++;
        }
        if (cnt == m) {
            pos = i;
            break;
        }
    }

    cout << n - pos << endl;
}
