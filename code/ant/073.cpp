// 解を仮定し可能か判定: p129
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 逐次問題でもないので一撃で求めることは難しそう -> 全探索していく
// -> 十分大きい長さから始めて可能な長さを探索する
// -> 可能かどうかの判定はO(n)でできる、かつ探索範囲は二分探索で絞れば良いのでO(nlog(li))でできる

// 最大最小問題で、条件判定が低コストでできるなら二分探索での全探索も選択肢に入る

int main() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    int maxv = 0;
    for (int i = 0; i < n; i++) {
        double l; cin >> l;
        a[i] = l * 100;
        maxv = max(maxv, a[i]);
    }

    // [left, right)
    int left = 1, right = maxv + 1;
    while (left + 1 < right) {
        int mid = (left + right) / 2;
        // 長さmidの紐をk本作れるか判定
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            cnt += a[i] / mid;
        }

        // lower_boundの場合はmid+1してはいけない
        if (cnt >= k) left = mid;
        else right = mid;
    }

    cout << fixed << setprecision(2) << double(left) / 100.0 << endl;
}
