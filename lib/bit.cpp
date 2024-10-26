#include <bits/stdc++.h>
using namespace std;

// BIT(binary-indexed-tree)は累積和のクエリと更新を高速(O(logn))に処理できる
// セグ木の簡略化版で、累積和は常に0からの区間の差で表現できることを利用して、セグ木から不要なノードを削除した構造を持つ

int n;
vector<int> bit;

int sum(int i) {
    int s = 0;
    while  (i > 0) {
        s += bit[i];
        i -= i & -i;  // 最後の1を引く
    }
    return s;
}

void add(int i, int x) {
    while (i <= n) {
        bit[i] += x;
        i += i & -i;  // 最後の1を加算する
    }
}

int main() {
    cin >> n;
    bit = vector<int>(n + 1);
}
