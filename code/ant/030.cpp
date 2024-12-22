// 三角形: p21
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 全探索の問題

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int maxv = 0;
    // 全ての組み合わせを試す
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                int hypo = max(a[i], max(a[j], a[k]));
                int sum = a[i] + a[j] + a[k];
                // 三角不等式により三角形が作れるかチェック
                if (sum - hypo <= hypo) continue;
                maxv = max(maxv, sum);
            }
        }
    }

    cout << maxv << endl;
}
