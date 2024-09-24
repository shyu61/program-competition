// 貪欲法: 辞書順最小の問題: p45
#include <bits/stdc++.h>
using namespace std;

// 辞書順の問題は貪欲法を使うケースが多い
// その他、prefixやtrie木、LCPなど絡むケースが多い

int main() {
    int n; cin >> n;
    string s; cin >> s;

    string ans;
    int l = 0, r = n - 1;
    for (int i = 0; i < n; i++) {
        // 最後までs[left]==s[right]だった場合はs[left]を先にとる
        bool is_left = true;
        int nl = l, nr = r;
        // s[left]==s[right]の場合は掘り続ける
        while (nl > nr) {
            if (s[nl] < s[nr]) {
                is_left = true;
                break;
            } else if (s[nr] < s[nl]) {
                is_left = false;
                break;
            }
            nl++; nr--;
        }

        if (is_left) ans.push_back(s[l++]);
        else ans.push_back(s[r--]);
    }

    cout << ans << endl;
}
