#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// パリティの類問
// https://atcoder.jp/contests/abc124/tasks/abc124_c

// 数学的考察を要する問題のコツはいくつかあるが、パリティが絡むのもその典型
// パリティが絡む問題の傾向としては
// - 交互, 反転, 01の変化, グリッド(2次元)操作などが多い

int main() {
    string s; cin >> s;
    int n = s.size();

    auto f = [&](int x) {
        int x2 = x ^ 1, res = 0;
        rep(i, n) {
            if (i % 2 == x && s[i] == '0') res++;
            if (i % 2 == x2 && s[i] == '1') res++;
        }
        return res;
    };

    cout << min(f(0), f(1)) << endl;
}
