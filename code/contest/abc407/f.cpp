#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;

// 🔷初見でどうやったら解けるか
// 全ペア走査ではないが、kごとにn個の要素を舐める必要があるので状況としては類似している。
// そう考えるとペア生成自体が間に合わないケースと言えるので、数式変換,対称性を使ってまとめる,主客転倒などが選択肢になる。
// 全ペアではなくクエリ問題という見方をすれば尺取り法や、区間データ構造を使ったアプローチも選択肢になる。
// 実験してみると主客転倒するしかないことがわかる。つまり配列の各要素ごとにどのkにどれだけ寄与するかを考えていく。
// すると領域加算の形になり、加算する値が一次関数になることが分かる。領域加算を高速にするにはimos法が第一選択肢であり、
// 定数じゃなく一次関数なら2回の累積和で表現できると思いつける。

// 🔷抑えるべき抽象論は？
// 明示的な全ペア走査の形状じゃなくても、2つの変数を全走査しないといけない問題設定なら、全ペア走査的アプローチが使える
// ある区間に静的な加減を行う場合はimos法が有効。
// - 定数なら1回,一次関数なら2回累積和をとる

int main() {
    int n; cin >> n;
    vector<P> a(n);
    rep(i, n) {
        cin >> a[i].first;
        a[i].second = i;
    }

    vector<int> L(n), R(n);
    {
        stack<P> st;
        rep(i, n) {
            while (!st.empty() && st.top().first <= a[i].first) st.pop();
            if (st.empty()) L[i] = i;
            else L[i] = i - st.top().second - 1;
            st.push(a[i]);
        }
    }
    {
        stack<P> st;
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && st.top().first < a[i].first) st.pop();
            if (st.empty()) R[i] = n - i - 1;
            else R[i] = st.top().second - i - 1;
            st.push(a[i]);
        }
    }

    vector<ll> res(n + 3);
    rep(i, n) {
        int minx = min(L[i], R[i]);
        int maxx = max(L[i], R[i]);
        res[1] += a[i].first;
        res[2 + minx] -= a[i].first;
        res[2 + maxx] -= a[i].first;
        res[3 + minx + maxx] += a[i].first;
    }

    vector<ll> res2(n + 1), ans(n + 1);
    rep(i, n) res2[i + 1] = res2[i] + res[i + 1];
    rep(i, n) ans[i + 1] = ans[i] + res2[i + 1];

    for (int i = 1; i <= n; i++) cout << ans[i] << '\n';
}
