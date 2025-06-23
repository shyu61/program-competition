#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int n; cin >> n;
    vector<int> d(n - 1);
    rep(i, n - 1) cin >> d[i];

    rep(i, n) {
        int ans = 0;
        for (int j = i + 1; j < n; j++) {
            ans += d[j - 1];
            cout << ans << ' ';
        }
        cout << endl;
    }
}
