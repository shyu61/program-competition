// 半分全列挙(A Values whose Sum is 0)
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n; cin >> n;
    vector<int> A(n), B(n), C(n), D(n);
    for (int i = 0; i < n; i++) cin >> A[i];
    for (int i = 0; i < n; i++) cin >> B[i];
    for (int i = 0; i < n; i++) cin >> C[i];
    for (int i = 0; i < n; i++) cin >> D[i];

    // C+Dを全列挙: O(n^2)
    vector<int> CD(n * n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            CD[i * n + j] = C[i] + D[j];
        }
    }
    sort(CD.begin(), CD.end());

    // A, Bを全列挙
    int sum = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum = A[i] + B[j];

            // CDから合計が0になる位置を二分探索
            ans += upper_bound(CD.begin(), CD.end(), -sum) - lower_bound(CD.begin(), CD.end(), -sum);
        }
    }

    cout << ans << endl;
}
