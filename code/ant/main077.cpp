// Jessica's Reading Problem: p137
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 区間に対するユニーク数の数え上げ問題。区間に対する数え上げとくれば尺取り法。
// 数え上げは単調性を持つため尺取り法がマッチする。

// map: 平行二分木(大体は赤黒木), 操作系はO(logn), 構築はO(nlogn), keyに応じてソートされる
// unordered_map: ハッシュテーブル, 操作系はO(1), 構築はO(n)
// set: 平行二分木(大体は赤黒木)
// unordered_set: ハッシュテーブル

int main() {
    int P; cin >> P;
    vector<int> a(P);
    unordered_map<int, int> um;
    for (int i = 0; i < P; i++) {
        cin >> a[i];
        um[a[i]]++;
    }

    int n_unique = um.size();
    um.clear();

    int right = 0, nu = 0, ans = P;
    for (int left = 0; left < P; left++) {
        while (nu < n_unique && right < P) {
            if (um[a[right++]]++ == 0) nu++;
        }

        if (nu == n_unique) {
            ans = min(ans, right - left);
            // leftをキャンセル
            if (--um[a[left]] == 0) nu--;
        } else break;
    }
    cout << ans << endl;
}
