// 2-SAT(Priest John's Busiest Day): P290
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 2-SATの利用シーン
// 大前提、求めたいものが論理命題であり、かつそれを複数の論理式の組み合わせによって表現できること
// 例) 区間の交差判定、制約付き選択、割当問題

// 充足可能性問題の考え方
// - 充足したい論理命題を決める
// - その命題を真にするために満たす必要がある"制約条件"を論理式として加えていく
// - 制約条件は、まず満たさなくなる条件を考えて、それを避けるための論理条件を定義する感じ

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

int parse_timestring(string s) {
    int hours, minutes;

    stringstream ss(s);
    char delimiter;
    ss >> hours >> delimiter >> minutes;

    return hours * 60 + minutes;
}

int main() {
    int N; cin >> N;
    vector<int> S(N), T(N), D(N);
    for (int i = 0; i < N; i++) {
        string s, t; cin >> s >> t >> D[i];
        S[i] = parse_timestring(s);
        T[i] = parse_timestring(t);
    }

    int V = N * 2;
    G = rG = vector<vector<int>>(V);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            // 最初と最初
            // 全ての終点が少なくとも1方の始点より後にあるか
            if (min(S[i] + D[i], S[j] + D[j]) > max(S[i], S[j])) {  // 区間の重複を判定する書き方: min,maxの比較でかける
                // ¬xi ∨ ¬xj
                // xi=>¬xj, xj=>¬xi
                add_edge(i, N + j);
                add_edge(j, N + i);
            }
            // 最初と最後
            if (min(S[i] + D[i], T[j]) > max(S[i], T[j] - D[j])) {
                // ¬xi ∨ xj
                // xi=>xj, ¬xj=>¬xi
                add_edge(i, j);
                add_edge(N + j, N + i);
            }
            // 最後と最初
            if (min(T[i], S[j] + D[j]) > max(T[i] - D[i], S[j])) {
                // xi v ¬xj
                // ¬xi=>¬xj, xj=>xi
                add_edge(N + i, N + j);
                add_edge(j, i);
            }
            // 最後と最後
            if (min(T[i], T[j]) > max(T[i] - D[i], T[j] - D[j])) {
                // xi v xj
                // ¬xi=>xj, ¬xj=>xi
                add_edge(N + i, j);
                add_edge(N + j, i);
            }
        }
    }

    scc(V);

    // xと¬xが異なるsccに含まれるか判定
    for (int i = 0; i < N; i++) {
        if (cmp[i] == cmp[i + N]) {
            // 充足不可
            cout << "no" << endl;
            return 0;
        }
    }

    // 充足可能な場合に解を復元
    cout << "yes" << endl;
    for (int i = 0; i < N; i++) {
        // xが¬xよりトポロジカル順で後の場合はtrue
        if (cmp[i] > cmp[N + i]) {
            // 最初
            printf("%02d:%02d %02d:%02d\n", S[i] / 60, S[i] % 60, (S[i] + D[i]) / 60, (S[i] + D[i]) % 60);
        } else {
            printf("%02d:%02d %02d:%02d\n", (T[i] - D[i]) / 60, (T[i] - D[i]) % 60, T[i] / 60, T[i] % 60);
        }
    }
}
