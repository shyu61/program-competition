#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int n, a, b; cin >> n >> a >> b;
    string s; cin >> s;
    for (int i = a; i < n - b; i++) cout << s[i];
    cout << endl;
}

// substr(0-indexed-pos, 個数)
int main() {
    int n, a, b; cin >> n >> a >> b;
    string s; cin >> s;
    s = s.substr(a, n - a - b);
    cout << s << endl;
}
