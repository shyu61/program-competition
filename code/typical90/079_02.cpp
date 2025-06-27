#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;

// https://atcoder.jp/contests/abc090/tasks/arc091_a

// 🔷初見でどうやったら解けるか
// 🔷抑えるべき抽象論は？
// 組合せ最適化問題で最初に考えるべきこと
// - 解が決定的か？: 操作系で、操作が可換な場合などは決定的である場合が多い
//   - この場合はもはや組合せ最適化問題ではなく、数え上げ問題である
// - 解が決定的でない場合(操作の仕方によって結果が変わる場合): 組合せ最適化問題の枠組みで解く

ll solve() {
    int h, w; cin >> h >> w;
    if (h > w) swap(h, w);
    if (h == 1 && w == 1) return 1;
    if (h == 1) return w - 2;

    return ll(h - 2) * (w - 2);
}

int main() {
    cout << solve() << endl;
}

