// Minimum Scalar Product: p117
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 組み合わせ最適化問題なので、全探索/貪欲法/DP/グラフなどを考える
// smallは全探索でいけるがlargeは難しそうで、メモ化も難しい
// 貪欲でいけないかをまず考えてみる。明らかに小さい数と大きい数を掛け合わせれば良いことに気付くのでsortすれば良いことに気づける
// サンプルを試してみても良い。

int main() {
    int n; cin >> n;
    vector<int> v1(n), v2(n);
    for (int i = 0; i < n; i++) cin >> v1[i];
    for (int i = 0; i < n; i++) cin >> v2[i];

    sort(v1.begin(), v1.end());
    sort(v2.rbegin(), v2.rend());

    ll ans = 0;
    for (int i = 0; i < n; i++) ans += ll(v1[i]) * v2[i];
    cout << ans << endl;
}
