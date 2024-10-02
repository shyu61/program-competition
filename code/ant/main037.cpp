// 硬貨の問題
#include <bits/stdc++.h>
using namespace std;

// 貪欲法は、局所最適性が成立する条件下での逐次ステップ問題で、各ステップで最適な操作を行うことで全体最適解を導く方法
// グラフは局所最適構造を持ちやすく、他にも単調構造になっているケースでは貪欲法が使えるシーンが多い。

// 明らかに金額が大きいコインを優先して使った方が枚数が少なくなるため、貪欲法で解ける。
// コインの枚数はどのコインを選んでも単調に増加していくので単調性がある

int main() {
    vector<int> c(5);
    for (int i = 0; i < 6; i++) cin >> c[i];
    int a; cin >> a;

    vector<int> coins{1,5,10,50,100,500};
    int ans = 0;
    for (int i = 5; i >= 0; i--) {
        // 条件を満たすまで個数を増やしていくなどの操作は、ループを書かずに商を取る
        int m = min(a / coins[i], c[i]);
        a -= m * coins[i];
        ans += m;
        if (a == 0) {
            cout << ans << endl;
            return 0;
        }
    }
}
