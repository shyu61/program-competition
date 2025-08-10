#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int n; string s; cin >> n >> s;
    if (n >= 3 && s.substr(n - 3) == "tea") cout << "Yes" << endl;
    else cout << "No" << endl;
}
