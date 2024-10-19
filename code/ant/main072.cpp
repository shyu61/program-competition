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

int n;
vector<int> a;

int lower(int x) {
    int left = -1; // 0が条件を満みたす場合もあるので-1
    int right = n; // n-1が条件を満たさない場合もあるのでn
    while (right - left > 1) {
        int mid = (left + right) / 2;
        if (x <= a[mid]) right = mid;
        else left = mid;
    }
    return right;
}

int upper(int x) {
    int left = -1, right = n;
    while (right - left > 1) {
        int mid = (left + right) / 2;
        if (x < a[mid]) right = mid;
        else left = mid;
    }
    return right;
}

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int k; cin >> k;

    cout << lower(k) << endl;
}
