#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// ジャンル
// 確率, 数え上げ

// 方針
// 条件を満たすカードの組みを数え上げる問題。カードの組み合わせは81通りしかないので全探索できる
// 各組み合わせを取れる場合の数は1つではなく残り枚数に依存するので、組み合わせのループ内で場合の数の合計をカウントアップしていけば良い。

// ポイント
// 変に問題を分割計算しない。定数倍で遅くなる実装は最初はほぼ気にしなくて良い。
//「一様性の仮定」を疑うこと
//   - 重複や同一性がある場合は特に注意
//   - dpを使う問題など、操作結果が状態に依存する問題も一様性が成立しない典型

int main() {
    int k; string s, t; cin >> k >> s >> t;
    vector<int> cnt(10, k);
    cnt[0] = 0;
    rep(i, 4) cnt[s[i] - '0']--;
    rep(i, 4) cnt[t[i] - '0']--;

    auto f = [&](string s) -> ll {
        vector<int> a(10);
        for (char c : s) a[c - '0']++;
        ll res = 0;
        for (int i = 1; i <= 9; i++) {
            int x = 1;
            rep(j, a[i]) x *= 10;
            res += i * x;
        }
        return res;
    };

    ll wins = 0;
    // 裏のカードの組み合わせを全探索
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            s[4] = i + '0';
            t[4] = j + '0';
            if (f(s) > f(t)) {
                // 各組み合わせの出現確率は一様ではなく、残り枚数に依存する
                if (i == j) wins += ll(cnt[i]) * (cnt[i] - 1);
                else wins += ll(cnt[i]) * cnt[j];
            }
        }
    }

    ll total = ll(9 * k - 8) * (9 * k - 9);
    cout << fixed << setprecision(12) << double(wins) / total << endl;
}
