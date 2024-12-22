// Ants: p23
#include <bits/stdc++.h>
using namespace std;

// 対称性を利用して計算量を抑える問題
// ジャンルとしては逐次シミュレーション問題だが、その前に変数が複数ある場合は対称性を確認することが重要

int main() {
    int l, n; cin >> l >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int maxv = 0, minv = 0;
    for (int i = 0; i < n; i++) {
        maxv = max(maxv, max(a[i], l - a[i]));
        minv = max(minv, min(a[i], l - a[i]));
    }

    cout << minv << " " << maxv << endl;
}
