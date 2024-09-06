// ナップサック問題: i=0を別で考える場合
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Item { int v, w; };

int N, W;
vector<Item> items;

int solve() {
    // 各重さでの価値の最大値を格納する
    vector<vector<int>> dp(N, vector<int>(W + 1, 0));
    for (int w = items[0].w; w <= W; w++) dp[0][w] = items[0].v;
    for (int i = 1; i < N; i++) {
        for (int w = 1; w <= W; w++) {
            if (w - items[i].w < 0) {
                dp[i][w] = dp[i - 1][w];
                continue;
            }
            dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - items[i].w] + items[i].v);
        }
    }
    return dp[N - 1][W];
}

int main() {
    cin >> N >> W;
    items = vector<Item>(N);
    for (int i = 0; i < N; i++) {
        cin >> items[i].v >> items[i].w;
    }
    cout << solve() << endl;
}
