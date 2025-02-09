#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// ジャンル
// グラフ問題, 連結成分

// 解けなかった理由
// - 貪欲法は確証がない限りは非常に危険。回避策があるならそれを使うに越したことはない
// - dsuのleaderには注意。経路圧縮によりmerge後はleaderが変化する可能性がある
// - 連結成分の数を減らしていくという操作は、bool配列でtrackするよりもeraseした方が良い
//   - その理由はmergeしたもの同士は消えるのではなく1つになって新たな連結成分として残るから
//   - こういった状況の場合はbool配列管理しにくいのでeraseしつつグローバルにtrackingする方が簡単
//   - mergeした後のleaderを再度setに入れるという発想がなかった

// ポイント
// vectorも末尾からなら順にpopすることができる

struct UnionFind {
    vector<int> parents;
    UnionFind(int n) : parents(n, -1) {}

    void init(int n) {
        parents.assign(n, -1);
    }

    int leader(int x) {
        return parents[x] < 0 ? x : parents[x] = leader(parents[x]);
    }

    bool same(int x, int y) {
        return leader(x) == leader(y);
    }

    int merge(int x, int y) {
        x = leader(x), y = leader(y);
        if (x == y) return x;
        if (parents[x] > parents[y]) swap(x, y);
        parents[x] += parents[y];
        parents[y] = x;
        return x;
    }

    int size(int x) {
        return -parents[leader(x)];
    }
};

// 正解実装
int main() {
    int n, m; cin >> n >> m;

    UnionFind uf(n);    
    vector<tuple<int, int, int>> ex;
    rep(i, m) {
        int a, b; cin >> a >> b; a--, b--;
        if (!uf.same(a, b)) uf.merge(a, b);
        else ex.emplace_back(i, a, b);
    }

    set<int> lds;
    rep(i, n) lds.insert(uf.leader(i));

    cout << lds.size() - 1 << endl;
    while (lds.size() > 1) {
        auto [ei, u, v] = ex.back(); ex.pop_back();
        int s = uf.leader(u); lds.erase(s);
        int t = *lds.begin(); lds.erase(t);

        int nl = uf.merge(s, t);
        lds.insert(nl);

        cout << ei + 1 << ' ' << u + 1 << ' ' << t + 1 << '\n';
    }
}

// 自分の実装(AC)
int main() {
    int n, m; cin >> n >> m;
    vector<pair<int, int>> es(m);
    rep(i, m) {
        int a, b; cin >> a >> b; a--, b--;
        es[i] = {a, b};
    }

    UnionFind uf(n);
    vector<tuple<int, int, int>> ex;
    rep(i, m) {
        auto [u, v] = es[i];
        if (!uf.same(u, v)) uf.merge(u, v);
        else ex.emplace_back(i, u, v);
    }

    vector<vector<int>> ex2(n);
    for (auto [ei, u, v] : ex) ex2[uf.leader(u)].push_back(ei);

    vector<int> lds;
    rep(i, n) lds.push_back(uf.leader(i));
    sort(lds.begin(), lds.end());
    lds.erase(unique(lds.begin(), lds.end()), lds.end());

    cout << lds.size() - 1 << endl;

    int j = 0;
    rep(i, lds.size()) {
        for (auto e : ex2[lds[i]]) {
            if (j == i) j++;
            if (j >= lds.size()) return 0;
            cout << e + 1 << ' ' << es[e].first + 1 << ' ' << lds[j] + 1 << '\n';
            j++;
        }
    }
}
