#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using ll = long long;
using mint = atcoder::modint998244353;

// ジャンル
// - 数列, 数え上げ, indexが数列の値になる問題, 条件を満たす数列の数え上げ, 組み合わせ最適化, 到達可能性問題

// 方針
// 数列の各位置の間に大小制約が存在する組み合わせ最適化問題なので、グラフで表現することを考える

// ポイント
// - Functional Graph
//   - 全ての頂点の出次数が1の有向グラフ
//   - 各連結成分内にちょうど1つ閉路が存在する
//   - どの頂点から出発しても必ず閉路に辿り着き、閉路から出ることはない -> 任意の頂点から|V|回移動すると必ず閉路ないの頂点に辿り着く
//     - これを利用して通常の有向グラフより簡単に閉路検出が行える
//   - サイクルを縮約すると有向木になる

struct UnionFind {
    vector<int> par;
    UnionFind(int n) : par(n, -1) {}
    void init(int n) { par.assign(n, -1); }
    int root(int x) { return par[x] < 0 ? x : par[x] = root(par[x]); }
    bool same(int x, int y) { return root(x) == root(y); }
    bool unite(int x, int y) {
        x = root(x), y = root(y);
        if (x == y) return false;
        if (par[x] > par[y]) swap(x, y);
        par[x] += par[y];
        par[y] = x;
        return true;
    }
    int size(int x) { return -par[root(x)]; }
};

int N, M;
vector<vector<int>> G;
vector<bool> in_cycle;
vector<vector<mint>> dp;

void dfs(int v) {
    for (auto ch : G[v]) {
        if (in_cycle[ch]) continue;
        dfs(ch);

        mint sum = 0;
        for (int k = 0; k < M; k++) {
            sum += dp[ch][k];
            dp[v][k] *= sum;
        }
    }
}

int main() {
    cin >> N >> M;
    vector<int> A(N);
    G = vector<vector<int>>(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        G[--A[i]].push_back(i);
    }

    // 閉路の縮約
    vector<vector<int>> cycles;
    in_cycle = vector<bool>(N);
    UnionFind uf(N);
    for (int i = 0; i < N; i++) {
        if (!uf.unite(i, A[i])) {
            int now = A[i];
            vector<int> cyc;
            do {
                cyc.push_back(now);
                in_cycle[now] = true;
                now = A[now];
            } while (now != A[i]);
            cycles.push_back(cyc);
        }
    }

    // dp
    mint ans = 1;
    dp = vector<vector<mint>>(N, vector<mint>(M, 1));
    for (auto cycle : cycles) {
        vector<mint> prod(M, 1);
        for (auto i : cycle) {
            // dp[i][j]を求める
            dfs(i);
            for (int j = 0; j < M; j++) prod[j] *= dp[i][j];
        }
        mint sum = 0;
        for (int j = 0; j < M; j++) sum += prod[j];
        ans *= sum;
    }

    cout << ans.val() << endl;
}
