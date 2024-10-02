// 辞書順の最小問題: p45
#include <bits/stdc++.h>
using namespace std;

// 現在の位置の文字に対する辞書順は、前の文字の影響を受けないため、
// 貪欲法で常に先頭か末尾の内、辞書順で早い方を選択し続ければ良い。
// ただし、同じ文字だった場合は次の文字を比較していく

// 辞書順処理は局所最適性が成立する典型的なパターン
// 模範解答の書き方は面白くて、いわゆるi=0で成立するパターンもinner-loopにまとめてしまっている。
// 本来i=0の場合はわざわざーループする必要はないが、このようにまとめて書くこともできる

// 内側のwhileはなんのために実行する? => leftかrightかどっちを使うかを判定したい => `bool left`さえわかれば十分
// 欲張ってpushまで書かずに、目的に立ち返ってできるだけシンプルに記述するとミスが減る

int main() {
    int n;
    string s;
    cin >> n >> s;

    string ans;
    int l = 0, r = n - 1;
    while (l <= r) {
        bool left = true;
        int nl = l, nr = r;
        while (nl <= nr) {
            if (s[nl] < s[nr]) break;
            else if (s[nl] > s[nr]) {
                left = false;
                break;
            }
            nl++; nr--;
        }
        if (left) ans.push_back(s[l++]);
        else ans.push_back(s[r--]);
    }

    cout << ans << endl;
}

// 別の書き方
// int main() {
//     int n;
//     string s;
//     cin >> n >> s;

//     string ans;
//     int l = 0, r = n - 1;
//     while (l < r) {
//         if (s[l] < s[r]) ans.push_back(s[l++]);
//         else if (s[l] > s[r]) ans.push_back(s[r--]);
//         else {
//             int nl = l, nr = r;
//             while (nl < nr) {
//                 if (s[nl] < s[nr]) {
//                     ans.push_back(s[l++]);
//                     break;
//                 } else if (s[nl] > s[nr]) {
//                     ans.push_back(s[r--]);
//                     break;
//                 }
//                 nl++; nr--;
//             }
//         }
//     }
//     ans.push_back(s[l]);

//     cout << ans << endl;
// }
