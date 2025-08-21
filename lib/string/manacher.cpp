#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 文字iを中心とする最長の回文半径: O(|s|)
// 回文の中に回文がある場合、反対側にも同じ回文が現れることを利用する
vector<int> manacher_with_description(const string &s) {  // sは'#'などを間に入れた2倍列を想定する
    int n = s.size();
    vector<int> rad(n);  // 偶奇によらず rad[i]-1 がiを中心とする回文の回文長になる
    int i = 0, d = 0;
    while (i < n) {
        // iを中心として、前回から引き継いだ半径dからさらに伸ばせるか試す
        while (d <= i && i + d < n && s[i - d] == s[i + d]) d++;
        rad[i] = d;

        // iを中心とする回文内に完全に含まれる回文(k+a[i-k]<j)について、反対側に同様の半径を記録し計算を省略する
        int k = 1;
        // iより左にあり、かつその半径がrad[i]に完全に含まれるものを求め、逆側にミラーリングする
        while (k <= i && k + rad[i - k] < d) {
            rad[i + k] = rad[i - k];
            k++;
        }
        i += k; d -= k;
    }
    return rad;
}

vector<int> manacher(const string &s) {
    int n = s.size();
    vector<int> rad(n);
    int i = 0, d = 0;
    while (i < n) {
        while (d <= i && i + d < n && s[i - d] == s[i + d]) d++;
        rad[i] = d;

        int k = 1;
        while (k <= i && k + rad[i - k] < d) {
            rad[i + k] = rad[i - k];
            k++;
        }
        i += k; d -= k;
    }
    return rad;
}
