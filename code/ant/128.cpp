// Nim(Georgia and Bob): p278
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Nimへの帰着を検討すべき問題
// - 複数の独立した部分集合から成る場合
// - 各部分集合を操作可能なリソースとみなせること
// - 終了条件がリソースが尽きることに該当すること

int main() {
    int n; cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];

    sort(p.begin(), p.end());

    int x = 0;
    for (int i = 0; i + 1 < n; i += 2) {
        // 2駒間の距離を石の数と考えてNimに帰着
        x ^= (p[i + 1] - p[i] - 1);
    }
    if (n % 2 == 1) x ^= p[0] - 1;

    cout << (x != 0 ? "Georgia will win" : "Bob will win") << endl;
}
