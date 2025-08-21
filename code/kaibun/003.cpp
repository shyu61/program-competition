#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// https://atcoder.jp/contests/abc198/tasks/abc198_b

// 回文判定問題のうち、長さが可変のパターン
// 長さが不変なら中心も不変なので判定は容易だが、可変の場合は中心も変化するので一気に難しい
// 本問題は全探索できる

bool is_palindrome(deque<char>& deq) {
    int n = deq.size();
    rep(i, (n - 1) / 2 + 1) {
        if (deq[i] != deq[n - i - 1]) return false;
    }
    return true;
}

bool solve() {
    string s; cin >> s;
    int n = s.size();
    deque<char> deq;
    rep(i, n) deq.push_back(s[i]);
    if (is_palindrome(deq)) return true;

    rep(i, n) {
        deq.push_front('0');
        if (is_palindrome(deq)) return true;
    }
    return false;
}

int main() {
    if (solve()) cout << "Yes" << endl;
    else cout << "No" << endl;
}
