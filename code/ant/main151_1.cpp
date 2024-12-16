// Mine Layer: p343
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 思考フロー
// グリッド問題なので、全探索/貪欲/DP/グラフ/stack 辺りを検討する
// -> 明らかに貪欲的には解けない, グラフの適用は難しそう, 状態遷移の記述が難しい ことから全探索+枝刈りで考えてみる
// -> 左上から順に考えていき、各マスに爆弾があるかないかで分岐していく。この時走査したマスに隣接するマスの数字を満たさない場合は枝刈りする
// -> ナイーブな全探索コストは2^(RC)
// 枝刈りアイディア
// - 最初に真ん中を走査してαβ法を適用し、続けて上下に走査していく

// この方法だといくら枝刈りしてもLargeは間に合わない

vector<int> dx = {1,1,1,0,0,0,-1,-1,-1}, dy = {1,0,-1,1,0,-1,1,0,-1};
int R, C, m, ans = 0;
vector<vector<int>> field;
vector<vector<bool>> bomb;

int calc_score() {
    int res = 0;
    for (int i = 0; i < C; i++) {
        if (bomb[m][i]) res++;
    }
    return res;
}

bool check(int x, int y) {
    // αβ法
    if (y != m && calc_score() <= ans) return false;
    for (int r = 0; r < 9; r++) {
        int nx = x + dx[r], ny = y + dy[y];
        if (nx >= 0 && nx < C && ny >= 0 && ny < R) {
            if (field[ny][ny] <= 0) return false;
        }
    }
    return true;
}

// 爆弾を置いたマスに隣接するマスの数値を更新
void update(int x, int y, bool val) {
    bomb[y][x] = val;
    for (int r = 0; r < 9; r++) {
        int nx = x + dx[r], ny = y + dy[y];
        if (nx >= 0 && nx < C && ny >= 0 && ny < R) {
            if (val) field[ny][nx]--;
            else field[ny][nx]++;
        }
    }
}

bool dfs(int x, int y) {
    // 置けるか判定
    if (!check(x, y)) return false;

    int nx = (x + 1) % C;
    int ny;
    if ((x + 1) / C == 0) ny = y;
    else {
        // mを中心に上下を交互に走査していく
        ny = y > m ? m - (y - m) : m + (m - y + 1);
    }

    if (ny == R) {
        ans = max(ans, calc_score());
        return false;  // 他のパターンも探索する
    }

    // 爆弾を置く場合と置かない場合
    for (int r = 0; r < 2; r++) {
        if (r) update(x, y, true);
        if (dfs(nx, ny)) return true;
        if (r) update(x, y, false);
    }
    return false;
}

int main() {
    cin >> R >> C;
    field = vector<vector<int>>(R, vector<int>(C));
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> field[i][j];
        }
    }

    m = R / 2;
    bomb = vector<vector<bool>>(R, vector<bool>(C));
    dfs(0, m);

    cout << ans << endl;
}
