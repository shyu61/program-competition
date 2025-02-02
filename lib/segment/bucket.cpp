#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // バケットの作成
    int n2 = sqrt(n);
    int bk_size = n / n2 + 1;
    vector<vector<int>> bk(bk_size);
    for (int i = 0; i < n; i++) {
        bk[i / n2].push_back(a[i]);
        if ((i + 1) % n2 == 0) {
            // FIXME
            sort(bk[i / n2].begin(), bk[i / n2].end());
        }
    }
    sort(bk[bk_size - 1].begin(), bk[bk_size - 1].end());

    // 区間が与えられた時にバケットを走査する
    int l, r; cin >> l >> r;

    // 境界バケットを処理
    while (l < r && l % n2 != 0) {
        // もはや元の配列を見れば十分
        a[l++];  // 処理を追加
    }
    while (l < r && l % n2 != 0) {
        a[--r];  // 処理を追加
    }

    // 完全に含まれるバケットを処理
    while (l < r) {
        int i = l / n2;
        // bk[i] に対して処理
        l += n2;
    }
}
