#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using ll = long long;

// Mo's algorithm
// 平方分割から派生したアルゴリズム
// 区間のmergeが高速に行えないケースで有用。Mo's algorithmはmergeを行わず、尺取り法と同様に区間を伸縮させることで、重複部分の計算結果を使い回す手法をとっている。
// (セグ木はその区間の代表値同士に結合則が成立することを前提としている。例えばn_uniqueなどはこの結合則が成立しない)
// https://take44444.github.io/Algorithm-Book/range/mo/main.html

// 使える条件
// - クエリの先読みが可能
// - 要素が不変
// - [l,r)の結果から[l,r-1),[l,r+1),[l-1,r),[l+1,r)を高速に求められる
// - [l,m)と[m,r)の結果をmergeして[l,r)を高速に求めることができない(できるならセグ木などを使えば良い)

// 計算量
// O((N+Q)√N)
// - r方向: 各バケットでNの移動なので、O(N√N)
// - l方向: 各クエリで最悪バケットの端から端への移動(√N)があるので、O(Q√N)

// 思考フロー
// ナイーブに処理したら間に合わない -> Xk,Ykが単調性を保証するように処理するなら、何らかしらの累積構造が使えそう
// -> 処理順を変えても問題さそうなので、累積構造が使えないか考えてみる -> 絶対値は単純な区間のmergeが行えない。セグ木などの典型的な区間アルゴリズムが使えない
// -> こういう時は区間の伸縮を愚直に行う mo's algorithm を検討する(尺取り法と近い設計)
// -> 区間の伸縮が高速に行えることが全体なので調べてみる。この時mo's algorithmは最終的には典型的な区間アルゴリズムを内部で使う形になることが多いことを念頭に入れておく。
// -> f(x+1,y)-f(x,y) = yAx+1 + ΣBj - 2{(y-c)Ax+1 + s} より、累積個数と累積和が手に入れば高速に処理できることがわかる
// -> fenwick_treeを使う時はindex空間に注意しながら実装する

// ジャンル
// - 数列, 数式問題, 区間クエリ, 累積和, 区間mergeができない累積構造

// 方針
// 範囲クエリで累積和を求める数式なので累積構造を使って高速化したい。区間アルゴリズムの適用を検討する
// 絶対値は大抵扱いにくく区間mergeができないので、累積和やセグ木の適用が難しいかも。尺取り法やMo's algorithmあたりも選択肢に入れる

// ポイント
// 数式問題はそれ自体がジャンルではなく、数式が何を表すか特定できて初めてジャンル特定ができる
// ジャンル特定方法
// - (1)数式の構造解析: 外側演算子の意味(Σやmin/maxなど), 内部の要素の意味を特定
// - (2)数式の目的を特定: 最終的にその数式が何を求めているのか特定
//   - 数え上げ, 最適化, sum/avg, ...

template<typename T=int>
struct CC {
    bool initialized;
    vector<T> xs;

    CC(): initialized(false) {}
    void add(T x) { xs.push_back(x); }
    void init() {
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        initialized = true;
    }
    int size() {
        if (!initialized) init();
        return xs.size();
    }

    int operator()(T x) {
        if (!initialized) init();
        return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
    }
    T operator[](int i) {
        if (!initialized) init();
        return xs[i];
    }
};

vector<ll> A, B;
CC cc;
atcoder::fenwick_tree<ll> ca, cb, sa, sb;

// x方向に伸縮する
void add_a(int i, int sign, int m, ll& now) {
    int ai = cc(A[i]);
    // 差分計算: f(X+1,Y)-f(X,Y) = Σj=1_to_Y |Ax+1-Bj|
    // {B1,B2,..,By}のうち、Aiより小さいものの個数: cb.sum(0, ai)
    //                　   Aiより大きいものの個数: cb.sum(ai, m)
    now += (cb.sum(0, ai) * A[i] * sign) - (sb.sum(0, ai) * sign);  // Ax+1>Bj の時
    now -= (cb.sum(ai, m) * A[i] * sign) - (sb.sum(ai, m) * sign);  // Ax+1<Bj の時
    ca.add(ai, sign);
    sa.add(ai, A[i] * sign);
}

// y方向に伸縮する
void add_b(int i, int sign, int m, ll& now) {
    int bi = cc(B[i]);
    now += (ca.sum(0, bi) * B[i] * sign) - (sa.sum(0, bi) * sign);  // Bx+1>Aj の時
    now -= (ca.sum(bi, m) * B[i] * sign) - (sa.sum(bi, m) * sign);  // Bx+1<Aj の時
    cb.add(bi, sign);
    sb.add(bi, B[i] * sign);
}

int main() {
    int N; cin >> N;
    A = B = vector<ll>(N);
    for (int i = 0; i < N; i++) cin >> A[i];
    for (int i = 0; i < N; i++) cin >> B[i];
    int Q; cin >> Q;
    vector<tuple<int, int, int>> query(Q);
    for (int i = 0; i < Q; i++) {
        int x, y; cin >> x >> y;
        query[i] = {x, y, i};
    }

    int w = 1000;  // bucket size: N/wとQ/wが大体同じになるようにwを決める (N/w: バケット数, Q/w: バケットあたりのクエリ数)
    sort(query.begin(), query.end(), [w](const auto& a, const auto& b) {
        // bucket番号
        int ba = get<0>(a) / w;
        int bb = get<0>(b) / w;
        if (ba != bb) return ba < bb;
        // bucket番号の偶奇に応じて、yについての昇順降順を切り替える
        return (ba % 2 == 0) ? get<1>(a) < get<1>(b) : get<1>(a) > get<1>(b);
    });

    // 座標圧縮
    for (int i = 0; i < N; i++) {
        cc.add(A[i]);
        cc.add(B[i]);
    }

    int m = cc.size();
    ca = cb = sa = sb = atcoder::fenwick_tree<ll>(m);

    // クエリを順番に処理する
    vector<ll> ans(Q);
    int x = 0, y = 0;  // 現在地
    ll now = 0;
    for (auto [xi, yi, i] : query) {
        // xiまでxを進める
        // 進めながらnow値を更新していく
        while (x < xi) add_a(x++, 1, m, now);
        while (x > xi) add_a(--x, -1, m, now);
        while (y < yi) add_b(y++, 1, m, now);
        while (y > yi) add_b(--y, -1, m, now);
        ans[i] = now;
    }
    for (auto v : ans) cout << v << "\n";
}
