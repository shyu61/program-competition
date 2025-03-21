#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

int main() {
    int n; cin >> n;

    vector<ll> memo(n + 1, -1);
    auto f = [&](auto f, int x) -> ll {
        if (memo[x] != -1) return memo[x];
        if (x <= 1) return 1;
        return memo[x] = f(f, x - 1) + f(f, x - 2);
    };

    cout << f(f, n) << endl;
}
