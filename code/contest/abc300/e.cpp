#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using mint = atcoder::modint998244353;

// ジャンル
// 確率問題, 確率dp

// 方針
// 確率問題だが場合の数を数え上げる問題
// 出目の順序は関係ないので、1~6の数字それぞれを何回まで出せるかを高速に数えられれば良さそう
// N<=10^18より逐次的に見ていくのは不可能

// 確率問題のうち、発生確率が状態に依存するケースの問題。例えば現在の値がnの直前だった場合、1~6全ての値を取れるわけではなくなる。
// これは各状態に応じて取りうる場合の数が異なるということなので、dpで考えると良さそう
// 出目の順序は関係なく、組み合わせで決まる

int main() {
    ll n; cin >> n;
}
