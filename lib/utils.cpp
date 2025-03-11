#include <bits/stdc++.h>
using namespace std;
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
