// ビットDP(ドミノ敷き詰め): p177
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// https://hcpc-hokudai.github.io/archive/dynamic_programming_002.pdf
// 組合せ最適化の問題。グラフアルゴリズムなどで一足飛びに解けなさそうであれば、まず全探索で考えてみてメモ化による高速化を検討するのがセオリー。
// 全探索のメモ化を考える時は、再利用される部分を考える。再利用とはいわゆる繰り返し単位で、全探索ループの中で繰り返し構造がある時、そこをメモ化することで高速化できる
// 本問題では「未配置のマスの状態が同じであれば、その地点までのマスの埋め方によらず残りは同じ計算結果になる」というのがコア
// つまり現地点と、残りの未埋めマスの形状をdpテーブルに持つメモ化する。
// また、未埋めマスは全て管理する必要はなく、現地点までのブロックの置き方によって変わる部分だけ持てば良い、つまりすでに埋めたブロックに隣接するブロックエリアだけ持てば良い。

// ポイント
// グリッド問題の敷き詰め問題はbitDPでマスの状態を管理することで解けるケースが多い。どのマスまで状態管理する必要があるかに注意しよう
// 全探索において、ある地点における残りの形状が同じなら、これまでのルートに非依存的にルート(組合せ)が決まるケースは結構ある。
//   反転問題も同様に考えることができるし、グリッドに限らず1次元配列でも言えるし、グラフでもありそう。全探索の場合では本当に累乗の場合の数を考える必要があるか一度考える癖をつける

int n, m, cnt = 0;
vector<vector<bool>> tile;
vector<vector<vector<int>>> dp;

int dfs(int x, int y, int S) {
    if (x == m) return dfs(0, y + 1, S);
    if (y == n) return 1;

    // 同じ地点から見て、残りの未埋めマスの形状が同じならキャッシュを返す
    if (dp[x][y][S] != -1) return dp[x][y][S];

    if (tile[y][x] | (S >> x & 1)) {
        // 一つ右に進むとき、現列の管理対象は一つ下にずれる。また縦置きしてないので下は必ず空きになる
        return dp[x][y][S] = dfs(x + 1, y, S & ~(1 << x));
    }

    // 横に置く
    int res = 0;
    if (x + 1 < m && !tile[y][x + 1] && !(S >> (x + 1) & 1)) {
        // 横に置くと現列の一つの下の行は空きになる, x+1の下は縦置きされないので空きのままで良い
        res += dfs(x + 2, y, S & ~(1 << x));
    }
    // 縦に置く
    if (y + 1 < n && !tile[y + 1][x]) {
        // 縦に置くと現列の一つ下の行は埋まる
        res += dfs(x + 1, y, S | (1 << x));
    }

    return dp[x][y][S] = res;
}

int main() {
    cin >> n >> m;
    tile = vector<vector<bool>>(n, vector<bool>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c; cin >> c;
            if (c == 'x') tile[i][j] = true;
        }
    }

    dp = vector<vector<vector<int>>>(m, vector<vector<int>>(n, vector<int>(1 << m, -1)));
    dfs(0, 0, 0);
    cout << dp[0][0][0] << endl;
}
