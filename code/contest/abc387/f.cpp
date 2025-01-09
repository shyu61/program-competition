#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// ジャンル
// - 数列, 数え上げ
// - 数列の数え上げは条件からさらにジャンルを特定
//   - 要素間の依存関係が条件: dp, グラフ
//     - 閉路がないもしくは縮約できる, 遷移の方向を規定できる: dp
//     - それ以外: グラフ

// 方針
// 数列の要素間依存関係(隣接ではない)なので、dpかグラフで考える。
// ただしグラフはパス探索などを除いて、一般に数え上げには適さないのでdpが使える形に帰着させることを考える。
// 閉路が含まれる可能性があるので、縮約してdagにしてからdpを適用する作戦でいく
// Functional Graphっぽいので、閉路は必ず一つで、縮約した頂点を根としてdpすれば良さそう
// dpの高速化は区間アルゴリズムか線形min/maxあたりを検討する

// ポイント
// - Functional Graph
//   - 全ての頂点の出次数が1の有向グラフ
//   - 各連結成分内にちょうど1つ閉路が存在する
//   - どの頂点から出発しても必ず閉路に辿り着き、閉路から出ることはない -> 任意の頂点から|V|回移動すると必ず閉路ないの頂点に辿り着く
//     - これを利用して通常の有向グラフより簡単に閉路検出が行える
//   - サイクルを縮約すると有向木になる
//   - トポロジカルソートせずともdpが適用可能(縮約したサイクルを根とすれば良い)
// - 数列の数え上げ問題のジャンル特定
//   - 数え上げ条件により特定を行う
//   - (1)各要素を独立に扱う場合
//   - (2)隣接要素間の制約の場合: 区間アルゴリズム
//   - (3)離れた要素間の制約の場合: dp, グラフ
//   - (4)要素の集合に対する制約の場合: bitdpなど
// - dp vs グラフ
//   - 制約条件下での数え上げや最適化, 組合せ最適化などでよく使う両者のusecase
//   - dp: 閉路がない, 遷移の順序を規定可能, 局所制約のみ, 状態数が多すぎない, 範囲条件がない(空間が小さい)
//   - グラフ: 値が離散, 最適化問題(数え上げは限定的), 局所制約以外にも全体制約がある, 閉路がある
//   - その他にも連立方程式や行列累乗を使うケースもある
// - グラフの問題はまず最初にFunctional Graphかどうかチェックする
// - dpの高速化
//   - 累積構造を活用した区間アルゴリズム(累積和,セグ木など)
//   - 漸化式が線形min/maxならConvex Hull Trick

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
