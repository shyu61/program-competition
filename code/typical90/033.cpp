#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int h, w; cin >> h >> w;

    if (h == 1 || w == 1) {
        cout << h * w << endl;
        return 0;
    }

    // 切り上げ除算
    int hi = (h - 1 + 2) / 2;
    int wi = (w - 1 + 2) / 2;

    cout << hi * wi << endl;
}
