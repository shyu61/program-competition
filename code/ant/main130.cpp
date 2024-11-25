// Grundy数(Cutting Game): p283
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Nimは独立な部分集合が基本構造だが、部分集合が後から作られるパターンにも適用できる
// これは部分集合が作られるたびにtrackしてXORを順次取っていくことで対応できる
// すべての状態でのgrundyを保持する必要はなく、必要なのはあくまでもXORの結果だけということを利用している

// ゲーム問題まとめ
// 1. DPが使える構造か調べる
//   状態空間が比較的小さい,後ろから遷移できる
// 2. (物理的な)対称構造があるか
//   ミラーリング(後手が対称性を再構築する操作)が最適操作になることがある
// 3. (数理的な)対称構造があるか
//   Nimに帰着させる
//     - 複数の独立した部分集合から成ること
//     - 各部分集合を消費可能なリソースとみなせること
//     - 終了条件がリソースの完全消費に該当すること
//   操作に制約がある場合や、部分集合同士が完全な独立じゃない場合、部分集合が操作により増加する場合でも、grundy数を使うことでNimに帰着できる
// 4. その他法則性を見抜く
//   各操作の本質的な自由度(勝敗に影響を与えうる操作の自由度)を調べる
//   とにかく実験することが大事

vector<vector<int>> memo;

int grundy(int w, int h) {
    if (memo[w][h] != -1) return memo[w][h];

    set<int> s;
    for (int i = 2; w - i >= 2; i++) s.insert(grundy(i, h) ^ grundy(w - i, h));
    for (int i = 2; h - i >= 2; i++) s.insert(grundy(w, i) ^ grundy(w, h - i));

    int res = 0;
    while (s.count(res)) res++;
    return memo[w][h] = res;
}

int main() {
    int w, h; cin >> w >> h;
    memo = vector<vector<int>>(w + 1, vector<int>(h + 1, -1));
    cout << (grundy(w, h) != 0 ? "WIN" : "LOSE") << endl;
}
