// Football Team: p350
#include <bits/stdc++.h>
using namespace std;

// 思考フロー
// 明らかにグラフの彩色問題 -> 彩色問題はNP困難なので何らかの特殊な構造を持つグラフである可能性が非常に高い
// -> 真っ先に疑うべきは平面グラフかどうか。頂点の位置関係により判断できる(交差しないかどうか)。x1<x3<x2となるxが存在しないので明らかにedgeは交差しない
// -> 高々4色であることがわかった。1,2色は高速に解けるので、本問題は実質3色彩色問題に帰着
// -> 3色問題が高速に解ける状況はある程度前提知識がないと難しい -> 局所的制約が使えるケースが多く、いくつか試すとグラフが作る面は必ず三角形になることがわかる
// -> (1)辺を共有する場合, (2)点を共有する場合, (3)共有しない(非連結)場合を考える -> (1)は最初の2頂点を塗ると後は一意に決まる, (2)(3)は辺を共有する部分グラフのみ考慮すれば十分

// 彩色問題
// - k=2 二部グラフ
// - k=3 NP困難
//   - グラフが小さい場合は工夫しつつ力技で解ける場合がある
//     - 1色を全探索して二部グラフを考える(1色の決定方法は、近似した最大独立集合を考えるとよい)
//     - 全探索+枝刈り
//   - 問題固有の構造を使って効率的に探索できるケースもある。多くは局所的な制約に着目すると良い
//     - 隣接関係や三角形(辺を共有する三角形のみで作られるグラフなど)
// - k=4 NP困難, 平面グラフは必ずk<=4(四色定理)

// ポイント
// - 全要素をなめる必要がある場合に、候補を逐次的に更新することでO(N^2)をO(N)にできることは多い
// - 彩色問題の特徴は押さえておく

int N;
vector<int> x, y;
vector<vector<bool>> G, used;  // G: 隣接行列
vector<int> color;

// 3彩色可能か判定
// 2点v,uの色が確定している状態で、v-uの辺を共有する三角形の色を再帰的に調べる
// 2点の色が確定していれば他全ての頂点が一意に定まる。例えば、5角形以上の奇数角形の場合は4色必要になる
bool rec(int v, int u) {
    used[v][u] = used[u][v] = true;
    int c = 3 - color[v] - color[u];  // 残りの色
    for (int w = 0; w < N; w++) {
        // v,u,wを頂点とする三角形
        if (G[v][w] && G[u][w]) {
            if (color[w] < 0) {
                color[w] = c;
                used[v][w] = used[u][w] = true;
                // 残りの2つの三角形について調べる
                if (!rec(v, w) || !rec(u, w)) return false;
            } else if (color[w] != c) {
                // 4色目で塗られている
                return false;
            }
        }
    }
    return true;
}

int main() {
    cin >> N;
    x = y = vector<int>(N);
    for (int i = 0; i < N; i++) cin >> x[i] >> y[i];

    // グラフの作成
    // "近い"頂点同士にedgeを張る
    G = vector<vector<bool>>(N, vector<bool>(N));
    for (int i = 0; i < N; i++) {
        // 点iに対して点jが近いかは、yについては絶対的に判定できるのに対して、
        // xはその他の点も考慮しないと判定できない。=> 都度O(N)探索は非効率なので、候補を保持して更新していくという考え方をする必要がある
        vector<int> v = {-1,-1,-1};
        for (int j = 0; j < N; j++) {
            if (i == j) continue;
            int k = y[i] - y[j] + 1;  // y座標は3通りしかない
            // "近い" := abs(y1-y2)<=1 && x1<x3<x2, (x3,y2)となる点がない
            if (k >= 0 && k <= 2 && x[i] < x[j] && (v[k] < 0 || x[j] < x[v[k]])) {
                v[k] = j;
            }
        }
        for (int r = 0; r < 3; r++) {
            if (v[r] >= 0) {
                G[i][v[r]] = G[v[r]][i] = true;
            }
        }
    }

    color = vector<int>(N, -1);
    used = vector<vector<bool>>(N, vector<bool>(N));
    int res = 1;
    for (int v = 0; v < N; v++) {
        for (int u = 0; u < N; u++) {
            if (G[v][u] && !used[v][u]) {
                // 1色判定: edgeが1つでもあれば2色以上
                res = max(res, 2);
                for (int w = 0; w < N; w++) {
                    if (G[u][w] && G[w][v]) {
                        // 2色判定: 三角形が存在したら3色以上
                        res = max(res, 3);
                        fill(color.begin(), color.end(), -1);
                        color[v] = 0;
                        color[u] = 1;
                        if (!rec(v, u)) {
                            // 3色判定: 辺を共有する三角形のみで構成されない場合は4色
                            cout << 4 << endl;
                            return 0;
                        }
                        break;
                    }
                }
            }
        }
    }
    cout << res << endl;
}
