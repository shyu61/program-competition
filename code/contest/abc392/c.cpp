#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// ジャンル
// 射影

// 方針
// ゼッケンx ->r-> 人r[x] ->p-> 人p[r[x]] ->q-> ゼッケンq[p[r[x]]]
// ゼッケン_to_人 の射影関数が欲しくて、人_to_ゼッケン の射影関数はあるので、逆関数にすれば良い

// ポイント
// 射影はフロー図を描くと良い
// ある関数の逆射影は簡単に求めることができる

int main() {
    int n; cin >> n;
    vector<int> p(n), q(n);
    rep(i, n) cin >> p[i], p[i]--;
    rep(i, n) cin >> q[i], q[i]--;

    // 番号iをつけた人が誰か
    vector<int> r(n);
    rep(i, n) r[q[i]] = i;

    rep(i, n) {
        int human = r[i];
        int see = p[human];
        int bib = q[see];
        cout << bib + 1 << ' ';
    }
    cout << endl;
}
