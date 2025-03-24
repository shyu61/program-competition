#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;

// ジャンル
// 逐次問題 + 影響が過去に及ぶタイプ
// => 過去全体は更新できないので、逆の比較対象側を更新し、新たにシミュレートするものにoffsetを加える

// 解けなかった理由
// 比較対象側を動かすというのを思いつくのに時間がかかった => 典型的な考え方なので抑える
// 比較対象側を動かした時に、新たにシミュレートするものにoffsetを加えれば良いことに気づくのに時間がかかった => 典型的な考え方なので抑える
// 新たにシミュレートするものに加えるoffsetの計算に手間取った
// => 比較対象側に加えられた値を初期値として加えれば、過去の影響を打ち消せる。
// => そもそも比較対象を動かしoffsetを加えるという発想は、「相対関係は変化させない」というのが根幹にある。これを理解している必要がある。
// 落ち着いて考察ができていない。しっかりジャンルを特定し、「何が障壁なのか」「どうやれば突破できるのか」を落ち着いて整理することが必要。

int main() {
    int n, r, c; cin >> n >> r >> c;
    string s; cin >> s;

    set<P> st;
    st.emplace(0, 0);
    int ri = 0, ci = 0;
    rep(i, n) {
        if (s[i] == 'N') ri++;
        if (s[i] == 'W') ci++;
        if (s[i] == 'S') ri--;
        if (s[i] == 'E') ci--;
        st.emplace(ri, ci);
        if (st.contains({r + ri, c + ci})) cout << 1;
        else cout << 0;
    }
}

int main() {
    int n, r, c; cin >> n >> r >> c;
    string s; cin >> s;

    vector<P> move(n);
    rep(i, n) {
        int dr = 0, dc = 0;
        if (s[i] == 'N') dr = -1;
        if (s[i] == 'W') dc = -1;
        if (s[i] == 'S') dr = 1;
        if (s[i] == 'E') dc = 1;
        move[i] = {dr, dc};
    }

    multiset<P> st;
    int ri = 0, ci = 0;
    for (int i = n - 1; i >= 0; i--) {
        ri += move[i].first;
        ci += move[i].second;
        st.emplace(ri, ci);
    }

    vector<int> ans(n);
    int mr = 0, mc = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (st.find({r + mr, c + mc}) != st.end()) ans[i] = 1;
        mr += move[i].first;
        mc += move[i].second;
        auto it = st.find({mr, mc});
        if (it != st.end()) st.erase(it);
    }

    rep(i, n) cout << ans[i];
    cout << endl;
}
