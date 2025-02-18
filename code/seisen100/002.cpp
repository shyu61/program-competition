#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int divisor(int n) {
    vector<int> res;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            res.push_back(i);
            if (i != n / i) res.push_back(n / i);
        }
    }
    return res.size();
}

int main() {
    int n; cin >> n;
    int ans = 0;
    for (int i = 1; i <= n; i += 2) {
        if (divisor(i) == 6) ans++;
    }
    cout << ans << endl;
}
