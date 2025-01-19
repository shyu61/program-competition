#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll x; cin >> x;
    int i = 1;
    while (x > 1) {
        x /= i;
        i++;
    }
    cout << i - 1 << endl;
}
