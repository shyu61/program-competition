// Grundy数(コインのゲーム2): p281
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// grundy数の性質
// 各サブゲームの状態を数値化したもので、g(G)=0は負け確の状態を表す
// Nimにおける各山の石の個数と等価で、各サブゲームのgrundy数のXORを取ることでゲームの勝敗を知ることができる

// grundy数の本質
// 各サブゲームにおいて、最後の手番をどちらが取れるかを偶奇性を使って表現したもの
// XORは数理的な対称性を表現するもので、つまりは偶数性を表現している。ある1つのサブゲームが負け確(g(G)=0: つまり遷移先G'でg(G')=0がないので、自分の手番で終わらせることができない)でも全体として勝ち確になることはあって、
// それは全体として最後の手番をどちらが取れるかは全てのサブゲームの偶奇性の組み合わせによって決定するから。
// grundy数はNim値を抽象化していて、Nimのように任意の個数が取れない制約があるゲームでも、mexにより偶奇性が表現できる構造になっている
// 故に以下のようなケースもNimに帰着させることができる(+XORの結合則, 交換則を利用)
// - 操作に制約がある
// - サブゲーム数が動的

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
