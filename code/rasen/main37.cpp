#include <iostream>
using namespace std;

const int MAX = 44;

int dp[MAX];

int main() {
    int n; cin >> n;
    for (int i = 0; i <= n; i++) {
        if (i <= 1) dp[i] = 1;
        else dp[i] = dp[i - 1] + dp[i - 2];
    }
    cout << dp[n] << endl;
}