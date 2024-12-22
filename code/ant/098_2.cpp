// 二部マッチング: p195
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 増加パスを使った方法
// 増加パス: "マッチング数"を増加させるパス
// 始点と終点が共に未マッチノードであり、未マッチ/マッチが交互に現れる経路を指す。
// この経路は未マッチ/マッチを反転することで1つペアを増やすことができる
// 二部グラフは必ず異種間にエッジが張られるため、反転しても問題ないが一般グラフならそうはいかない

// 抽象化
// このように、ネットワークフロー問題では、"改善可能なパス"を見つけるアプローチがしばしば取られる
// これはつまり、一足飛びに求解することが難しく、段階的に状況を改善していくアプローチが主流ということを示している
// 条件に"交互"な要素がある問題では、反転は条件を満たしたまま構造上の変化をもたらすことができるので便利

vector<vector<int>> G;
vector<int> match;
vector<bool> used;

// 増加パスの探索
bool dfs(int v) {
    // 二部グラフの性質上、再訪せずdfsすると異種間を交互に行き来することになる
    used[v] = true;

    for (auto u : G[v]) {
        int w = match[u];
        // 未マッチが見つかれば終了
        // マッチ済みならさらに探索(マッチ先からの遷移先ノードとは絶対ペアにならないので、結果交互に未マッチ/マッチが現れることになる)
        if (w < 0 || !used[w] && dfs(w)) {  // マッチ先から探索を再開する、uからじゃないことに注意
            match[v] = u;
            match[u] = v;
            return true;
        }
    }
    return false;
}

int main() {
    int N, K, M; cin >> N >> K >> M;
    G = vector<vector<int>>(N + K);
    for (int i = 0; i < M; i++) {
        int x, y; cin >> x >> y;
        x--; y = y + N - 1;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    match = vector<int>(N + K, -1);
    used = vector<bool>(N + K);
    int ans = 0;
    for (int i = 0; i < N + K; i++) {
        if (match[i] >= 0) continue;
        fill(used.begin(), used.end(), false);
        if (dfs(i)) ans++;
    }

    cout << ans << endl;
}
