// 二分探索木: p77
#include <bits/stdc++.h>
using namespace std;

// ポインタを使う場合の注意点
// 関数内で宣言したポインタ変数のスコープは関数内だけ。グローバルに保持したい場合はヒープメモリを使う必要がある
// 自動解放されないので忘れずに

// BSTの削除はいくつか考え方があるが一番明快なのは以下
// 1.対象がleftの場合 -> 削除するだけ
// 2.対象の子が1つの場合 -> その子をスライドする
// 3.対象の子が2つの場合 -> 左部分木の最大値を持ってくる(右部分木の最小値でもok)

const node *root = nullptr;

struct node {
    int val;
    node *lch, *rch;
};

// もちろんループでもかけるが、木構造の構築は再帰関数と相性がいい
// 再帰関数は戻り値をうまく使う
node *insert(node *p, int v) {
    if (p == nullptr) {
        node *q = new node{v};
        return q;
    }

    if (v < p->val) p->lch = insert(p->lch, v);
    else p->rch = insert(p->rch, v);

    return p;
}

bool find(node *p, int v) {
    if (p == nullptr) return false;
    if (v == p->val) return true;
    if (v < p->val) return find(p->lch, v);
    return find(p->rch, v);
}

// ノードの削除はポインタの貼り替え漏れに注意する
// 移動元での貼り替えと移動先での貼り替えをそれぞれ考えると良い
node* remove(node *p, int v) {
    // まずremoveするノードを探索する
    if (p == nullptr) return nullptr;
    if (v == p->val) {
        // 左部分木がない場合は右部分木をスライドさせる
        if (p->lch == nullptr) {
            node *q = p->rch;
            delete p;
            return q;
        }
        // 左部分木が右部分木を持たない場合は直下の左の子が最大値になるので、左部分木をスライドさせる
        if (p->lch->rch == nullptr) {
            node *q = p->lch;
            q->rch = p->rch;
            delete p;
            return q;
        }
        // それ以外の場合は、左部分木の内、最大のleftを採用
        node *q;
        for (q = p->lch; q->rch->rch != nullptr; q->rch);
        node *r = q->rch;
        // rをpの位置に移動させる、そのためにrから生える枝をqに付け替える
        // 移動元での貼り替え
        q->rch = r->lch;
        // 移動先での貼り替え
        r->lch = p->lch;
        r->rch = p->rch;
        delete p;
        return r;
    } else if (v < p->val) p->lch = remove(p->lch, v);
    else p->rch = remove(p->rch, v);
    return p;
}
