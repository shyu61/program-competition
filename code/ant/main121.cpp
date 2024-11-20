// 包除原理
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 最小公倍数について
// lcm(a,b) = gcd(a,b) * (aにしかない因数) * (bにしかない因数)
// a = gcd(a,b) * (aにしかない因数)
// b = gcd(a,b) * (bにしかない因数)
// 故に
// a * b = gcd(a,b)^2 * (aにしかない因数) * (bにしかない因数)
// a * b = gcd(a,b) * lcm(a,b)
// lcm(a,b) = a * b / gcd(a,b)

// 包除原理
// 積集合が簡単に求まり、かつ集合の個数が小さい場合に使える。O(2^m*f)もかかるので決して軽くない

// 思考フロー
// 全探索したらO(nm)かかって間に合わない -> 数論の問題であり、一定区間の数全てに対して割れるか調べたい。エラトステネスの篩と構造が同じ
// -> O(nloglogn)かかるので無理 -> 和集合を求める問題だと気づけば、包除原理が思いつく

// ポイント
// 区間に対して倍数条件,約数条件,など割り算に関連する条件を満たす数を列挙したい -> エラトステネスの篩の構造が使えないか検討
// 和集合を求める問題("少なくとも"), 条件が重複する場合 -> 包除原理を検討(積集合が簡単に計算できる必要がある)

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    int n, m; cin >> n >> m;
    vector<int> a(m);
    for (int i = 0; i < m; i++) cin >> a[i];

    ll res = 0;
    for (int i = 1; i < (1 << m); i++) {
        // 項数をカウント: 偶数の時のみ-になる
        int num = 0;
        for (int j = i; j != 0; j >>= 1) {
            if (j & 1) num++;
        }
        ll lcm = 1;
        for (int j = 0; j < m; j++) {
            if (i >> j & 1) {
                // lcm(a,b) = a*b/gcd(a,b)
                lcm = lcm * a[j] / gcd(lcm, a[j]);
                // lcmがnを超えるとその数で割れる個数は0になるのでそれ以上調べる意味がない
                if (lcm > n) break;
            }
        }
        res += num % 2 == 0 ? -n / lcm : n / lcm;
    }

    cout << res << endl;
}
