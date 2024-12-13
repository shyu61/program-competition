#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

// ローリングハッシュ法, Rabin-Karp法
// ポイント
// 核は文字列の一致判定をO(1)でするためにハッシュを使うこと
// また、ハッシュ計算を効率的に行うためにローリングハッシュを使い、最初のm文字の計算(O(m))以降はO(1)で計算している
// 基数を十分大きくとることで、衝突確率を限りなく小さくしている(累乗が1つ違うだけで値が大きく異なる)

// 利用シーン
// 文字列検索(完全一致)。部分一致は扱えない

const ull B = 100000007;  // ハッシュの基数

// aはbに含まれているか？
bool contain(string a, string b) {
    int al = a.length(), bl = b.length();
    if (al > bl) return false;

    // Bのal乗を計算
    ull t = 1;
    for (int i = 0; i < al; i++) t *= B;

    // aとbの最初のal文字に関するハッシュ値を計算
    ull ah = 0, bh = 0;
    for (int i = 0; i < al; i++) ah = ah * B + a[i];
    for (int i = 0; i < al; i++) bh = bh * B + b[i];

    // bの場所を1つずつ進めながらハッシュ値をチェック
    for (int i = 0; i + al <= bl; i++) {
        if (ah == bh) return true;  // bのi文字目からのal文字が一致
        if (i + al < bl) bh = bh * B + b[i + al] - b[i] * t;
    }
    return false;
}

// aの末尾とbの先頭を何文字重ねることができるか
int overlap(string a, string b) {
    int al = a.length(), bl = b.length();
    int res = 0;
    ull ah = 0, bh = 0, t = 1;
    for (int i = 1; i <= min(al, bl); i++) {
        // ahは後ろからなので、初項がB^0になる
        ah = ah + a[al - i] * t;  // aの末尾i文字のハッシュ値
        // bhは通常通りなので、初項はB^iになる
        bh = bh * B + b[i - 1];  // bの先頭i文字のハッシュ値
        if (ah == bh) res = i;
        t *= B;
    }
    return res;
}
