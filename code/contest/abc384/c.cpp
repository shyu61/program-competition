#include <bits/stdc++.h>
using namespace std;
using P = pair<int, string>;

// sortの順序を制御する方法
// - カスタムコンパレータを使う
// - 符号を反転させる

const int N = 5;

int main() {
    vector<int> a(N);
    for (int i = 0; i < N; i++) cin >> a[i];

    vector<P> res;
    for (int i = 1; i < 1 << N; i++) {
        int score = 0; string name;

        for (int j = 0; j < N; j++) {
            if (i >> j & 1) {
                score += a[j];
                name += "ABCDE"[j];
            }
        }
        res.emplace_back(-score, name);
    }

    sort(res.begin(), res.end());
    for (auto [score, name] : res) cout << name << endl;
}
