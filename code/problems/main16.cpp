// E - Max/Min
// https://atcoder.jp/contests/abc356/tasks/abc356_e
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int AMAX = 1e6;

int main() {
    int n; cin >> n;
    vector<int> c(AMAX + 1, 0), s(AMAX + 1, 0);
    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        c[a]++;
    }

    // 各値の個数の累積和
    for (int i = 0; i <= AMAX; i++) s[i + 1] = s[i] + c[i];

    ll ans = 0;
    for (int i = 1; i <= AMAX; i++) {
        if (c[i] == 0) continue;
        for (int k = 1; k * i <= AMAX; k++) {
            // floor関数の答えがkになる要素数つまり、`k*Ai <= Aj < (k+1)*Ai` を満たすAjの個数をカウント
            // (k+1)*Aiは常に定義閾内とは限らないので終端とminをとる
            // k * floor関数がkになる個数 * iの個数
            ans += ll(k) * (s[min(AMAX + 1, (k + 1) * i)] - s[k * i]) * c[i];
        }
        // 重複分を引く
        ans -= ll(c[i]) * (c[i] + 1) / 2;
    }

    cout << ans << endl;
}
