#include <bits/stdc++.h>
using namespace std;

int main() {
    string s; cin >> s;
    for (char c : s) {
        if (c == 'N') cout << 'S';
        if (c == 'S') cout << 'N';
        if (c == 'W') cout << 'E';
        if (c == 'E') cout << 'W';
    }
    cout << endl;
}
