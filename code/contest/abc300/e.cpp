#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using mint = atcoder::modint998244353;

// ジャンル
// 確率問題, 確率dp, 数論, 約数

// 方針
// 逆順に考えた方が良い逐次問題のタイプ
// また、前に何を選んだかによって次選べるものの選択肢が変わるので状態依存である
// 故にdpで考える。自己ループは除去しつつ遷移させるだけで良い

// ポイント
// 確率や期待値問題は逐次的な遷移を伴う問題が多く、逆方向から考えるという選択肢は常に持つべき
// 状態が遷移しない操作が存在するなら、式変形による自己遷移除去が必要になる

int main() {
    ll n; cin >> n;

    unordered_map<ll, mint> mem;
    auto rec = [&](auto rec, ll n) -> mint {
        if (n == 1) return 1;
        if (mem.contains(n)) return mem[n];
        mint res = 0;
        for (int i = 2; i <= 6; i++) {
            if (n % i == 0) res += rec(rec, n / i);
        }
        return mem[n] = res / 5;
    };

    mint ans = rec(rec, n);
    cout << ans.val() << endl;
}
