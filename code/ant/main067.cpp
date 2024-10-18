// 素数に関する基本的なアルゴリズム(区間内の素数の個数): p113
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 素数判定: O(√n)
// 素数の個数: その範囲内の個数分素数判定を行うこととイコールなので、プレーンにやるならO(n√n)
// 　　　　　  エラトステネスの篩を使うならO(nlog(log(n)))

// 素数の個数なのでなんとかしてエラトステネスの篩を作りたい。[2,b)の篩は作れないので、どうするか
// -> 素数判定方法で他に知っているものを探す。xが素数じゃないなら√x以下に素因数を持つことを使えないか考える
// -> √b以下で篩を作ることを考える。そもそもの目的は[a,b)の区間篩を作ることであり、エラトステネスの篩は素因数の定数倍を除外するという方法をとっている。
// -> 区間篩を作りたいという目的と、エラトステネスの篩が素因数の定数倍を消去することを利用していることを考えれば、[2,√b)の篩で[a,b)の篩を作ることができることに気付く。
// ポイントは、目的を明確にすることと、知っているアルゴリズムの組み合わせを考えること、アルゴリズムの本質に立ち返って考えること。

int main() {
    ll a, b; cin >> a >> b;

    int small_max = int(sqrt(b));

    vector<bool> small(small_max + 1, true);
    vector<bool> big(b - a, true);

    for (int i = 2; i <= small_max; i++) {
        if (!small[i]) continue;
        for (int j = 1; j * i <= small_max; j++) small[j * i] = false;

        ll j = a / i;
        if (a % i != 0) j++;
        for (; j * i < b; j++) big[j * i - a] = false;
    }

    int cnt = 0;
    for (int i = 0; i < b - a; i++) {
        if (big[i]) cnt++;
    }
    cout << cnt << endl;
}
