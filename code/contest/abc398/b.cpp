#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int n = 7;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    vector<int> cnt(14);
    rep(i, n) cnt[a[i]]++;

    int sum1 = 0, sum2 = 0;
    rep(i, 14) {
        if (cnt[i] >= 2) sum1++;
        if (cnt[i] >= 3) sum2++;
    }
    if (sum1 >= 2 && sum2 >= 1) cout << "Yes" << endl;
    else cout << "No" << endl;
}
