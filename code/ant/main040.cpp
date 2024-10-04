// その他の例題(Saruman's Army): p47
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// できるだけ重複が少ないように塗ればいいことは直感的にわかる -> 貪欲法が使えそう
// 前までの結果に非依存的に次塗る点を決定できるので、局所最適性が成立するため貪欲法で解ける
// 範囲の右端より大きい最小の点をxiとすると、xj < xi + r を満たす最大の点xjを常に塗れば良い
// 区間は塗るたびに単調に右に進んでいくため、単調性もあるし、区間x重複の有無は、区間スケジューリング問題と類似していることからも貪欲法と気付ける

int main() {
    int n, r; cin >> n >> r;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());

    int i = 0, ans = 0;
    // ループ内でiを進めたい時はforではなくwhileの方が良い
    while (i < n) {
        int s = a[i];
        // i=n-1が条件を満たさなかった場合でも、最後は処理をしたい場合などはif continueで外側のiteratorに任せるのではなく、
        // 内部で進める書き方をするといい
        while (i < n && s + r >= a[i]) i++;

        int t = a[i - 1];
        while (i < n && t + r >= a[i]) i++;
        ans++;
    }
    cout << ans << endl;
}
