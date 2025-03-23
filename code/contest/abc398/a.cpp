#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int n; cin >> n;
    string s(n, '-');
    if (n % 2 == 0) {
        s[n / 2] = '=';
        s[n / 2 - 1] = '=';
    } else s[n / 2] = '=';

    cout << s << endl;
}
