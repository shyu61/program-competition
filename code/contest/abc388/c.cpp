#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ジャンル
// 数列, 数え上げ, ペア数え上げ, 並べ替え可能な数列, 単調性条件

// 方針
// 数列の要素数え上げで、単調性条件なので区間アルゴリズムを使って高速に数え上げる方針
// ペア数え上げは一方を固定して数えるのが基本なので、単調性より条件を満たす境界を高速に求められれば良い
// 尺取り法か二分探索で解ける

int main() {
    int N; cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    int cur = 1;
    ll ans = 0;
    for (int i = 0; i < N; i++) {
        while (cur < N && A[i] * 2 > A[cur]) cur++;
        if (cur == N) break;
        ans += N - cur;
    }
    cout << ans << endl;
}
