#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int r, x; cin >> r >> x;
    bool ok = false;
    if (x == 1) {
        if (r >= 1600 && r <= 2999) ok = true;
    } else {
        if (r >= 1200 && r <= 2399) ok = true;
    }

    cout << (ok ? "Yes" : "No") << endl;
}
