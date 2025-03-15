#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
const int INF = 1001001001;

// 貪欲法
int main() {
    int n; cin >> n;
    vector<int> a(n), b(n - 1);
    rep(i, n) cin >> a[i];
    rep(i, n - 1) cin >> b[i];

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int i = n - 1;
    while (i > 0 && a[i] <= b[i - 1]) i--;
    int x = a[i];

    rep(j, i) {
        if (a[j] > b[j]) x = -1;
    }

    cout << x << endl;
}

// 二分探索
int main() {
    int n; cin >> n;
    vector<int> a(n), b(n - 1);
    rep(i, n) cin >> a[i];
    rep(i, n - 1) cin >> b[i];

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    auto check = [&](int mid) -> bool {
        vector<int> c = b;
        c.push_back(mid);
        sort(c.begin(), c.end());
        rep(i, n) {
            if (a[i] > c[i]) return false;
        }
        return true;
    };

    int ok = INF, ng = 0;
    while (abs(ok - ng) > 1) {
        int mid = (ok + ng) / 2;
        check(mid) ? ok = mid : ng = mid;
    }
    if (ok == INF) ok = -1;
    cout << ok << endl;
}
