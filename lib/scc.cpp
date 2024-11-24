#include <bits/stdc++.h>
using namespace std;

// 強連結成分の性質
// - 強連結成分を縮約して1つの頂点とすると、グラフはDAGになる
// - 任意のグラフを強連結成分の和集合(積集合なし)に分解できる
// - 要素数が2以上の強連結成分は必ず閉路を持つ

// 2回のdfsで強連結成分が求まる理由
// 目的は「双方向にパスが存在する頂点群」を探すこと。
// ゆえにまずは普通にパスがある頂点群を探索(post_orderを採番することで、大->小にパスがあることを保証する)し、
// 次は最初入口だった頂点を出口として逆向きに探索する(エッジを反転して再び大→小へパスがあるか調べる)ことで双方向にパスがあるかをチェックしている

// 無向グラフの関節点と非常に似ている
// Tarjan法はlow_linkを使うのでまさに同じアルゴリズムだと言える
// 要するに子から祖先へのバイパスがあるかを調べている(親から子孫へは当然パスがあるのでバイパスがあれば双方にパスがあることになる)

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

int scc() {
    int V; cin >> V;
    G = rG = vector<vector<int>>(V);
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
