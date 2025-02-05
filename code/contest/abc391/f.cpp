#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// ジャンル
// 組合せ最適化, 全ペア走査問題, kth-number

// 方針
// 全ペアを生成せずに求解する必要がある。ソートして問題ないのでまずソートして考える
// 組合せ最適化問題などは、まずは考えやすい特定の条件下で実験してみるのがよい。例えばk=1つまり最大値は、3つとも先頭をとった場合になる。
// さらに、組合せの上限はN^3<=8e15だが、kの上限はk<=5e5なので、1番目からk番目まで逐次的に見ていくことができるという点も考慮に入れると、
// 貪欲に見ていけるのでは？と思いつくのは難しくない。同じ集合から値を取る限りは、必ずソート列の前から取る方がf値は大きくなるので、
// ほぼ貪欲に考えらそうと思いつく。
// 3列のうち最大の値を取り出し、取り出した列の次の値を候補とする操作を繰り返せばよく、pqが使える構造になっていることがわかる

// kth-numberは判定問題で考えるとうまくいくケースが多い。つまり、x以下の数が丁度k個になるxを二分探索する
// 後は、x以下の個数を高速に判定する方法が見つかれば良い。

// ポイント
// 上限値はヒントの宝庫

int main() {
    int n, K; cin >> n >> K;
    vector<vector<ll>> a(3, vector<ll>(n));
    rep(r, 3) {
        rep(i, n) cin >> a[r][i];
        sort(a[r].begin(), a[r].end(), greater<>());
    }

    priority_queue<tuple<ll, int, int, int>> pq;
    set<tuple<int, int, int>> used;
    auto push = [&](int i, int j, int k) {
        if (i >= n || j >= n || k >= n) return;
        if (used.contains({i, j, k})) return;
        ll val = a[0][i] * a[1][j] + a[1][j] * a[2][k] + a[2][k] * a[0][i];
        pq.emplace(val, i, j, k);
        used.insert({i, j, k});
    };

    push(0, 0, 0);
    rep(ki, K - 1) {
        auto [val, i, j, k] = pq.top(); pq.pop();
        push(i + 1, j, k);
        push(i, j + 1, k);
        push(i, j, k + 1);
    }

    ll ans = get<0>(pq.top());
    cout << ans << endl;
}
