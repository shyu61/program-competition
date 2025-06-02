#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 🔷抑えるべき抽象論は？
// dequeuの内部構造
// - ある程度大きなblockの中心から値を格納していく戦略
// - 無駄が少なくなるようにblockは大きくしすぎず、複数のblockを繋ぎ合わせる。連結関係は別で記憶する

int main() {
    int q; cin >> q;
    deque<int> deq;
    while (q--) {
        int t, x; cin >> t >> x;
        if (t == 1) deq.push_front(x);
        if (t == 2) deq.push_back(x);
        if (t == 3) cout << deq[--x] << '\n';
    }
}
