// 文字列に対する動的計画法(単一文字列の場合): p327
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 文字列に関する問題のコツ
// - 前から逐次的に見ていくケースが多いのでdpが使えることが多い
// - 保持する必要がある範囲を見極めることで状態数を絞れる
// - 部分一致を考える問題は非常に多い
//   - dp[i][j] := iは走査線, jは部分一致制約に関する状態 と設計すると多くの場合うまくいく
//   - 単純な遷移ではない(1文字加えると部分列が+1 or リセット のような単純構造ではない)
//   - 遷移先の部分文字列は事前計算できる場合が多い

// 思考フロー
// 全探索だと無理 -> 前から逐次的に文字列Sとの一致を調べれば良いのでdpで考える
// -> i文字目まで見たときに末尾k文字がSと一致しているかを調べて、一致してないものの総数をカウントしていけば良い
// -> 末尾k個を保持すると4^(k-1)で状態数がまだ多すぎる -> 本当に保持する範囲がどこか改めて考える
// -> そもそもSの部分列になっている部分からのみ保持すればよく、部分列になってない部分は"*"と考えれば良いことがわかる
// -> dp[i][j] := i文字目まで見た時、末尾がSの先頭からj文字まで一致しているものの総数として、
//    dp[i+1][ti] += dp[i][j] (ti: jまで一致している状態から文字列cを加えた時にti文字目まで一致となる)
// -> tiは事前計算しておく

const int MOD = 10009;
const string atgc = "ATGC";
int n, k;
string S;
vector<vector<int>> nxt;

void prep() {
    nxt = vector<vector<int>>(k, vector<int>(4));
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < 4; j++) {
            string s = S.substr(0, i) + atgc[j];
            // sがSの先頭から何文字目まで一致しているか
            while (S.substr(0, s.length()) != s) {
                s = s.substr(1);
            }
            nxt[i][j] = s.length();
        }
    }
}

int main() {
    cin >> n >> k >> S;

    prep();

    vector<vector<int>> dp(n + 1, vector<int>(k));
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            for (int r = 0; r < 4; r++) {
                int ti = nxt[j][r];  // 先頭からj文字一致している状態で文字rを加えた時、先頭から何文字一致になるか
                if (ti == k) continue;  // Sが作れてしまうので除外
                dp[i + 1][ti] = (dp[i + 1][ti] + dp[i][j]) % MOD;
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < k; i++) ans = (ans + dp[n][i]) % MOD;
    cout << ans << endl;
}
