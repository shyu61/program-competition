#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ジャンル
// 逐次処理問題, 組合せ論, 数え上げ, 全探索/全列挙

// 方針
// 逐次操作問題であり、無限時間後の収束状態を求める類の問題。
// 順序依存性がないことは明らかなので2つの袋のmergeを逐次的に処理していくのではなく最終状態を考える
// すると、単なる集合分割問題であることがわかる。ベル数の考え方を使えば解ける

// ポイント
// - 異常に制約が小さい場合、全探索,全列挙や集合の走査(bit全探索),半分全列挙などを疑え!
// - unordered_set,unordered_setはどちらもhashテーブルベースでO(1)と高速
// - xorは交換法則が成立する
// - ベル数

int main(){
    int n; cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<ll> seen;
    vector<vector<ll>> pt;
    auto dfs = [&](auto dfs, int cur) -> void {
        if (cur == n) {
            ll res = 0;
            for (auto sub : pt) {
                ll sum = 0;
                for (auto v : sub) sum += v;
                res ^= sum;
            }
            seen.push_back(res);
            return;
        }

        for (int i = 0; i < pt.size(); i++) {
            pt[i].push_back(a[cur]);
            dfs(dfs, cur + 1);
            pt[i].pop_back();
        }

        pt.push_back(vector<ll>{a[cur]});
        dfs(dfs, cur + 1);
        pt.pop_back();
    };

    dfs(dfs, 0);
    sort(seen.begin(), seen.end());
    seen.erase(unique(seen.begin(), seen.end()), seen.end());
    cout << seen.size() << endl;
}

// より高速な実装
int main(){
    int n; cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    vector<ll> seen, sums;
    auto dfs = [&](auto dfs, int cur) -> void {
        if (cur == n) {
            ll res = 0;
            for (auto sum : sums) res ^= sum;
            seen.push_back(res);
            return;
        }

        for (int i = 0; i < sums.size(); i++) {
            sums[i] += a[cur];
            dfs(dfs, cur + 1);
            sums[i] -= a[cur];
        }

        sums.push_back(a[cur]);
        dfs(dfs, cur + 1);
        sums.pop_back();
    };

    dfs(dfs, 0);
    sort(seen.begin(), seen.end());
    seen.erase(unique(seen.begin(), seen.end()), seen.end());
    cout << seen.size() << endl;
}
