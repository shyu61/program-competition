#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ジャンル
// - 数論, 区間数え上げ, 桁問題

// 方針
// - 区間数え上げなので累積の引き算で求解する
// - 桁問題かつ、各桁が最上位桁にしか依存せずほぼ独立なので、法則からの立式で解く
//   - n-1桁までの個数 + n桁で何番目か に分解してそれぞれを数え上げる
//   - 法則の場合でも桁dpの枠組みで考えるのがセオリーなので、k桁目まで元の数と一致する場合の数え上げを考える

// ポイント
// - 整数の累乗はstd::powは使わない
// - 桁dp: https://torus711.hatenablog.com/entry/20150423/1429794075
// - 型変換
//   - char_to_int: c-'0'
//   - int_to_string: to_string(i)
//   - string_to_int: stoi(s)

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
