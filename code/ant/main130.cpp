// Grundy数(Cutting Game): p283
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Nimは独立な部分集合が基本構造だが、部分集合が後から作られるパターンにも適用できる
// これは部分集合が作られるたびにtrackしてXORを順次取っていくことで対応できる
// すべての状態でのgrundyを保持する必要はなく、必要なのはあくまでもXORの結果だけということを利用している

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
