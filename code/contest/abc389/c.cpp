#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ポイント
// 累積和は開区間
//   - s[i+1]: 第i項までの和(i番目ではないことに注意)

int main() {
    int q; cin >> q;

    int cur = 0;
    vector<ll> s; s.push_back(0);
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int l; cin >> l;
            s.push_back(s.back() + l);
        } else if (t == 2) {
            cur++;
        } else {
            int k; cin >> k; k--;
            cout << s[cur + k] - s[cur] << '\n';
        }
    }
}
