// 対称性のある数え上げ: p268
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ポリアの数え上げ定理: 対称性のある数え上げに利用する。グリッド(タイル),円,多面体,グラフ,分子など
// 逐一重複を考慮せずとも対称性という性質を利用して数式で機械的に処理ができる。メビウス関数が包除原理を約数の世界限定で数式で処理することと似ている
// 適用順序
// 1. 変換操作の集合を定義
// 2. 不変点を考える(操作により同一視できる形状や塗り分けパターン)
//   ある程度パターンがあることを理解しておく。周期性,回転対称性,線対称性,平移対称性,スケール対称性など
// 3. 各操作における不変点の個数を計算する
// 4. N = 1/|G|Σg∈G(k^c(g))を計算, G:操作群,g:操作,k:色数,c(g):操作gでの不変点数

// 思考フロー
// 明らかに対称性のある数え上げの問題 -> ポリアの定理を適用できるよう情報を整理する -> (1)変換操作集合はk個分回転させるn通り, (2)不変は回転周期ごとに同じ配色にする
// ポリアの定理における操作gは、周期kに該当するので、周期k(操作g)における不変点数が分かれば良いことになる。周期kごとに同配色にするので、不変点数=軌道数になる
// -> 軌道数は直接数えにくいので、n/軌道数の要素数で求める -> 端切れを許容する周期数はn/gcd(k,n) (cf. 端切れを許容しない文字列の周期などはd|nについてn/d) -> 故に軌道数=gcd(k,n)
// -> ポリアの定理より、求める解は「1/nΣk(m^gcd(k,n)): kは1<=k<n」
// -> 愚直なΣ計算は間に合わない。約数は離散的でスパースなので、まとめて計算できることが多い。また数え上げのアルゴリズムが複数あることも大きい(オイラー関数,メビウス関数など)
// -> 欲しいのは、d=gcd(k,n)とすると、dの値とその個数。gcd(k,n)はk<nよりすなわちnの約数を走査することとイコール -> 「1/nΣd|n(m^d * gcd(k,n)=dとなるkの個数)」と変換できる
// -> あとはgcd(k,n)=dとなるkの個数が分かればいい。この形はオイラー関数で数え上げる典型的な形をしている。kの個数は、d*gcd(n/d,t)=1のtの個数と一致し、φ(n/d)と一致する
// -> 1/nΣd|n(m^d * φ(n/d)) = 1/nΣd|n(m^n/d * φ(d))

// ポイント
// - 約数の対称性: d|nとすると、(n/d)|nでありdとn/dは一対一対応する
// - 周期は端切れを許容するのか否かに注意する
// - ポリアの数え上げ定理は順序を追って考える。不変点のパターンはある程度覚えておく
// - 互いに素な形をしているもの以外にも、gcd(k,n)=dのkの数え上げはオイラー関数が使える。
// - ループ内の約数演算はスパースなので塊で考えることができる
// - 数論は数式を書く

const int MOD = 1000000007;

// 素因数を列挙: O(√n)
vector<int> get_primes(int n) {
    vector<int> res;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            res.push_back(i);
            while (n % i == 0) n /= i;
        }
    }
    if (n != 1) res.push_back(n);
    return res;
}

// 約数列挙: O(√n)
vector<int> divisor(int n) {
    vector<int> res;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            res.push_back(i);
            if (i != n / i) res.push_back(n / i);
        }
    }
    return res;
}

ll mod_pow(ll x, ll n, ll mod) {
    ll res = 1;
    while (n > 0) {
        if (n & 1) res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

int main() {
    int n, m; cin >> n >> m;

    vector<int> primes = get_primes(n);
    vector<int> divs = divisor(n);
    ll res = 0;

    // Σd|nについて計算
    for (int i = 0; i < divs.size(); i++) {
        // φ(d)を求める
        ll euler = divs[i];
        // 本来はdの素因数をループするが、dの約数はnの約数であることからnの約数を流用する
        for (auto p : primes) {
            if (divs[i] % p == 0) euler = euler / p * (p - 1);
        }

        res += euler * mod_pow(m, n / divs[i], MOD) % MOD;
        res %= MOD;
    }

    // 1/nをかける: modなので逆元操作を行う
    cout << res * mod_pow(n , MOD - 2, MOD) % MOD << endl;
}
