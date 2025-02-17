#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    string s, t; cin >> s >> t;
    if (s == "fine" && t == "fine") cout << 4 << endl;
    if (s == "fine" && t == "sick") cout << 3 << endl;
    if (s == "sick" && t == "fine") cout << 2 << endl;
    if (s == "sick" && t == "sick") cout << 1 << endl;
}
