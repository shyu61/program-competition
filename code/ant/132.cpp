// 2-SAT: P288
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 充足可能性問題(SAT): 1つの命題論理式が与えられたとき、それに含まれる論理変数にうまく真/偽を割り当てることで全体を真にできるかという問題
// 一般にNP完全だが、クロージャ内のリテラルが高々2の乗法標準形(いくつかのクロージャが論理積∧で繋がった状態)を2-SATといいsccで高速に解ける

// 集合と同じ(包除原理)で、論理和より論理積の方が扱いやすい。ゆえに論理和を論理積に変換し、同時に満たすべき関係を連結成分として表現する
// これにより論理積のみで表されることになるので、各条件式=>を満たすようにすると全てtrueになって充足する
// トポロジカル順で¬x->xの時はx=true, 逆はx=falseにする
// => 理由は、論理和を条件式に変換した影響によるもので、異なるsccに属していても条件式は満たす必要がある。
//   トポロジカル順がx->¬xということは、x=>¬xという条件式があるということなので、x=falseにする必要がある
//   ただしscc同士が完全に独立している場合はtrue,falseどっちを割り当ててもいい

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

int main() {
    int V = 6;
    G = rG = vector<vector<int>>(V);

    add_edge(3, 4);  // ¬a=>¬b
    add_edge(1, 0);  // b->a¬
    add_edge(4, 2);  // ¬b=>c
    add_edge(5, 1);  // ¬c=>b
    add_edge(2, 3);  // c=>¬a
    add_edge(0, 5);  // a=>¬c

    scc(V);

    // xと¬xが異なるsccに含まれるか判定
    for (int i = 0; i < 3; i++) {
        if (cmp[i] == cmp[i + 3]) {
            // 充足不可
            cout << "no" << endl;
            return 0;
        }
    }

    // 充足可能な場合に解を復元
    cout << "yes" << endl;
    for (int i = 0; i < 3; i++) {
        // xが¬xよりトポロジカル順で後の場合はtrue
        cout << (cmp[i] > cmp[i + 3] ? "true" : "no") << endl;
    }
}
