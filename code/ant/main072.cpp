// ソート列から値を探す: p128
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ソート済み配列の探索はもちろんだが、配列の値をf(x)に通した結果を評価するとき、この結果に単調性がある場合は同じく二分探索が使える
// キーワードは単調性配列に対する探索

// int main() {
//     int n; cin >> n;
//     vector<int> a(n);
//     for (int i = 0; i < n; i++) cin >> a[i];
//     int k; cin >> k;

//     cout << lower_bound(a.begin(), a.end(), k) - a.begin() << endl;
// }

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int k; cin >> k;

    int left = 0, right = n, mid;
    while (left < right) {
        mid = (left + right) / 2;
        if (k <= a[mid]) right = mid;
        else left = mid + 1;
    }
    cout << left << endl;
}
