#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using mint = atcoder::modint998244353;

// 🔷初見でどうやったら解けるか
// 確率/期待値の問題は、dpか組み合わせ論かの2つに大別される。
// 逐次的な操作により累積的に確率/期待値が変化していく場合はdp、操作に時差がなく全て同時に実行される場合は組み合わせ論的に解いていく。
// 本問題は明らかに後者。組み合わせ論と数え上げは非常に近いことを念頭に置くと、
// あるサイコロの目Aijがmaxになる通り数がそれぞれどれだけあるかを求める問題になる。考え方としては主客転倒に近い(期待値における主客転倒は、期待値の線形性の利用とみなせる)。
// Aijがmaxになるなら、他のサイコロの目は全てAij以下である。これを「集合」と「条件」で一旦整理すると、
// 全てのサイコロの出目がAij以下の集合において、少なくとも1つAijが出る確率を求める問題に帰着できる。
// 明らかに余事象であり、sortして読んでいくと各集合の確率は累積的に計算できそうとわかる。

// 🔷抑えるべき抽象論は？
// 確率問題では、maxが何かの値に一致する確率を求めるより、maxが何かの値以下になる確率を求める方が遥かに簡単
// - 故に余事象を使う
// 確率/期待値の問題は、dpか組み合わせ論かの2つに大別される
// - 組み合わせ論の解き方
//   - まず「集合」と「条件」を数学的に解釈する
//   - P,C,余事象,包除原理,(dp) などの手法のどれを使うか検討する

int main() {
    int n; cin >> n;
    vector<vector<int>> a(n, vector<int>(6));
    rep(i, n) rep(j, 6) cin >> a[i][j];

    // {サイコロの目: サイコロ番号}
    map<int, vector<int>, greater<>> mp;
    rep(i, n) {
        unordered_set<int> st(a[i].begin(), a[i].end());
        for (auto v : st) mp[v].push_back(i);
    }

    mint ans = 0, now = 1;  // 全てk以下の確率(初期はk=INF)
    for (auto& [k, v] : mp) {
        // E(k) = (全てk以下の確率 - 全てk未満の確率) * k;
        // 全てk未満の確率を計算
        mint p = now;
        for (auto i : v) {
            // サイコロiにおいて、k以下の確率とk未満の確率
            int c1 = 0, c2 = 0;
            rep(j, 6) {
                if (a[i][j] <= k) c1++;
                if (a[i][j] < k) c2++;
            }
            p *= (6 / mint(c1)) * (mint(c2) / 6);
        }
        // 期待値計算
        ans += k * (now - p);
        swap(now, p);
    }

    cout << ans.val() << endl;
}
