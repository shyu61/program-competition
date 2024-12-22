// 文字列に対する動的計画法(複数文字列の場合): p329
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 解法
// 文字列Sに対して部分一致を調べたい文字列Piが複数ある場合の問題(P={P1,P2,...Pn})
// 各Piをprefixで分解して、完全一致として扱う
// <= 単一文字列Tの問題の場合はTの何文字目まで一致するかで考えたが、これはprefix分解して複数の文字列に対しての完全一致を扱うことと同値
// 単一マッチの場合と同様に遷移後に何文字マッチになるか(=どのprefixになるか)を事前計算する

// 思考フロー
// 文字列Sに対する部分文字列Tの部分一致問題 -> dp[i][j]:=Sをi文字目まで走査した時のマッチ度j の枠組みが使える可能性高い
// -> 部分文字列が複数あるケース -> ループすると間に合わないので、単一文字列のケースに帰着できないか？
// -> 単一文字列の場合もjはそれぞれのprefixを考えていていわば複数の部分文字列との完全一致を調べている -> じゃあ複数文字列もprefix分解すれば全く同様にdpできる
// -> 目的は「禁止文字を含まないように修正する最小回数」なので、dp[i]:=Sのi文字目まで見たときに禁止文字を含まないための最小回数とまず考える。
// -> このままでは遷移が記述できない。直前の文字列の状態がわからないと遷移できない。また単一文字列の時もdp[i][j]として文字列の一致の状態をjで管理していたので今回も同様にしてみる
// -> そうするとdp[i][j]:=「Sのj文字目まで見た時に、prefix jと一致するための最小修正回数」となる。
// -> ここまでくれば、あとはdp[S.length()]まで見たときに、禁止文字以外の状態jになった場合のdpの値のうち最小を取れば良い

// 個数制限付きナップサックdpの2進法による解法と似ている
// 本来は別々に扱わないといけない集合の各要素をある基準で分解することで、全てが対象で同一処理できる形に帰着させる => 単一の場合と同様に扱える

// 本DPはtrie木上のDPである
// dp[i][j]のjはprefixのことなので、trie木上のノードを表す
// しかし新たな文字が追加された時の遷移先は、現在のノードの子とは限らないのでいずれにせよ事前計算が必要になる

// 文字列検索でDPを使うシーン
// 文字列Sの中に文字列Tを探す問題は非常に多い。基本はrolling hashやsaを使うのが高速だが、以下のケースではdpを使う必要がある
// - 文字列が生成的
//   - 生成パターンが多すぎてそもそも文字列Sを用意できない
// - 部分一致を扱う必要がある
// - 一致に制約条件がついている
//   - 複数個のうちのどれかとか、何回含まない解けないとか

const string atgc = "ATGC";
const int INF = 1e9;
string S;
vector<string> P;
vector<vector<int>> nxt;
vector<bool> ng;

int prep(int n) {
    // prefix分解
    vector<string> pfx;
    for (auto s : P) {
        for (int i = 0; i <= s.length(); i++) {
            pfx.push_back(s.substr(0, i));
        }
    }
    sort(pfx.begin(), pfx.end());
    pfx.erase(unique(pfx.begin(), pfx.end()), pfx.end());

    int K = pfx.size();  // dp[i][j]で調べるprefix jは全部でK個
    nxt = vector<vector<int>>(K, vector<int>(4));  // nxt[j][c]:=prefix jにcを加えると何番目のprefixと一致するか
    ng = vector<bool>(K);
    for (int i = 0; i < K; i++) {
        ng[i] = false;
        for (auto s : P) {
            // prefix sが完全なPiを含んでいる場合は遷移できない状態
            int len = s.length();
            // 末尾での一致を調べれば十分
            // 先頭部分で一致する場合は同じPiに対するより短いprefixが一致するため、ここでは末尾で新たにngになるかどうかだけ調べれば良い
            ng[i] = ng[i] || (len <= pfx[i].length() &&
                     pfx[i].substr(pfx[i].length() - len, len) == s);
        }
        for (int r = 0; r < 4; r++) {
            string s = pfx[i] + atgc[r];
            // 先頭から1文字ずつ削りつつ一致する文字列が状態にあればそれが移動先の状態
            int k;
            while (1) {
                k = lower_bound(pfx.begin(), pfx.end(), s) - pfx.begin();
                if (k < K && pfx[k] == s) break;  // k番目のprefixとsが完全一致
                s = s.substr(1);
            }
            nxt[i][r] = k;  // prefix iにrを加えるとprefix kになる(k>=Kなら該当なし)
        }
    }
    return K;
}

int main() {
    int n; cin >> n;
    P = vector<string>(n);
    for (int i = 0; i < n; i++) cin >> P[i];
    cin >> S;

    int K = prep(n);

    // dp[i][j]:=Sのi文字目までを見た時、prefix分解した集合のj番目のものと一致させるために必要な最小変更回数
    vector<vector<int>> dp(S.length() + 1, vector<int>(K));
    dp[0][0] = 1;
    for (int i = 0; i < S.length(); i++) {
        for (int j = 0; j < K; j++) dp[i + 1][j] = INF;
        for (int j = 0; j < K; j++) {
            if (ng[j]) continue;
            for (int r = 0; r < 4; r++) {
                int ti = nxt[j][r];  // prefix jに完全マッチしている状態からrを加えるとprefix tiになる
                dp[i + 1][ti] = min(dp[i + 1][ti], dp[i][j] + (S[i] == atgc[r] ? 0 : 1));
            }
        }
    }

    int ans = INF;
    for (int i = 0; i < K; i++) {
        if (ng[i]) continue;
        // 最終的に(dp[S.length()]の状態)ng以外の状態にする場合の最小変更回数を求める
        ans = min(ans, dp[S.length()][i]);
    }
    cout << (ans == INF ? -1 : ans) << endl;
}
