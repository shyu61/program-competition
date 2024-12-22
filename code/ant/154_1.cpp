// Endless Knight: p353
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 全探索する方法: O(H+W/3 ^2)

const int MOD = 10007;
int H, W, R, ans = 0;
vector<int> h, w;  // 石の位置
vector<int> dh = {1,2}, dw = {2,1};
vector<vector<bool>> used;

// (hi,wi)に石があるか判定
bool check(int hi, int wi) {
    bool ok = true;
    for (int i = 0; i < R; i++) {  // R<=10なのでO(1)
        if (h[i] == hi && w[i] == wi) {
            ok = false;
            break;
        }
    }
    return ok;
}

void dfs(int hi, int wi) {
    if (hi == H - 1 && wi == W - 1) {
        ans++;
        ans %= MOD;
        return;
    }

    for (int r = 0; r < 2; r++) {
        int nh = hi + dh[r], nw = wi + dw[r];
        if (nh >= 0 && nh < H && nw >= 0 && nw < W && !used[nh][nw] && check(nh, nw)) {
            used[nh][nw] = true;
            dfs(nh, nw);
            used[nh][nw] = false;
        }
    }
}

int main() {
    cin >> H >> W >> R;
    h = w = vector<int>(R);
    for (int i = 0; i < R; i++) {
        cin >> h[i] >> w[i];
        h[i]--; w[i]--;
    }

    // 全探索
    used = vector<vector<bool>>(H, vector<bool>(W));
    used[0][0] = true;
    dfs(0, 0);
    cout << ans % MOD << endl;
}
