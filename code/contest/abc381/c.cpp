#include <bits/stdc++.h>
using namespace std;

// ポイント
// 線形スキャンで配列外参照を防ぐ方法の一つに番兵法がある

int main() {
    int n; string s; cin >> n >> s;
    s = '$' + s + '$';
    n = s.size();

    int maxv = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '/') {
            int d = 1;
            while (s[i - d] == '1' && s[i + d] == '2') d++;
            maxv = max(maxv, d * 2 - 1);
        }
    }
    cout << maxv << endl;
}
