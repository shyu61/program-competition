// ゲームと必勝法(A Funny Game): p273
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 対称構造を持つゲームでは相手の操作をミラーリングすることが最適操作になることがしばしばある
// 対称構造を持つゲーム: 円形,グラフ,文字列など
// -> 後手が対称性を保てるかを考えてみる

int main() {
    int n; cin >> n;
    cout << (n <= 2 ? "Alice" : "Bob") << endl;
}
