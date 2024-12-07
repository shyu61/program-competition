// ツリーの分割統治法: p320
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 自前実装

// 思考フロー
// dfsで全部調べるとO(n^2)で間に合わない -> 数え上げは累積的であり、かつ木は部分独立性があり分割統治法と相性が良いので考えてみる
// -> 木の分割は重心を使う。頂点数をk以下まで分割すれば各部分木でのペアは0なので、統治の際に作られるペアだけ数えれば良いことがわかる
// -> 統治がO(n)かO(nlogn)まででできるなら解ける。すなわち、2つの配列の各要素の組み合わせでk以下のものの個数をO(n)かO(nlogn)で数えられるかどうか
//    ナイーブにはO(n^2)。マージソートは2数の大小比較だが、今回は2数の和とkの大小比較なので同じ計算量でできる。ソートは統治の際に引き継げないので毎回ソートする必要がある。
//    故にO(nlogn) + O(n) = O(nlogn)。全体でO(nlog^2 n)でできる

// ポイント
// 分割統治法の統治は一旦mergeソートをベースに考えてみる
// 木の分割は実際に分割するのではなく「centroid[v]=trueのノードより先には進まないない」とすることで代替する
// 複数グループある状況で、2グループから値を抽出し何らかの処理をしたい場合、nC2通りのグループを考えるのは面倒なので、重複分を事前処理し"まとめて1つのグループとしてグループ内ペアリングを考える"と良い

struct Edge {
    int to, w;
    Edge(int to, int w) : to(to), w(w) {};
};

int n, k, ans;
vector<vector<Edge>> G;
vector<int> subtree_size;
vector<bool> centroid;  // 実際に分割するのではなく、trueのノードより先には進めないようにする

// 重心のノード番号を調べる(複数ある時は先に見つかった方を返却)
// https://qiita.com/drken/items/4b4c3f1824339b090202
int get_centroids(int v, int p, int size) {
    subtree_size[v] = 1;
    bool is_centroid = true;
    for (auto ch : G[v]) {
        if (ch.to == p || centroid[ch.to]) continue;
        int c = get_centroids(ch.to, v, size);
        if (c != -1) return c;
        if (subtree_size[ch.to] > size / 2) is_centroid = false;
        subtree_size[v] += subtree_size[ch.to];
    }
    if (size - subtree_size[v] > size / 2) is_centroid = false;
    return is_centroid ? v : -1;
}

// 頂点vまでの距離を計算
void dfs(int v, int p, int pw, vector<int>& dist) {
    dist.push_back(pw);
    for (auto ch : G[v]) {
        if (ch.to == p || centroid[ch.to]) continue;
        int w = pw + ch.w;
        dfs(ch.to, v, w, dist);
    }
}

// 和がk以下となるペアの個数を求める
int count_pairs(vector<int> dist) {
    int res = 0;
    sort(dist.begin(), dist.end());

    int t = dist.size() - 1;
    for (int s = 0; s < t; s++) {
        while (s < t && dist[s] + dist[t] > k) t--;
        res += t - s;
    }
    return res;
}

// 分割: 再帰的に重心分解する
// 統治: mergeにより新たに増加するペアを加算する
void rec(int v, int size) {
    int s = get_centroids(v, -1, size);
    centroid[s] = true;
    // 重心から見た各部分木を再帰的に分割
    for (auto ch : G[s]) {
        if (centroid[ch.to]) continue;
        rec(ch.to, subtree_size[ch.to]);
    }

    // mergeする部分木間でできるペアをカウント
    vector<int> dist;
    dist.push_back(0);  // 頂点sの分
    // 重心により分割された各部分木を走査
    for (auto ch : G[s]) {
        if (centroid[ch.to]) continue;

        // sまでの距離を計算
        vector<int> tdist;
        dfs(ch.to, s, ch.w, tdist);
        ans -= count_pairs(tdist);  // 重複する分を予め引いておく
        dist.insert(dist.end(), tdist.begin(), tdist.end());
    }

    // mergeする
    ans += count_pairs(dist);
    centroid[s] = false;
}

int main() {
    cin >> n >> k;
    G = vector<vector<Edge>>(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b, l; cin >> a >> b >> l;
        a--; b--;
        G[a].emplace_back(b, l);
        G[b].emplace_back(a, l);
    }

    subtree_size = vector<int>(n);
    centroid = vector<bool>(n);
    rec(0, n);

    cout << ans << endl;
}
