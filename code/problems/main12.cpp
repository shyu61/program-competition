// D - Avoid K Palindrome
// https://atcoder.jp/contests/abc359/tasks/abc359_d
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

bool isPalindrome(string s) {
    string ns = s;
    reverse(ns.begin(), ns.end());
    return ns == s;
}

vector<char> options = {'A', 'B'};

int main() {
    int n, k; string s;
    cin >> n >> k >> s;

    map<string, mint> dp;
    dp[""] = 1;
    for (int i = 0; i < n; i++) {
        map<string, mint> prev;
        swap(prev, dp);

        for (auto [t, num] : prev) {
            for (int j = 0; j < options.size(); j++) {
                if (s[i] != '?' && s[i] != options[j]) continue;
                string nt = t + options[j];
                if (nt.size() == k && isPalindrome(nt)) continue;
                if (nt.size() == k) nt.erase(nt.begin());
                dp[nt] += num;
            }
        }
    }

    mint ans = 0;
    for (auto [t, num] : dp) ans += num;

    cout << ans.val() << endl;
}
