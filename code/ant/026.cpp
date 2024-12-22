// 貪欲法: Fence Repair: p49
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 別解
int main() {
    int n; cin >> n;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < n; i++) {
        int l; cin >> l;
        pq.push(l);
    }

    ll ans = 0;
    while (pq.size() > 1) {
        int min1 = pq.top(); pq.pop();
        int min2 = pq.top(); pq.pop();

        int t = min1 + min2;
        ans += t;
        pq.push(t);
    }

    cout << ans << endl;
}

// int main() {
//     int n; cin >> n;
//     vector<int> a(n);
//     for (int i = 0; i < n; i++) cin >> a[i];

//     int l = n;
//     ll ans = 0;
//     // ハフマン木を構築する
//     while (l > 1) {
//         // 1,2番目に短い板を探索
//         int min1 = 0, min2 = 1;
//         if (a[min2] < a[min1]) swap(min1, min2);
//         for (int i = 2; i < l; i++) {
//             if (a[i] <= a[min1]) {
//                 min2 = min1;
//                 min1 = i;
//             } else if (a[i] < a[min2]) min2 = i;
//         }

//         // min1,min2をmerge
//         // min1にmergeされるので次ループで範囲外になったら困るのでmin2とswapする
//         // min2はどこ道対象外にするのでl-1番目でも問題ない
//         if (min1 == l - 1) swap(min1, min2);
//         int t = a[min1] + a[min2];
//         ans += t;
//         a[min1] = t;
//         // l-1は次ループで対象外になる
//         swap(a[min2], a[l - 1]);
//         l--;
//     }

//     cout << ans << endl;
// }
