#include <bits/stdc++.h>
using namespace std;

int main() {
    string s; cin >> s;
    int a1 = 0, a2 = 0, a3 = 0;
    for (auto c : s) {
        if (c == '1') a1++;
        if (c == '2') a2++;
        if (c == '3') a3++;
    }

    if (a1 == 1 && a2 == 2 && a3 == 3) cout << "Yes" << endl;
    else cout << "No" << endl;
}
