#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// ポイント
// 二部マッチング系は、クロスをswapで解消することで最適になるケースがある
// 証明は、直感的には2つに着目するとお互いに相手にとってより遠い学校とマッチングしているから
// 厳密には、f(z)=|z-x|-|z-y|の単調減少性を示すことにより証明できる
// つまりはi<jについてf(i)>=f(j)が成立するとき、f(i)-f(j)=(|i-x|-|i-y|)-(|j-x|-|j-y|)=(|i-x|+|j-y|)-(|j-x|+|i-y|)>=0より
// swap(i,j)した方が大きくなることが分かる。

int main() {
    int n; cin >> n;
    vector<int> a(n), b(n);
    rep(i, n) cin >> a[i];
    rep(i, n) cin >> b[i];

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    ll ans = 0;
    rep(i, n) ans += abs(a[i] - b[i]);
    cout << ans << endl;
}
