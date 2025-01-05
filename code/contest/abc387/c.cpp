#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 問題の性質
// - キーワード
//   - 区間数え上げ問題, 数論, 桁dp
// - 区間数え上げ: 累積構造を使うべきで、f(x):=xまでのヘビ数としてf(R)-f(L-1)を求めるとするのが良い
// - 数え上げで、条件が桁に関するもの: 桁dpで考える

// ポイント
// - 整数の累乗はstd::powは使わない
// - 数論でも区間数え上げは頻出で、累積構造を使うケースが多い
// - 桁問題の数え上げ
//   - 「指定された値がその桁の何番目か」と「それより小さい桁の数の総数」の2つに分けて考える
// - 桁dp: 「決めた桁数」と「N未満フラグ」を基本構造とする。後者はつまりi桁目までが全てNと同じかどうか
//   - N未満フラグがtrueなら、以降の桁は任意の値を取れるし、falseならその桁の数以上の値は取れない
//   - https://torus711.hatenablog.com/entry/20150423/1429794075

// n^k
ll ipow(int n, int k) {
    ll res = 1;
    for (int i = 0; i < k; i++) res *= n;
    return res;
}

ll f(ll r) {
    vector<int> ns;
    while (r > 0) { ns.push_back(r % 10); r /= 10; }
    reverse(ns.begin(), ns.end());

    int n = ns.size();  // n桁
    ll res = 0;

    // n桁までのヘビ数の個数
    for (int k = 1; k < n; k++) {
        for (int i = 1; i <= 9; i++) {
            res += ipow(i, k - 1);
        }
    }

    // rはn桁で何番目のヘビ数か
    for (int k = 0; k < n; k++) {  // 上からk桁が元の数と同じ場合を考える
        if (k == 0) {  // 最上位が違う場合
            for (int i = 1; i < ns[0]; i++) {
                res += ipow(i, n - 1);
            }
        } else {
            res += min(ns[0], ns[k]) * ipow(ns[0], n - (k + 1));
            if (ns[k] >= ns[0]) break;  // k桁目まで同じだとヘビ数ではなくなるので以降は考えない
        }
    }

    // r自身がヘビ数かどうか
    bool ok = true;
    for (int i = 1; i < n; i++) {
        if (ns[i] >= ns[0]) {
            ok = false;
            break;
        }
    }
    if (ok) res++;

    return res;
}

int main() {
    ll L, R; cin >> L >> R;
    cout << f(R) - f(L - 1) << endl;
}
