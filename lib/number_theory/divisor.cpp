#include <bits/stdc++.h>
using namespace std;

// O(logmax(a,b))
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int extgcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int d = extgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}
