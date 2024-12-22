// E - Minimize Sum of Distances
// https://atcoder.jp/contests/abc348/tasks/abc348_e
// 全方位木dpによる解法
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 全方位木dp: ツリーdpを全ての頂点に対して効率的に実行する方法。ツリーdp実行時にmemo化される値を利用する。
//   全ての頂点に対してある処理を実行し、各値を比較して最終的な値を得たいようなケースで使える
//   親からの伝搬と、伝搬情報を使って子の値とmergeする2ステップから成る
//   memo化するのは各頂点で求めたい値だけでなく、merge関数の記述に必要な値もmemo化する必要がある場合がある
// この解法も重心の解法と同様にf(k)とf(k+1)の関係を理解しないとmerge関数を実装できない。親から子へ移動する時、
// csum分遠ざかる親のvalに、新たに親に加わる部分木のfxを加えたものが次に伝搬するvalになる。

int n;
vector<vector<int>> G;
vector<int> c;
vector<ll> dp, csum;
ll total = 0, ans = numeric_limits<ll>::max();

// ある点でツリーdpを実行しfxを求める
// merge関数では親のfxに加えて、csumがないと変化を記述できないので、dpとcsumの2つをmemo化する
void dfs1(int v, int par) {
    csum[v] = c[v];
    dp[v] = 0;
    for (auto adj : G[v]) {
        if (adj == par) continue;
        dfs1(adj, v);
        csum[v] += csum[adj];
        dp[v] += csum[adj] + dp[adj];
    }
}

void dfs2(int v, int par, ll val) {
    ans = min(ans, val + dp[v]);

    // 次に進む
    for (auto adj : G[v]) {
        if (adj == par) continue;
        // par側の部分木
        ll nval_par = val + (total - csum[v]);
        // vから生えるadj以外の部分木: csum[adj]分値は小さくなっていることに注意
        ll nval_others = (dp[v] - dp[adj] - csum[adj]) + (csum[v] - csum[adj]);
        ll nval = nval_par + nval_others;
        dfs2(adj, v, nval);
    }
}

int main() {
    cin >> n;
    G = vector<vector<int>>(n, vector<int>());
    c = vector<int>(n);
    dp = csum = vector<ll>(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        total += c[i];
    }

    dfs1(0, -1);
    dfs2(0, -1, 0);

    cout << ans << endl;
}
