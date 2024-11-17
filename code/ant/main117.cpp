// Number Sets: p248
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ペアを全部チェックしたら間に合わない -> なんとか調べるのを1回ずつにしたい -> そもそもペアで考える必要はなく、同じ素因数を持つもの同士を一気にuniteすれば良い
// -> まさにエラトステネスの篩の考え方そのもの -> 対象区間が[A,B]なので区間篩が使えそう -> 素数のチェックの場合は[2,√B]の素数のみを調べればよかったが、今回は素因数なので少し違う
// -> 違った範囲の絞り方をする必要がある -> B-A<=1e6をなんとか使いたい -> 調べるべき素数も1e6だったら嬉しいなぁ -> 「a,bが共にpで割れる時、b-aもpで割れる」という有名事実から、p<=1e6が示せる
// -> 区間篩で[2,1e6]の素数を調べればOK

// ポイント
// a,b(b>a)の約数pは、b-aの約数でもある。つまりb-aは必ずp以上になる
// 「因数/約数/割れる」はセットで考えておく。そのままだとイメージしにくいので、文字でおいて実験する癖をつける
// 計算量から逆算して、「こうあって欲しい」という仮定を置くことも重要

struct UnionFind {
    // 親のインデックスを保持する
    // rootは負の値を取り、その絶対値がその木における要素数を表す
    vector<int> par;

    UnionFind(int n) : par(n, -1) {}
    void init(int n) { par.assign(n, -1); }

    int root(int x) {
        if (par[x] < 0) return x;
        else return par[x] = root(par[x]);  // 経路圧縮
    }

    bool same(int x, int y) {
        return root(x) == root(y);
    }

    bool unite(int x, int y) {
        x = root(x), y = root(y);
        if (x == y) return false;
        // 常に小さい木を大きい木に結合する
        if (par[x] > par[y]) swap(x, y);
        par[x] += par[y];
        par[y] = x;
        return true;
    }

    int size(int x) {
        return -par[root(x)];
    }
};

const int P_MAX = 1e6;

int main() {
    ll A, B, P; cin >> A >> B >> P;

    // [2,P_MAX]の素数を求めておく: エラトステネスの篩 O(P_MAXloglogP_MAX)
    vector<bool> is_prime(P_MAX + 1, true);
    is_prime[0] = is_prime[1] = false;
    int p = 0;
    for (int i = 2; i <= P_MAX; i++) {
        if (!is_prime[i]) continue;
        p++;
        for (int j = 2 * i; j <= P_MAX; j += i) is_prime[j] = false;
    }

    ll len = B - A + 1;
    UnionFind uf(len);
    // [2,P_MAX]の素数を列挙しつつ、[A,B]におけるその定数倍の値どうしをuniteする
    for (int i = 2; i <= P_MAX; i++) {
        if (!is_prime[i] || i < P) continue;

        ll start = (A + i - 1) / i * i;
        ll end = B / i * i;
        for (ll j = start; j <= end; j += i) {
            uf.unite(start - A, j - A);
        }
    }

    int res = 0;
    for (int i = 0; i <= len; i++) {
        if (uf.root(i) == i) res++;
    }
    cout << res << endl;
}
