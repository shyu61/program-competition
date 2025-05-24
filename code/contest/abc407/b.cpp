#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 🔷抑えるべき抽象論は？
// プログラムでは「少なくとも」は必ずしも余事象で考えないといけない訳ではない

int main() {
    int x, y; cin >> x >> y;
    int n = 6, c = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i + j >= x || abs(i - j) >= y) c++;
        }
    }
    double ans = double(c) / 36;
    cout << fixed << setprecision(10) << ans << endl;
}
