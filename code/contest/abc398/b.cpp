#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int n = 7;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    vector<int> cnt(14);
    rep(i, n) cnt[a[i]]++;

    sort(cnt.rbegin(), cnt.rend());
    if (cnt[0] >= 3 && cnt[1] >= 2) cout << "Yes" << endl;
    else cout << "No" << endl;
}
