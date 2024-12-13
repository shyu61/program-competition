// 文字列検索: p333
#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
using GP = vector<vector<char>>;

// 思考フロー
// グリッドでのパターン一致問題 -> パターン一致問題といえばrolling hashだが、そのままでは1次元にしか適用できないのでなんとかして拡張することを考える
// -> 2次元は同時に扱えないなら別々に考えれば良い -> 最終的に欲しいのはPxQのhash値
// -> まずは行方向にhash計算は普通にできる。問題は列方向だが、すでに計算済みのhash値で行方向を圧縮できることに気付けると行方向も普通に計算すればPxQのhash値が計算できる
// -> あとは普通に数値同値の比較をすればいいだけ

// ポイント
// rolling hashの文字項は一意であればなんでもよいので、文字でなくてもhash値でも良い
// そもそもhashとは、圧縮表現。
//   - 文字列長mをhash化して1文字にすることでO(1)比較を可能にしていて、これは次元圧縮に簡単に応用できる

const ull B1 = 9973, B2 = 100000007;
int N, M, P, Q, T;
GP field;
vector<GP> patterns;

vector<vector<ull>> calc_hash(GP a, int n, int m) {
    // 行方向にhash計算
    vector<vector<ull>> rhash(n, vector<ull>(m - Q + 1));
    ull t1 = 1;
    for (int i = 0; i < Q; i++) t1 *= B1;
    for (int i = 0; i < n; i++) {
        ull e = 0;
        for (int j = 0; j < Q; j++) e = e * B1 + a[i][j];
        // windowサイズQで1つずつスライドさせていく
        for (int j = 0; j + Q <= m; j++) {
            rhash[i][j] = e;
            if (j + Q < m) e = e * B1 + a[i][j + Q] - a[i][j] * t1;
        }
    }

    // 列方向にhash計算
    vector<vector<ull>> chash(n - P + 1, vector<ull>(m - Q + 1));
    ull t2 = 1;
    for (int i = 0; i < P; i++) t2 *= B2;
    for (int i = 0; i + Q <= m; i++) {
        ull e = 0;
        for (int j = 0; j < P; j++) e = e * B2 + rhash[j][i];
        for (int j = 0; j + P <= n; j++) {
            chash[j][i] = e;
            if (j + P < n) e = e * B2 + rhash[j + P][i] - rhash[j][i] * t2;
        }
    }
    return chash;
}

int main() {
    cin >> N >> M >> P >> Q >> T;
    field = GP(N, vector<char>(M));
    patterns = vector<GP>(T, GP(P, vector<char>(Q)));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) cin >> field[i][j];
    }
    for (int t = 0; t < T; t++) {
        for (int i = 0; i < P; i++) {
            for (int j = 0; j < Q; j++) cin >> patterns[t][i][j];
        }
    }

    vector<vector<ull>> hash;
    multiset<ull> unseen;
    for (int t = 0; t < T; t++) {
        hash = calc_hash(patterns[t], P, Q);
        unseen.insert(hash[0][0]);
    }

    hash = calc_hash(field, N, M);
    for (auto u : hash) {
        for (auto v : u) {
            unseen.erase(v);
        }
    }

    cout << T - unseen.size() << endl;
}
