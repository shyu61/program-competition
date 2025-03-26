#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// ジャンル
// 回文, 接頭辞, 接尾辞
// suffixの最長回文を求める問題
// prefixに関する制約をsuffix制約に置き換えることで問題を簡略化させる問題

// ポイント
// prefix,suffix制約はお互い逆を考えることができ、問題をシンプルにできる可能性がある
// 文字列操作系アルゴリズムは確認しておく
// - kmp, manacher, z-algorithm, lcp, sa, rolling-hash, trie

vector<int> z_algorithm(const string &s) {
    vector<int> a(s.size());
    a[0] = s.size();
    int i = 1, j = 0;
    while (i < s.size()) {
        while (i + j < s.size() && s[j] == s[i + j]) j++;
        a[i] = j;
        if (j == 0) {
            i++;
            continue;
        }
        int k = 1;
        while (i + k < s.size() && k + a[k] < j) {
            a[i + k] = a[k];
            k++;
        }
        i += k; j -= k;
    }
    return a;
}

int main() {
    string s; cin >> s;
    int n = s.size();

    string t = s;
    reverse(t.begin(), t.end());
    t += s;
    vector<int> a = z_algorithm(t);

    rep(i, n) {
        // 後半を見る
        if (a[n + i] == n - i) {
            string x = s.substr(0, i);
            reverse(x.begin(), x.end());
            cout << s << x << endl;
            return 0;
        }
    }
}

vector<int> manacher(const string &s) {
    vector<int> a(s.size());
    int i = 0, j = 0;
    while (i < s.size()) {
        while (i - j >= 0 && i + j < s.size() && s[i - j] == s[i + j]) j++;
        a[i] = j;
        int k = 1;
        while (i - k >= 0 && k + a[i - k] < j) {
            a[i + k] = a[i - k];
            k++;
        }
        i += k; j -= k;
    }
    return a;
}

int main() {
    string s; cin >> s;
    int n = s.size();

    string t = "$";
    rep(i, n) {
        t += s[i];
        t += '$';
    }
    vector<int> a = manacher(t);

    int k = 0;
    rep(i, a.size()) {
        if (i + a[i] >= a.size()) {
            k = (i - a[i] + 1) / 2;
            break;
        }
    }

    string ans = s;
    rep(i, k) ans += s[k - 1 - i];
    cout << ans << endl;
}
