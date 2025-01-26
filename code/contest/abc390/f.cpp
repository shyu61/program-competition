#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ジャンル
// 数式問題, 数え上げ, 増加部分列, 全ペア問題, 区間問題

// 方針
// いかにして全ペア走査せず計算するかが最大のポイント
// 典型アプローチとして逆転の発想で考える方法がある。
// つまり、全ペアを走査しながら条件を満たすものを数え上げる代わりに、全条件を走査しながらそれに合致するペアを数え上げる。
// 条件を満たす=最小操作としてl=iを選ぶことができるとすると、区間にlが含まれ、かつl-1が含まれない必要がある
// ちょっと考えると直接数えるより補集合を考えた方が圧倒的に簡単であることに気付く。つまり区間にlが含まれない場合を考える
// 各値についてindex配列を用意して各gapの中から2つ選ぶ組み合わせを合計すれば良い

int main() {
    int n; cin >> n;
    vector<int> a(n);
    vector<vector<int>> is(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        is[--a[i]].push_back(i);
    }

    auto f = [&](vector<int> x) -> ll {
        x.insert(x.begin(), -1);
        x.push_back(n);

        ll res = 0;
        for (int i = 1; i < x.size(); i++) {
            ll gap = x[i] - x[i - 1];
            res += gap * (gap - 1) / 2;
        }
        return res;
    };

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        vector<int> nis = is[i - 1];
        nis.insert(nis.end(), is[i].begin(), is[i].end());
        sort(nis.begin(), nis.end());
        ans += f(is[i]);  // c-1∉Sを満たすf(L,R)の個数
        ans -= f(nis);  // c-1∉Sかつc∉Sを満たすf(L,R)の個数
    }
    cout << ans << endl;
}
