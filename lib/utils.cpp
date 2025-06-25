#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using mint = atcoder::modint998244353;

// --- 繰り返し二乗法 ---
// x^n
ll mpow(ll x, ll n, ll mod = 1) {
    // nを二進数で表した時、1の桁のみxの累乗をかけていく
    ll res = 1;
    while (n > 0) {
        if (n & 1) res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

mint mpow(mint x, ll n) {
    mint res = 1;
    while (n > 0) {
        if (n & 1) res *= x;
        x *= x;
        n >>= 1;
    }
    return res;
}

// --- 文字列操作 ---
int main() {
    // char to int
    char c = 'c';
    int ci = c - '0';

    // int to char
    int ci = 10;
    char c = ci + '0';

    // string to int
    string s = "10";
    int si = stoi(s);

    // int to string
    int si = 10;
    string s = to_string(si);
}

// --- next配列 ---
// 1次元配列で次に同じ数が現れるindexを保持する配列
int main() {
    vector<int> a = {1,2,3,2,3,1};
    int n = a.size();
    int VMAX = 3;

    vector<int> nx(n);
    {
        vector<int> pos(VMAX + 1, -1);
        for (int i = n - 1; i >= 0; i--) {
            nx[i] = pos[a[i]];
            pos[a[i]] = i;
        }
    }
}

// 圧縮したnext配列
int main() {
    vector<int> a = {1,2,2000000000,2,2000000000,1};
    int n = a.size();

    CC c;
    rep(i, n) c.add(a[i]);

    vector<int> nx(n);
    {
        vector<int> pos(c.size() + 1, -1);
        for (int i = n - 1; i >= 0; i--) {
            nx[i] = pos[c(a[i])];
            pos[c(a[i])] = i;
        }
    }
}
