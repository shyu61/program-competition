// 最大正方形
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int H, W;
vector<vector<int>> tiles;

int solve() {
    vector<vector<int>> dp(H, vector<int>(W, 0));
    int maxv = 0;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (tiles[i][j] == 1) dp[i][j] = 0;
            else if (i == 0 || j == 0) dp[i][j] = 1;
            else {
                dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
            }
            maxv = max(maxv, dp[i][j]);
        }
    }
    return maxv * maxv;
}

int main() {
    cin >> H >> W;
    tiles = vector<vector<int>>(H, vector<int>(W));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cin >> tiles[i][j];
        }
    }
    cout << solve() << endl;
}
