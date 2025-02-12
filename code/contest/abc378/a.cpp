#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    vector<int> a(4);
    rep(i, 4) cin >> a[i];
    sort(a.begin(), a.end());

    int ans = 0, cur = 0;
    while (cur + 1 < 4) {
        if (a[cur] == a[cur + 1]) {
            ans++;
            cur += 2;
        } else cur++;
    }

    cout << ans << endl;
}
