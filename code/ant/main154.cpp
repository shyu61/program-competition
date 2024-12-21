// The Year of Code Jam: p357
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 思考フロー
// グリッド問題 x 最適化問題 -> 全探索,貪欲法,dp,グラフ
// -> 遷移の方向を決めづらいのでdpは難しそう、かつ制約が複雑: 隣接同士の制約, 必ず参加,不参加がある -> ネットワークフローで考える
// -> 参加不参加の2つの割当て最適化問題なので最小カットで考える -> 問題は同じ側のノード間に制約があること(隣接ノードが共に参加の場合のみコストがかかる)
// -> ナイーブなカットでは表現できない -> グリッドグラフは二部グラフであることを利用して片方のノードの意味を反転させれば良い
// そうすれば、隣接ノードが同じ側に属する時、その隣接ノード間のエッジはカットされることになるので、普通にノードのコストを乗せれば良い

// ポイント
// - グリッドグラフは常に二部グラフであることを念頭に置く
//   - 頂点はnodeと見る場合もあればedgeと見る場合もある
//     - nodeと見る場合: 交互や(x+y)の偶奇に異種nodeと見ると良い
//     - edgeと見る場合: x,yで異種nodeと見て(x,y)の組み合わせである頂点がそれらを結ぶと見る
// - 最小カットの同じ側のノード間にも制約があるケースの問題
//   - 片方のノードで意味を反転させる
//   - https://ikatakos.com/pot/programming_algorithm/graph_theory/maximum_flow/burn_bury_problem

struct Edge {
    int to, cap, rev;
    Edge(int to, int cap, int rev): to(to), cap(cap), rev(rev) {}
};

const int INF = 4 * 50 * 50;
vector<int> dx = {1,0,-1,0}, dy = {0,1,0,-1};
int N, M;
vector<vector<Edge>> G;
vector<bool> used;

void add_edge(int from, int to, int cap) {
    G[from].emplace_back(to, cap, G[to].size());
    G[to].emplace_back(from, 0, G[from].size() - 1);
}

int dfs(int v, int t, int f) {
    if (v == t) return f;
    used[v] = true;

    // 逆辺も含めて探索する
    for (auto &adj : G[v]) {
        if (!used[adj.to] && adj.cap > 0) {
            int d = dfs(adj.to, t, min(f, adj.cap));
            if (d > 0) {
                // 残余グラフを計算
                adj.cap -= d;
                G[adj.to][adj.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int max_flow(int s, int t) {
    int res = 0;
    while (1) {
        fill(used.begin(), used.end(), false);
        int f = dfs(s, t, INF);
        if (f != 0) res += f;
        else break;
    }
    return res;
}

int main() {
    cin >> N >> M;
    vector<vector<char>> grid(N, vector<char>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) cin >> grid[i][j];
    }

    G = vector<vector<Edge>>(N * M + 2);
    used = vector<bool>(N * M + 2);
    int res = 0;
    int s = N * M, t = s + 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int v = i * M + j;
            // グリッドグラフを二部グラフとみなして、片方について意味を反転させる
            // 順方向のノード: s側が参加,t側が不参加
            // 逆方向のノード: s側が不参加,t側が参加
            bool is_even = (i + j) % 2 == 0;  // 交互ではないことに注意。こうとることで上下左右が必ず異種グラフになる
            if (grid[i][j] == '#') {
                res += 4;
                // 既に参加が確定しているので、s側に割当てないといけない => s->vのエッジを切れないようにする
                is_even ? add_edge(s, v, INF) : add_edge(v, t, INF);
            } else if (grid[i][j] == '.') {
                // 既に不参加が確定しているので、t側に割当てないといけない => v->tのエッジを切れないようにする
                is_even ? add_edge(v, t, INF) : add_edge(s, v, INF);
            } else {
                res += 4;
                // 不参加にすることで幸福度は4減るのでs->vにコスト4のエッジを張る
                is_even ? add_edge(s, v, 4) : add_edge(v, t, 4);
            }
            if (is_even) {
                // 隣接の場合の考慮: 両方参加の場合のみコスト2のエッジを張る
                for (int r = 0; r < 4; r++) {
                    int i2 = i + dx[r], j2 = j + dy[r];
                    if (i2 >= 0 && i2 < N && j2 >= 0 && j2 < M) {
                        add_edge(v, i2 * M + j2, 2);
                    }
                }
            }
        }
    }

    // 幸福度のmaxから最小カットコストを引く
    res -= max_flow(s, t);
    cout << res << endl;
}
