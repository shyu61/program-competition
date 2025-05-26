#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// https://atcoder.jp/contests/abc181/tasks/abc181_d

// 🔷抑えるべき抽象論は？
// 通り数が少ないようなケースや分岐では、網羅的に見たりデータ構造を使ったりするより、具体的に場合分けをして手動で数えたほうが早いケースも多い。
// 頻度配列同士の個数比較は、プラスで比較するよりマイナスして0以上か判定する方が分かりやすい。

bool solve() {
    string s; cin >> s;
    int n = s.size();
    if (n == 1) return s == "8";
    if (n == 2) {
        if (stoi(s) % 8 == 0) return true;
        swap(s[0], s[1]);
        return stoi(s) % 8 == 0;
    }

    vector<int> cnt(10);
    for (auto c : s) cnt[c - '0']++;
    for (int i = 112; i < 1000; i += 8) {
        vector<int> now = cnt;
        for (auto c : to_string(i)) now[c - '0']--;

        bool ok = true;
        rep(j, 10) {
            if (now[j] < 0) ok = false;
        }
        if (ok) return true;
    }
    return false;
}

int main() {
    if (solve()) cout << "Yes" << endl;
    else cout << "No" << endl;
}

