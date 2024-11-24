// Grundy数(コインのゲーム2): p281
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// grundy数は各状態を数値化したもので、Nimの各山の石の個数と等価でありXOR演算することができる
// 様々なゲーム問題をNimに帰着させることができる
// - 操作に制約がある
// - 部分集合が完全には独立ではない

int main() {
    int n, k; cin >> n >> k;
    vector<int> A(k), X(n);
    for (int i = 0; i < n; i++) cin >> A[i];
    for (int i = 0; i < n; i++) cin >> X[i];

    vector<int> grundy(n + 1);
    // 0で自分に回ってきたら負け
    grundy[0] = 0;

    // grundy数を計算
    int maxx = *max_element(X.begin(), X.end());
    for (int i = 1; i <= maxx; i++) {
        set<int> s;
        for (int j = 0; j < k; j++) {
            if (A[j] <= i) s.insert(grundy[i - A[j]]);
        }

        int g = 0;
        while (s.count(g) != 0) g++;
        grundy[i] = g;
    }

    // 勝敗を判定
    int x = 0;
    for (int i = 0; i < n; i++) x ^= grundy[X[i]];

    cout << (x != 0 ? "Alice" : "Bob") << endl;
}
