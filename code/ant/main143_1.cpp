// ツリーの分割統治法: p320
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 本の解法

struct Edge {
    int to, w;
    Edge(int to, int w) : to(to), w(w) {};
};

int n, k, ans;
vector<vector<Edge>> G;
vector<int> subtree_size;
vector<bool> centroid;

void get_subtree_size(int v, int p) {
    subtree_size[v] = 1;
    for (auto ch : G[v]) {
        if (ch.to == p || centroid[ch.to]) continue;
        get_subtree_size(ch.to, v);
        subtree_size[v] += subtree_size[ch.to];
    }
}

// (残る最大の部分木の頂点数, 頂点番号)
pair<int, int> get_centroids(int v, int p, int size) {
    pair<int, int> res = make_pair(INT_MAX, -1);
    int s = 1, m = 0;
    for (auto ch : G[v]) {
        if (ch.to == p || centroid[ch.to]) continue;
        res = min(res, get_centroids(ch.to, v, size));
        m = max(m, subtree_size[ch.to]);  // vを中心とする各部分木の最大サイズ
        s += subtree_size[ch.to];  // vを含まない側の全ての部分木の合計サイズ
    }

    // vを含む側の部分木も考慮
    m = max(m, size - s);  // vを重心とした場合の最大部分木サイズ
    res = min(res, make_pair(m, v));  // vの部分木のさらに再帰的な部分木を含めた中で、最大部分木が最小になるものを返却
    return res;
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
    int j = dist.size();
    for (int i = 0; i < dist.size(); i++) {
        while (j > 0 && dist[i] + dist[j - 1] > k) j--;
        res += j - (j > i ? 1 : 0);  // 自分自身とのペアは除く
    }
    return res / 2;
}

// 分割: 再帰的に重心分解し、各部分木に対してペアを数え上げる
// 統治: mergeにより新たに増加するペアを加算する
void rec(int v) {
    // 重心を求める
    get_subtree_size(v, -1);
    int s = get_centroids(v, -1, subtree_size[v]).second;
    centroid[s] = true;
    // 分割する
    for (auto ch : G[s]) {
        if (centroid[ch.to]) continue;
        // 重心から見た各部分木を再帰的に分割
        rec(ch.to);
    }

    // mergeする部分木間でできるペアをカウント
    vector<int> dist;
    dist.push_back(0);
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
    // 分割統治法
    rec(0);

    cout << ans << endl;
}
