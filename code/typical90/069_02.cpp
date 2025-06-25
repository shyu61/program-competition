#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using mint = atcoder::modint1000000007;

// https://atcoder.jp/contests/abc178/tasks/abc178_c

// 🔷初見でどうやったら解けるか
// 組み合わせ論問題なので、まず「集合」と「条件」を数学的に解釈する。
// 集合は「0<=Ai<=9を満たす長さNの数列」なので10^n通り
// 条件は「少なくとも0と9を1つずつ含む」
// 少なくともなので余事象を考えれば良い

// 🔷抑えるべき抽象論は？
// 組み合わせ論の解き方
// - まず「集合」と「条件」を数学的に解釈する
// - P,C,余事象,包除原理,dp などの手法のどれを使うか検討する

mint mpow(mint x, int n) {
    mint res = 1;
    while (n > 0) {
        if (n & 1) res *= x;
        x *= x;
        n >>= 1;
    }
    return res;
}

int main() {
    int n; cin >> n;
    mint ans = mpow(10, n) - mpow(9, n) - mpow(9, n) + mpow(8, n);
    cout << ans.val() << endl;
}
