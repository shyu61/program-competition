// メビウス関数: p265
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 思考フロー
// 周期性に関する問題 -> すなわち約数を考える問題 -> 約数の約数という重複を除外しつつ数え上げる問題
// -> まさに包除原理だが、約数の累積なのでメビウスの反転公式が使えないか検討する
// -> 素直に立式すればメビウスの反転公式が使える形なので、定石通りメビウス関数値は事前計算しておいて求解する

// ポイント
// - 長さnの周期性がない文字列 -> 周期がnと読み替える
// - 周期の問題は約数と、約数の約数による重複が絡む
// - メビウスの反転公式: 約数に対する累積情報F(n)を、約数に対する分解情報G(n)に変換するもの
//   - 本質は約数に特化した包除原理である。メビウス関数が足すのか引くのか無視するのかを判断する
//   - ある部分集合を求めたい時に、和集合から導くことができる。逆も然り
// - 約数の対称性: d|nとすると、(n/d)|nでありdとn/dは一対一対応する

const int MOD = 10009;

ll mod_pow(ll x, ll n, ll mod) {
    ll res = 1;
    while (n > 0) {
        if (n & 1) res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

// nの約数におけるメビウス関数の値のmapを返す: O(√n)
map<int, int> moebius(int n) {
    map<int, int> res;
    vector<int> primes;

    // nの素因数を列挙する
    // 平方数を含む場合はmu=0なので、後段のΣ計算に含める必要がない。故に素因数分解ではなく素因数の列挙を行う
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            primes.push_back(i);
            while (n % i == 0) n /= i;
        }
    }
    if (n != 1) primes.push_back(n);

    int m = primes.size();
    for (int i = 0; i < (1 << m); i++) {  // 2^m回回るが、nの約数の個数より小さい
        int mu = 1, d = 1;
        for (int j = 0; j < m; j++) {
            if (i >> j & 1) {
                mu *= -1;
                d *= primes[j];  // 素因数を組み合わせて約数を作る
            }
        }
        res[d] = mu;
    }
    return res;
}

int main() {
    int n; cin >> n;
    int res = 0;
    map<int, int> mu = moebius(n);

    // d|nにおいて、f(d): 周期がdの約数である文字列の個数, g(d): 周期がちょうどdである文字列の個数とする
    // 求めたいのは、長さnで周期的でないもの => 周期がちょうどnのもの => g(n)
    // f(n) = Σd|n(g(d)) より、g(n) = Σd|n(μ(d)*f(n/d))
    // 故に(1)nの約数dにおけるメビウス関数の値と、(2)周期がn/dの約数である文字列の個数が分かれば良い
    // (1)はnの素因数から約数を作り、使った素因数の個数の偶奇に応じて-1か1かを定めればよく、
    // (2)は周期がxの文字列の個数は26^xなので26^(n/d)で求まる

    for (auto it = mu.begin(); it != mu.end(); it++) {  // nの約数回回る
        res += it->second * mod_pow(26, n / it->first, MOD);  // μ(d)*26^(n/d)
        res = (res % MOD + MOD) % MOD;
    }
    cout << res << endl;
}
