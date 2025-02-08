#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
const int INF = 1001001001;

// ジャンル
// subseq問題

// 方針
// 辞書順で最小なので、常にprefixは選択範囲内での最小文字を選べばよく、複数ある場合はindexが小さいものの方が有利である
// 故に区間最小問題になる。末尾に残り文字数を取れるだけは残した区間で最小文字を高速に探索できればよく、segtreeやスライド最小化が選択肢

// ポイント
// - 辞書順最小は前から貪欲
// - "貪欲"に取りたい場合は位置配列が有効
// - 文字列問題は、文字種に関しては全探索できるケースが多い

int main() {
    int n, k; string s; cin >> n >> k >> s;

    string ans = "";
    deque<pair<char, int>> deq;
    rep(i, n) {
        while (!deq.empty() && deq.back().first > s[i]) deq.pop_back();
        deq.emplace_back(s[i], i);

        if (i > n - k + int(ans.size()) - 1) {
            auto [c, j] = deq.front();
            ans += c;
            if (ans.size() == k) break;
            deq.pop_front();
            while (!deq.empty() && deq.back().second <= j) deq.pop_front();
        }
    }

    cout << ans << endl;
}

// 位置配列を使う解法
int main() {
    int n, k; string s; cin >> n >> k >> s;

    vector<vector<int>> nx(n, vector<int>(26, INF));
    for (int i = n - 1; i >= 0; i--) {
        if (i < n - 1) nx[i] = nx[i + 1];
        nx[i][s[i] - 'a'] = i;
    }

    string ans = "";
    int cur = 0;
    rep(i, k) {
        rep(j, 26) {
            if (nx[cur][j] + (k - i) - 1 < n) {
                ans += char(j + 'a');
                cur = nx[cur][j] + 1;
                break;
            }
        }
    }
    cout << ans << endl;
}
