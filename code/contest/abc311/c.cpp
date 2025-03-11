#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i], a[i]--;

    vector<int> cyc;
    auto solve1 = [&]() -> void {
        vector<int> id(n, -1);
        int s = 0, d = 0;
        while (id[s] == -1) {
            id[s] = d++;
            s = a[s];
        }
        int len = d - id[s];
        rep(i, len) {
            cyc.push_back(s);
            s = a[s];
        }
    };

    auto solve2 = [&]() -> void {
        int s = 0;
        rep(i, n) s = a[s];
        int cur = s;
        do {
            cyc.push_back(cur);
            cur = a[cur];
        } while (cur != s);
    };

    solve1();
    // solve2();

    cout << cyc.size() << endl;
    for (auto v : cyc) cout << v + 1 << ' ';
    cout << endl;
}
