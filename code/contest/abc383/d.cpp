#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 約数の個数について
// - 素因数分解して、各素因数の(指数部分+1)の積を考える
// - 奇数個なら、必ず平方数のみからなる

struct Sieve {
    int n;
    vector<int> is_pn, pn;
    Sieve(int n): n(n), is_pn(n + 1, true) {
        is_pn[0] = is_pn[1] = false;
        for (int i = 2; i <= n; i++) {
            if (is_pn[i]) {
                pn.push_back(i);
                for (int j = 2 * i; j <= n; j += i) is_pn[j] = false;
            }
        }
    }
};

int main() {
    ll N; cin >> N;

    // √Nまでの素数を列挙
    Sieve sv(sqrt(N));
    int m = sv.pn.size(), ans = 0;

    // 1数の場合: p^8<=N となるxの個数をカウント
    for (auto p : sv.pn) {
        ll pp = p;
        for (int j = 0; j < 3; j++) pp *= pp;
        if (pp > N) break;
        ans++;
    }
    // 2数の場合: p^2q^2<=N となるpqの組み合わせをカウント
    // 内側のループはN/pn[i]までしか回らないので、計算量は調和級数になる
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < i; j++) {
            if (ll(sv.pn[i]) * sv.pn[i] * sv.pn[j] * sv.pn[j] > N) break;
            ans++;
        }
    }

    cout << ans << endl;
}
