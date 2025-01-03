#include <bits/stdc++.h>
using namespace std;

// グリッド問題の全探索
// - 組み合わせ型全探索
//   - あるマスへの操作が他のマスへの操作に影響を与えないケース
// - 構造型全探索
//   - マスに対する操作に依存関係があるケース
// 今回の問題はどこのマスに加湿器が置かれようと他のマスに対して加湿器を置くかどうかの制約に影響を与えないので組み合わせ型全探索で十分

int main() {
    int H, W, D; cin >> H >> W >> D;
    vector<string> grid(H);
    for (int i = 0; i < H; i++) cin >> grid[i];

    // 全探索
    int ans = 0;
    for (int i = 0; i < H * W; i++) {
        for (int j = i + 1; j < H * W; j++) {
            int x1 = i / W, y1 = i % W;
            int x2 = j / W, y2 = j % W;
            if (grid[x1][y1] == '.' && grid[x2][y2] == '.') {
                // スコア計算
                int res = 0;
                for (int x = 0; x < H; x++) {
                    for (int y = 0; y < W; y++) {
                        if (grid[x][y] == '#') continue;
                        if (abs(x1 - x) + abs(y1 - y) <= D || (abs(x2 - x) + abs(y2 - y)) <= D) res++;
                    }
                }
                ans = max(ans, res);
            }
        }
    }
    cout << ans << endl;
}
