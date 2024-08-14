#include <iostream>
#include <string>
using namespace std;

int lcs(string A, string B) {
    A = ' ' + A;
    B = ' ' + B;

    int asize = A.size(); int bsize = B.size();
    int dp[asize][bsize];
    for (int i = 0; i < asize; i++) dp[i][0] = 0;
    for (int i = 0; i < bsize; i++) dp[0][i] = 0;

    for (int i = 1; i < asize; i++) {
        for (int j = 1; j < bsize; j++) {
            if (A[i] == B[j]) dp[i][j] = dp[i - 1][j - 1] + 1;
            else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    return dp[asize - 1][bsize - 1];
}

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        string A, B;
        cin >> A >> B;
        cout << lcs(A, B) << endl;
    }
}
