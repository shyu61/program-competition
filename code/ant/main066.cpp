// 素数に関する基本的なアルゴリズム(素数の個数): p111
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 通常の素数判定はO(√n)で十分な速度だが、素数判定したい整数がk個数あればO(k√n)コストがかかる
// その場合はエラトステネスの篩を使うと個数kに依存せずO(nlog(log(n)))で判定できる
// 篩を作るのに約O(n)のコストがかかるが、この篩を作ってしまえばはn以下の整数であればO(1)で素数判定ができる

int main() {
    int n; cin >> n;

    vector<bool> a(n);
    int cnt = 0;
    // O(nlog(log(n)))
    for (int i = 2; i <= n; i++) {
        if (a[i]) continue;
        cnt++;
        for (int j = 1; i * j <= n; j++) a[i * j] = true;
    }

    cout << cnt << endl;
}
