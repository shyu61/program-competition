#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
const ll INF = 1000000000000000000LL;  // 1e18

// 🔷抑えるべき抽象論は？
// オーバーフローを回避するには移項が有効
// 10^16以上ではe表現は使わない
// 約数と倍数は対をなす関係。一方からもう一方を導ける: lcm(a,b)=a*b/gcd(a,b)

int main() {
    ll a, b; cin >> a >> b;
    if (a < b) swap(a, b);

    if (a > INF) {
        cout << "Large" << endl;
        return 0;
    }

    ll g = gcd(a, b);
    if (a / g > INF / b) cout << "Large" << endl;
    else cout << a / g * b << endl;
}
