#include <bits/stdc++.h>
#include <lib/cc.cpp>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 繰り返し二乗法
ll pow(ll x, ll n, ll mod = 1) {
    // nを二進数で表した時、1の桁のみxの累乗をかけていく
    ll res = 1;
    while (n > 0) {
        if (n & 1) res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

int main() {
    {
        // char_to_int
        char c;
        int(c - '0');
    
        // int_to_string
        int i;
        to_string(i);
    
        // string_to_int
        string s;
        stoi(s);
    }
}

// next配列
int main() {
    int n;
    vector<int> a(n);
    int VMAX;

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
    int n;
    vector<int> a(n);

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
