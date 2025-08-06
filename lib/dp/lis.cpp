#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int n, INF;
    vector<int> a(n);

    // O(NlogN)
    // 同じ長さのLISなら最終要素が小さい方が有利
    // dp[i]:=長さがi+1のLISの最終要素の最小値(INFの場合はその長さのLISは存在しない)
    vector<int> dp(n, INF);
    rep(i, n) {
        *lower_bound(dp.begin(), dp.end(), a[i]) = a[i];
    }
    // dp[i]<INFとなる最大のiに対してi+1が解
    int lis = lower_bound(dp.begin(), dp.end(), INF) - dp.begin();
}
