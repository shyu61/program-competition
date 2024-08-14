// 最大公約数: ユークリッド互除法
#include <iostream>
using namespace std;

int solve(int x, int y) {
    if (x < y) swap(x, y);

    int r;
    while (y > 0) {
        r = x % y;
        x = y; y = r;
    }
    return x;
}

int main() {
    int x, y;
    cin >> x >> y;
    cout << solve(x, y) << endl;
}
