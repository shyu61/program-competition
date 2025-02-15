#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// https://youtu.be/8uowVvQ_-Mo?t=6002
// https://youtu.be/Tgd_zLfRZOQ?t=9928
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
