// 強連結成分分解: p287
#include <bits/stdc++.h>
using namespace std;

// 思考フロー
// 全ての牛から到達可能な牛を調べれば良い -> 全牛でdfsするのは時間的に無理
// 到達可能性といえば連結成分問題 -> dfs,union-find,scc(sccを考えるときは、DAG,トポロジカルソートもセットで検討する)
// -> scc分解を考えるとDAGの最後のsccを調べれば良いことがわかる
// -> 孤立点の考慮も忘れずに

vector<vector<int>> G, rG;
vector<bool> used;
vector<int> vs, cmp;  // 属する強連結成分のトポロジカル順序

void add_edge(int from, int to) {
    G[from].push_back(to);
    rG[to].push_back(from);
}

void dfs(int v) {
    used[v] = true;
    for (auto adj : G[v]) {
        if (!used[adj]) dfs(adj);
    }
    vs.push_back(v);
}

void rdfs(int v, int k) {
    used[v] = true;
    cmp[v] = k;
    for (auto adj : rG[v]) {
        if (!used[adj]) rdfs(adj, k);
    }
}

int scc(int V) {
    used = vector<bool>(V);
    vs = cmp = vector<int>(V);

    for (int v = 0; v < V; v++) {
        if (!used[v]) dfs(v);  // vsを計算
    }

    fill(used.begin(), used.end(), 0);
    int k = 0;
    // 帰りがけに振った番号が大きいもの(根本側)から調べる
    for (int i = vs.size() - 1; i >= 0; i--) {
        if (!used[vs[i]]) rdfs(vs[i], k++);
    }
    return k;
}

int main() {
    int N, M; cin >> N >> M;
    G = rG = vector<vector<int>>(N);
    for (int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        add_edge(a, b);
    }

    int k = scc(N);
    // トポロジカル順で最後のsccを特定
    int u = 0, num = 0;
    for (int i = 0; i < N; i++) {
        if (cmp[i] == k - 1) {
            u = i;
            num++;
        }
    }

    // そもそもグラフが連結でない可能性があるので調べる
    fill(used.begin(), used.end(), 0);
    rdfs(u, 0);
    for (int i = 0; i < N; i++) {
        if (!used[i]) {
            num = 0;
            break;
        }
    }

    cout << num << endl;
}
