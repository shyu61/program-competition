#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

struct Matrix {
    int row, col;
};

int n;

int solve(vector<Matrix> M) {
    vector<vector<int> > dp(n, vector<int>(n, 0));
    for (int l = 2; l <= n; l++) {
        for (int i = 0; i <= n - l; i++) {
            int j = i + l - 1;
            dp[i][j] = numeric_limits<int>::max();
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k + 1][j] + M[i].row * M[k].col * M[j].col;
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }
    return dp[0][n - 1];
}

int main() {
    cin >> n;
    vector<Matrix> M(n, Matrix());
    for (int i = 0; i < n; i++) {
        cin >> M[i].row >> M[i].col;
    }
    cout << solve(M) << endl;
}