// 最大公約数: 合成数の性質を使った解法
#include <iostream>
#include <set>
#include <stdexcept>
using namespace std;

int solve(int x, int y) {
    if (x > y) swap(x, y);

    // xの約数を調べる
    set<int> x_cd;
    for (int i = 1; i * i <= x; i++) {
        if (x % i == 0) {
            x_cd.insert(i);
            x_cd.insert(x / i);
        }
    }

    // yとの公約数を調べる
    for (auto it = x_cd.rbegin(); it != x_cd.rend(); it++) {
        if (y % *it == 0) return *it;  // 1が入ってるので必ずreturnされる
    }

    throw runtime_error("common divisor not found");
}

int main() {
    int x, y;
    cin >> x >> y;
    cout << solve(x, y) << endl;
}
