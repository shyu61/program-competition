// D - 2017-like Number
// https://atcoder.jp/contests/abc084/tasks/abc084_d
#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5;

int main() {
    // エラトステネスの篩
    vector<int> a(MAX + 1, 1);
    a[0] = a[1] = 0;
    for (int i = 2; i < MAX; i++) {
        if (a[i] == 0) continue;
        for (int j = 2; j * i < MAX; j++) a[j * i] = 0;
    }

    // 累積和
    vector<int> s(MAX + 1, 0);
    for (int i = 0; i < MAX; i++) {
        s[i + 1] = s[i] + (a[i] && a[(i + 1) / 2]);
    }

    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        // 累積和は[l,r)で解は[l,r]なので++rする
        cout << s[++r] - s[l] << endl;
    }
}
