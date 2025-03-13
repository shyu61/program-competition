#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 想定解
// エラトステネスの篩を利用してO(nloglogn)で解く問題

// 障壁
// 愚直に素因数分解したらO(N√N)でTLEなので、うまく結果を再利用して高速化する必要がある
// 約数と倍数は常にセット。bottom-up的な倍数の方が重複構造を再利用しやすい
// → 倍数方向に素数を調べていくといえば、エラトステネスの篩しかない

// ポイント
// Σ_i_n(√i) ≒ O(n^3/2)

int main() {
    int n, k; cin >> n >> k;

    vector<int> a(n + 1);
    vector<bool> is_pn(n + 1, true);
    is_pn[0] = is_pn[1] = false;
    for (int i = 2; i <= n; i++) {
        if (is_pn[i]) {
            a[i]++;
            for (int j = i * 2; j <= n; j += i) {
                is_pn[j] = false;
                a[j]++;
            }
        }
    }

    int ans = 0;
    rep(i, n + 1) {
        if (a[i] >= k) ans++;
    }
    cout << ans << endl;
}
