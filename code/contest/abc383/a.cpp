#include <bits/stdc++.h>
using namespace std;

// 逐次処理問題

int main() {
    int N; cin >> N;
    vector<int> T(N), V(N);
    int ans = 0, pre = 0;
    for (int i = 0; i < N; i++) {
        int t, v; cin >> t >> v;
        ans = max(ans - (t - pre), 0);
        ans += v;
        pre = t;
    }
    cout << ans << endl;
}
