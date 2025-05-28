#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using mint = atcoder::modint1000000007;

int main() {
    int n; cin >> n;
    mint ans = 1;
    rep(i, n) {
        mint sum = 0;
        rep(j, 6) {
            int a; cin >> a;
            sum += a;
        }
        ans *= sum;
    }
    cout << ans.val() << endl;
}
