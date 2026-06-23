#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;

bool is_palindrome(string s) {
    string t = s;
    reverse(t.begin(), t.end());
    return s == t;
}

int main() {
    string s; cin >> s;
    int n = s.size();

    string a = s.substr(0, (n-1)/2);
    string b = s.substr((n+3)/2-1);

    if (is_palindrome(s) && is_palindrome(a) && is_palindrome(b)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
