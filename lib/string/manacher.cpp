#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 文字iを中心とする最長の回文半径: O(|s|)
// 回文の中に回文がある場合、反対側にも同じ回文が現れることを利用する
vector<int> manacher(const string &s) {
    vector<int> a(s.size());
    int i = 0, j = 0;
    while (i < s.size()) {
        // 愚直に回文半径を求める
        while (i - j >= 0 && i + j < s.size() && s[i - j] == s[i + j]) j++;
        a[i] = j;
        // iを中心とする回文内に完全に含まれる回文(k+a[i-k]<j)について、反対側に同様の半径を記録し計算を省略する
        int k = 1;
        while (i - k >= 0 && k + a[i - k] < j) {
            a[i + k] = a[i - k];
            k++;
        }
        i += k; j -= k;
    }
    return a;
}
