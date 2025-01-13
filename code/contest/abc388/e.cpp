#include <bits/stdc++.h>
using namespace std;

// ジャンル
// 数列, 数え上げ, ペアリング問題, 組み合わせ最適化, マッチング

// 方針
// 組合せ最適化問題なので、全探索,貪欲,dp,グラフ,判定問題を検討していく
// 判定が簡単にできることがわかるので、二分探索+貪欲判定で解くだけ

int N;
vector<int> A;

bool check(int k) {
    bool ok = true;
    for (int i = 0; i < k; i++) {
        if (A[i] * 2 > A[N - k + i]) {
            ok = false;
            break;
        }
    }
    return ok;
}

int main() {
    cin >> N;
    A = vector<int>(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    int lb = 0, ub = N / 2 + 1;
    while (ub - lb > 1) {
        int m = (lb + ub) / 2;
        check(m) ? lb = m : ub = m;
    }

    cout << lb << endl;
}

// int main() {
//     int N; cin >> N;
//     vector<int> A(N);
//     for (int i = 0; i < N; i++) cin >> A[i];

//     int cur = N / 2, ans = 0;
//     for (int i = 0; i < N / 2; i++) {
//         while (cur < N && A[i] * 2 > A[cur]) cur++;
//         if (cur == N) break;
//         ans++;
//         cur++;
//     }
//     cout << ans << endl;
// }
