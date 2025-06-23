#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using TP = tuple<int, int, string>;

int main() {
    int n, q; cin >> n >> q;
    vector<TP> qs(q);
    rep(i, q) {
        int t, p; cin >> t >> p, p--;
        string s = "";
        if (t == 2) cin >> s;
        qs[i] = {t, p, s};
    }

    int tp = -1;
    vector<string> ans;
    for (int i = q - 1; i >= 0; i--) {
        auto& [t, p, s] = qs[i];
        if (tp == -1) {
            if (t == 3) tp = p;
        } else {
            if (tp == p) {
                if (t == 1) tp = -1;
                if (t == 2) ans.push_back(s);
            }
        }
    }

    for (int i = ans.size() - 1; i >= 0; i--) cout << ans[i];
    cout << endl;
}
