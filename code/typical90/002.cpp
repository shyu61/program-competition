#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// ジャンル
// bit全探索

// ポイント
// `vector<char>`で書けるものなら`string`にした方が良い

int main() {
    int n; cin >> n;
    if (n % 2 != 0) return 0;

    int n2 = 1 << n;
    for (int s = n2 - 1; s >= 0; s--) {
        string ans = "";
        int cnt = 0;
        for (int i = n - 1; i >= 0; i--) {
            (s >> i & 1) ? cnt++ : cnt--;
            if (cnt < 0) break;
            ans += (s >> i & 1) ? '(' : ')';
        }
        if (cnt == 0) cout << ans << '\n';
    }
}
