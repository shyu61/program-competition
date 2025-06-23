#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using TP = tuple<int, int, string>;

// 🔷初見でどうやったら解けるか
// まずはどこがボトルネックかを考える。文字列のcopyがボトルネックなので、type=1,3クエリでの置き換えで、
// 文字列をcopyしない方法をとる必要がある。
// 文字列の代わりにpc番号を使うのが最も素直だが、参照元の文字列が動的に変化するのでややこしそう。
// 欲しいのがある一点の最終状態のみであることに注目すると、関係ある部分だけ再帰的にトラックすれば良いことがわかる。

// 🔷抑えるべき抽象論は？
// n文字のcopyはO(n)かかる
// "+"と"+="は計算量が違う
// クエリ問題や逐次問題はdpの側面を持っている
// - 最終状態のみ問われる場合は、逆順や再帰なども選択肢になる
// - トラックする状態数を絞りたい場合は再帰が有効

int main() {
    int n, q; cin >> n >> q;
    vector<TP> qs(q);
    rep(i, q) {
        int t, p; cin >> t >> p, p--;
        string s = "";
        if (t == 2) cin >> s;
        qs[i] = {t, p, s};
    }

    int tp = -1;
    vector<string> ans;
    for (int i = q - 1; i >= 0; i--) {
        auto& [t, p, s] = qs[i];
        if (tp == -1) {
            if (t == 3) tp = p;
        } else {
            if (tp == p) {
                if (t == 1) tp = -1;
                if (t == 2) ans.push_back(s);
            }
        }
    }

    for (int i = ans.size() - 1; i >= 0; i--) cout << ans[i];
    cout << endl;
}
