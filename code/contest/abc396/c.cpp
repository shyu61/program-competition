#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 想定解
// 貪欲法

// ポイント
// 理論を直接実装するのではなく、やや冗長でもより簡略な形で書けるならそうすべき

int main() {
    int n, m; cin >> n >> m;
    vector<int> b(n), w(m);
    rep(i, n) cin >> b[i];
    rep(i, m) cin >> w[i];

    sort(b.rbegin(), b.rend());
    sort(w.rbegin(), w.rend());

    ll ans = 0;
    rep(i, n) {
        int wi = i < m ? w[i] : 0;
        ans = max({ans, ans + b[i], ans + b[i] + wi});
    }

    cout << ans << endl;
}
