#include <iostream>
#include <string>
#include <vector>
using namespace std;

string A, B;

vector<vector<int>> dp;



int solve(int i, int j) {
    if (i == 0 || j == 0) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    if (A[i] == B[j]) dp[i][j] = solve(i - 1, j - 1) + 1;
    else dp[i][j] = max(solve(i - 1, j), solve(i, j - 1));
    return dp[i][j];
}

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> A >> B;
        A = ' ' + A;
        B = ' ' + B;
        dp.assign(A.size(), vector<int>(B.size(), -1));
        cout << solve(A.size() - 1, B.size() - 1) << endl;
    }
}
