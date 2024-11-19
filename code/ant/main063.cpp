// ユークリッド互除法(双六): p108
#include <bits/stdc++.h>
using namespace std;

// ユークリッド互除法は大きく2つの側面を持つ。
// 1. gcd(a,b)=gcd(b,a%b): 最も基本的で、最大公約数を求めるために再帰的に同型の小問題に帰着させているところが肝
// 2. gcd(a,b)=ax+by: 最大公約数はa,bの線型結合で表せる点。これは同値条件なので不定方程式の整数解の有無は右辺がgcd(a,b)の倍数になっているかどうかで判断できる。
// 特にa,bが互いに疎な場合は必ず解を持つと言え、逆に右辺が1ならa,bは互いに素である必要がある。

// ユークリッド互除法を拡張するとベズーの等式である不定方程式が解ける。これはユークリッド互除法の最終項ではその解がx=1,y=0となることに起因する
// ユークリッド互除法は漸化式なので、最終項の値を初項まで伝播すればよいので、第n+1項から第n項へx,yがどう更新されるかを調べれば良いことがわかる
// gcd(a,b)=ax+byとすると、gcd(a,b)=gcd(b,r)=bx'+ry'. ここでr=a-⌊b/a⌋bより、gcd(b,r)=bx'+(a-⌊b/a⌋b)y'=ay'+b(x'-⌊b/a⌋by')となり、係数比較するとx=y', y=x'-⌊b/a⌋by'となる
// これは戻る方向への更新になるの帰りがけに更新すれば良い

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
