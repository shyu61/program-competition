// 最小値の最大化: p131
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 最小値の最大化、最大値の最小化問題では二分探索が使えることが多い
// 本問題は組合せ最適化の一種で、かつ最大化問題。組合せ最適化問題とくれば、DP,貪欲法,全探索,グラフなどがある
// その中でも最大化が絡む場合は二分探索を利用した全探索を選択肢にあげるとよい。これはいわゆる"閾値の判定問題"として解く方法である。

// 最小値を求める考え方
// 1. 直接最小値を考える方法
// 2. 全てはその値以上でないといけないと考える方法(実際に全てを求めて判定する方法と、この条件を適用しつつ値を求める方法がある)

int n, m;
vector<int> a;

// xが全ての間隔の最小値以上か
bool cond(int x) {
    // まずa[0]に配置し、その後x以上離れた最も近い点に配置し続けたときにk個以上になるか
    int cnt = 1, now = a[0];
    for (int i = 1; i < n && cnt < m; i++) {
        if (a[i] >= now + x) {
            cnt++;
            now = a[i];
        }
    }
    return cnt >= m;
}

int main() {
    cin >> n >> m;
    a = vector<int>(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());

    int left = 0, right = a.back();
    while (left + 1 < right) {
        int mid = (left + right) / 2;
        if (cond(mid)) left = mid;
        else right = mid;
    }

    cout << left << endl;
}
