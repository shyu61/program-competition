#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    string s; cin >> s;
    int n = s.size();
    int i = 0;
    while (i < n - 1) {
        if (s.substr(i, 2) == "WA") {
            s[i] = 'A';
            s[i + 1] = 'C';
            if (i > 0) i--;
        } else i++;
    }
    cout << s << endl;
}
