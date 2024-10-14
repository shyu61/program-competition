// ユークリッド互除法(双六): p108
#include <bits/stdc++.h>
using namespace std;

// ユークリッド互除法は大きく2つの側面を持つ。
// 1. gcd(a,b)=gcd(a,a%b): 最も基本的で、最大公約数を求めるために再帰的に同型の小問題に帰着させているところが肝
// 2. gcd(a,b)=ax+by: 最大公約数はa,bの線型結合で表せる点。これは同値条件なので不定方程式の整数解の有無は右辺がgcd(a,b)の倍数になっているかどうかで判断できる。
// 特にa,bが互いに疎な場合は必ず解を持つと言え、逆に右辺が1ならa,bは互いに素である必要がある。

// ユークリッド互除法は再帰関数なので、漸化式と捉えても良い。遷移式は剰余の線形結合なので、末項の値(gcd(a,b))を初項の値(a,b)の線形結合で表現できることになる。
// 故にべズーの等式: gcd(a,b)=ax+by を導くことができ、逆順にたどる(帰りがけ)で逆の遷移式を計算することで、x,yを求めることもできる。
// 遷移式はgcd(b,r)からgcd(a,b)への遷移を考えれば良い。x=y_old, y=x_old-(a/b)*y_oldが導ける

int extgcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    int d = extgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}

// int extgcd(int a, int b, int& x, int& y) {
//     if (b == 0) {
//         x = 1; y = 0;
//         return a;
//     }
//     int d = extgcd(b, a % b, x, y);
//     int x_old = x;
//     x = y;
//     y = x_old - (a / b) * y;
//     return d;
// }

int main() {
    int a, b; cin >> a >> b;

    int x, y;
    int gcd = extgcd(a, b, x, y);

    if (gcd != 1) cout << -1 << endl;
    else {
        if (x < 0) cout << 0 << -x;
        else cout << x << 0;

        if (y < 0) cout << 0 << -y;
        else cout << y << 0;

        cout << endl;
    }
}
