#include <bits/stdc++.h>
using namespace std;

// ジャンル
// 数列, 最適化問題, 隣接制約, 連続部分列問題(subarray)

// 方針
// subarray問題であり、条件判定に累積性が必要ないので、尺取り法で前から順に見ていく
// subarrayの隣接制約は開始位置の偶奇で場合分けできる

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int maxv = 0;
    for (int k = 0; k < 2; k++) {
        vector<bool> seen(n + 1);
        int cur = k;
        for (int i = k; i + 1 < n; i += 2) {
            if (i > cur) cur = i;
            while (cur + 1 < n && a[cur] == a[cur + 1] && !seen[a[cur]]) {
                seen[a[cur]] = true;
                cur += 2;
            }
            maxv = max(maxv, cur - i);
            seen[a[i]] = seen[a[i + 1]] = false;
        }
    }
    cout << maxv << endl;
}
