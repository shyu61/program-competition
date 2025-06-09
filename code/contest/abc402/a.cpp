#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    string s; cin >> s;
    for (auto c : s) {
        if (isupper(c)) cout << c;
    }
    cout << endl;
}
