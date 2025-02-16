#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    string s, t; cin >> s >> t;
    if (s == "sick" && t == "fine") cout << 2 << endl;
    else if (s == "fine" && t == "sick") cout << 3 << endl;
    else if (s == "sick" && t == "sick") cout << 1 << endl;
    else cout << 4 << endl;
}
