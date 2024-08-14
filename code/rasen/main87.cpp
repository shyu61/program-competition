// 最長増加部分列(LIS): O(n^2)
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> A;

int solve() {
    vector<int> dp(n, 1);
    int maxl = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (A[i] > A[j]) {
                // iを新たにLISに加えることができる
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        maxl = max(maxl, dp[i]);
    }
    return maxl;
}

int main() {
    cin >> n;
    A = vector<int>(n);
    for (int i = 0; i < n; i++) cin >> A[i];
    cout << solve() << endl;
}