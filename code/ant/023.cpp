// 尺取り法: p137
#include <bits/stdc++.h>
using namespace std;

// 区間における最小個数を求める問題
// 個数は単調性が成立するので、尺取り法が使える

int main() {
    int n; cin >> n;
    vector<int> a(n);
    map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }

    int m = cnt.size();

    int ans = n + 1;
    map<int, int> cur;
    int right = 0, nuniq = 0;
    for (int left = 0; left < n; left++) {
        while (nuniq < m && right < n) {
            cur[a[right]]++;
            if (cur[a[right]] == 1) nuniq++;
            right++;
        }

        if (nuniq < m) break;
        ans = min(ans, right - left);

        cur[a[left]]--;
        if (cur[a[left]] == 0) nuniq--;
    }

    cout << ans << endl;
}
