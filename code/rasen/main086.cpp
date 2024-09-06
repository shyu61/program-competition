// ナップサック問題: i=1から格納する場合
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Item { int v, w; };

int N, W;
vector<Item> items;

int solve() {
    vector<vector<int>> dp(N + 1, vector<int>(W + 1, 0));
    for (int i = 1; i <= N; i++) {
        for (int w = 1; w <= W; w++) {
            if (w - items[i].w < 0) {
                dp[i][w] = dp[i - 1][w];
                continue;
            }
            dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - items[i].w] + items[i].v);
        }
    }
    return dp[N][W];
}

int main() {
    cin >> N >> W;
    items = vector<Item>(N + 1); items[0].w = items[0].v = 0;
    for (int i = 1; i <= N; i++) {
        cin >> items[i].v >> items[i].w;
    }
    cout << solve() << endl;
}
