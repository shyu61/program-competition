#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// https://atcoder.jp/contests/agc020/tasks/agc020_a

// 不変量: 駒間の距離(B-A-1)のパリティ

int main() {
    int n, a, b; cin >> n >> a >> b;
    int d = b - a - 1;
    if (d % 2 == 0) cout << "Borys" << endl;
    else cout << "Alice" << endl;
}
