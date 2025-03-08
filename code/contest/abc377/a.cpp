#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    string s; cin >> s;
    sort(s.begin(), s.end());
    if (s == "ABC") cout << "Yes" << endl;
    else cout << "No" << endl;
}
