#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using mint = atcoder::modint998244353;

// 🔷初見でどうやったら解けるか
// 制約的にもどれか1つのパラメータを固定することを前提に考える
// 最も固定すべきなのは自由度が高いパラメータなのでbかcを固定する
// するとBをi個,Cをc個,Dをd個並べる問題になる。愚直に考えればさらにcかdを全探索する必要がありそうだが間に合わない。
// 同じものを含む順列における異種間制約を考えてみると、BとDは全順序制約になっているので区別をなくすことでその制約を表現できることがわかる。

// 🔷抑えるべき抽象論は？
// 同じものを含む順列
// - n!/(p!q!r!) = (n,p) * (n-p,q) * (n-p-q,r)
//   - n個の位置から要素1を置く場所をp個選ぶ, ...
// - 異なるものが2種類の場合は一方の組み合わせ数と一致する: (n,p)
// 異種間制約では以下が重要
// - 隣接制約: 固定/圧縮が有効
// - 順序制約: 区別をなくす

struct ModInv {
    int n; vector<mint> d;
    ModInv() : n(2), d({0, 1}) {}
    mint operator()(int i) {
        while (n <= i) {
            d.push_back(-d[mint::mod() % n] * (mint::mod() / n)), ++n;
        }
        return d[i];
    }
    mint operator[](int i) const { return d[i]; }
} invs;

struct ModFact {
    int n; vector<mint> d;
    ModFact() : n(2), d({1, 1}) {}
    mint operator()(int i) {
        while (n <= i) d.push_back(d.back() * n), ++n;
        return d[i];
    }
    mint operator[](int i) const { return d[i]; }
} facts;

struct ModFactInv {
    int n; vector<mint> d;
    ModFactInv() : n(2), d({1, 1}) {}
    mint operator()(int i) {
        while (n <= i) d.push_back(d.back() * invs(n)), ++n;
        return d[i];
    }
    mint operator[](int i) const { return d[i]; }
} ifacts;

mint comb(int n, int k) {
    if (n < k || k < 0) return 0;
    return facts(n) * ifacts(k) * ifacts(n - k);
}

int main() {
    int a, b, c, d; cin >> a >> b >> c >> d;
    mint ans = 0;
    rep(i, b + 1) {
        ans += comb(a + i, a) * comb(b - i + c + d, c);
    }
    cout << ans.val() << endl;
}
