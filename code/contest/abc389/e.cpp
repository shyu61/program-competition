#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ジャンル
// 組合せ最適化

// 方針
// ナップサックdpに似た設定の問題だが、「組合せ最適化」だという前提に立ち返ると、全探索→貪欲法 と検討するのがセオリー
// コスト関数と目的関数がそれぞれの最適化方向に対して広義単調性をもつので、貪欲法が適用できる
// つまり常に最小価格のものを選び続ければよく、pqでO(XlogN)で解けるがTLEする
// "単調性"というワードは尺取り法や二分探索などを考える良いワード。二分探索などをするときは、直接解を探索するのか間接的に解を探索するのかを考える
// "X個買えるか"はどの商品を幾つ買うかの組み合わせを求める必要があり高速に判定不可能。間接情報に切り替えて考える。
// "Y円の商品まで買えるか"は各商品でO(1)で計算できるのでO(N), 全体でO(NlogX)で解ける
// 最後にub円の商品を買えるだけ買うステップを忘れずにやれば求解できる

// ポイント
// ナップサック問題がdpを必要とする理由(貪欲性が成立しない理由)
// - コスト関数(価格)と目的関数(価値)がそれぞれの最適化の方向に対して単調性か成立しないから
//   - つまり、価格が小さいものが常に価値が小さくないという広義単調性が成立しない
//   - 価値密度で考えると大まかに良い組み合わせはわかるが、制約金額をギリギリまで使い切るために価値が最大ではないが金額の小さい商品を選んだほうが良い場合が存在する
// - 一方で本問題は、価値(コスト関数)が小さいものが常に個数(目的関数)の増分が小さくないという広義単調性が成立するため貪欲法が適用できる
// - 一般化: 「コスト関数と目的関数がそれぞれの最適化方向に対して広義単調性をもつ」場合に貪欲性が成立する

int main() {
    int n; ll m; cin >> n >> m;
    vector<int> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];

    auto f = [&](ll x) -> pair<ll, ll> {
        x--;
        ll num = 0, cost = 0;
        for (auto pi : p) {
            ll k = (x + pi) / (2 * pi);
            if (k > 0 && m / k / k / pi == 0) return {-1, m + 1};  // overflow対策
            num += k;
            cost += k * k * pi;
            if (cost > m) return {-1, m + 1};
        }
        return {num, cost};
    };

    // mid円未満のものを全部買えるか判定
    auto check = [&](ll mid) -> bool { return f(mid).second <= m; };

    ll lb = 1, ub = m + 1;
    while (ub - lb > 1) {
        ll mid = (lb + ub) / 2;
        check(mid) ? lb = mid : ub = mid;
    }

    auto [ans, cost] = f(lb);

    // ちょうどlb円のものを買えるだけ買う
    ans += (m - cost) / lb;
    cout << ans << endl;
}

// ================================================
// TLEするがシンプルな解法

using TL = tuple<ll, ll, int>;
int main() {
    int n; ll m; cin >> n >> m;
    vector<int> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];

    priority_queue<TL, vector<TL>, greater<TL>> pq;
    for (int i = 0; i < n; i++) pq.emplace(p[i], 1, i);

    ll cost = 0, ans = 0;
    while (!pq.empty()) {
        auto [c, num, i] = pq.top(); pq.pop();
        cost += c;
        if (cost > m) break;
        ans++;
        pq.emplace(p[i] * (2 * num + 1), num + 1, i);
    }
    cout << ans << endl;
}
