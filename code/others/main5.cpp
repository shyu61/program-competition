// 区間和
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0516
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int AMAX = 1e4;
const int NMAX = 1e5;
const int INF = AMAX * NMAX + 1;

int main() {
    int n, k;
    while (cin >> n >> k) {
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        // 累積和: O(n)
        vector<int> s(n + 1, 0);
        for (int i = 0; i < n; i++) s[i + 1] = s[i] + a[i];

        int maxv = -INF;
        for (int i = 0; i + k < n; i++) {
            maxv = max(maxv, s[i + k] - s[i]);
        }

        cout << maxv << endl;
    }
}
