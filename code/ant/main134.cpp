// LCA: p295
#include <bits/stdc++.h>
using namespace std;
using P = pair<int, int>;

// 思考フロー
// 木構造の距離問題 -> 素直に考えるならdfsだが、O(qn)は間に合わない -> 2^kテーブルかオイラーツアーで配列に直して区間処理するか
// -> 更新があるので後者を採用する -> LCAは区間における最小値(RMQ)だが、距離は区間和なのでセグ木かBITを使う
// -> BITの方がより高速なので使うとすると、u,v間の距離は、sum(u)+sum(v)-sum(lca(u,v))*2になる
// -> 木を配列に直す上での最大の注意点は重複があること。LCAはRMQなので行きがけ帰りがけどっちでも値は同じなので考慮しなくて良いが、距離は和なので考慮する必要がある
// -> 帰りしはadd(k,-cost)とすればsumするときに打ち消してくれる。あとはdfsしながらaddなりすれば良い

// ポイント
// 木はdfsを使って配列に変換することができる => その配列は区間としての性質を持つので、区間アルゴリズムが使える
// - 距離: 区間和 => 累積和,尺取り法,セグ木,BIT
// - LCA(=深さ): RMQ => セグ木
// -> セグ木やBITは重複がある訪問番号に対して構築すること。lcaの戻り値はノード番号なので注意
// ただし重複があることに注意する。RMQは重複を考慮しなくて良いが、区間和は考慮する必要がある。帰りがけは-costをaddすることは覚えておく

// 木の距離の求め方
// - dfs
// - 2^kテーブル
// - LCA+BIT

const int INF = numeric_limits<int>::max();
struct RMQ {
    vector<P> dat;
    int sz = 1;

    RMQ() {}
    // n: 要素数, a: 初期化時に利用する値
    RMQ(int n, const vector<int>& a) {
        while (sz < n) sz *= 2;
        dat = vector<P>(sz * 2 - 1, make_pair(INF, -1));

        for (int i = 0; i < n; i++) dat[i + sz - 1] = make_pair(a[i], i);
        for (int i = sz - 2; i >= 0; i--) {
            dat[i] = min(dat[i * 2 + 1], dat[i * 2 + 2]);
        }
    }

    // (value,index)
    P query(int a, int b, int k, int l, int r) {
        if (b <= l || r <= a) return make_pair(INF, -1);
        if (a <= l && r <= b) return dat[k];
        else {
            P vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
            P vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
            return min(vl, vr);
        }
    }

    // k: 要素番号, a: 更新値
    void update(int k, int a) {
        // ノード番号に変換
        k += sz - 1;
        dat[k].first = a;
        while (k > 0) {
            k = (k - 1) / 2;
            dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
        }
    }
};

template <typename T>
struct BIT {
    vector<T> bit;
    T n;
    BIT() {};
    BIT(T n_) : bit(n_ + 1, 0), n(n_) {};

    T sum(int i) {
        T s = 0;
        while (i > 0) {
            s += bit[i];
            i -= i & -i;
        }
        return s;
    };

    void add(int i, T x) {
        while (i <= n) {
            bit[i] += x;
            i += i & -i;
        }
    };
};

struct Edge {
    int id, to, cost;
    Edge() {};
    Edge(int id, int to, int cost): id(id), to(to), cost(cost) {};
};

vector<vector<Edge>> G;
vector<int> depth, tour, preorder, edgeidx;
BIT<int> bit;
RMQ rmq;

void dfs(int v, int p, int d, int& k) {
    preorder[v] = k;
    tour[k] = v;
    depth[k++] = d;
    for (auto u : G[v]) {
        if (u.to != p) {
            bit.add(k, u.cost);
            edgeidx[u.id * 2] = k;

            dfs(u.to, v, d + 1, k);
            tour[k] = v;
            depth[k++] = d;

            bit.add(k, -u.cost);
            edgeidx[u.id * 2 + 1] = k;
        }
    }
}

int lca(int u, int v) {
    int s = min(preorder[u], preorder[v]);
    int t = max(preorder[u], preorder[v]);
    return tour[rmq.query(s, t + 1, 0, 0, rmq.sz).second];
}

int main() {
    int n, q, s; cin >> n >> q >> s; s--;
    vector<int> A(n), B(n), W(n);
    G = vector<vector<Edge>>(n);
    for (int i = 0; i < n - 1; i++) {
        cin >> A[i] >> B[i] >> W[i];
        A[i]--; B[i]--;
        G[A[i]].emplace_back(i, B[i], W[i]);
        G[B[i]].emplace_back(i, A[i], W[i]);
    }

    // 初期化
    bit = BIT<int>((n - 1) * 2);
    depth = tour = vector<int>(n * 2 - 1);
    edgeidx = vector<int>((n - 1) * 2);
    preorder = vector<int>(n);
    int k = 0;
    dfs(0, -1, 0, k);
    rmq = RMQ(n * 2 - 1, depth);

    int v = s;
    while (q--) {
        char c; cin >> c;
        if (c == 'A') {
            int x; cin >> x; x--;
            // 現在地からxへ移動
            int p = lca(v, x);
            cout << bit.sum(preorder[v]) + bit.sum(preorder[x]) - bit.sum(preorder[p]) * 2 << endl;
            v = x;
        } else {
            int x, t; cin >> x >> t; x--;
            // x番の道路のコストをtに変更
            bit.add(edgeidx[x * 2], t - W[x]);
            bit.add(edgeidx[x * 2 + 1], W[x] - t);
            W[x] = t;
        }
    }
}
