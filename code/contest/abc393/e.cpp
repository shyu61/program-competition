#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    const int M = 1e6;
    vector<int> cnt(M + 1), m_cnt(M + 1), ans(M + 1);
    rep(i, n) cnt[a[i]]++;

    for (int i = 1; i <= M; i++) {
        for (int j = i; j <= M; j += i) {
            m_cnt[i] += cnt[j];
        }
    }

    for (int i = 1; i <= M; i++) {
        if (m_cnt[i] < k) continue;
        for (int j = i; j <= M; j += i) {
            ans[j] = max(ans[j], i);
        }
    }

    rep(i, n) {
        cout << ans[a[i]] << '\n';
    }
}
