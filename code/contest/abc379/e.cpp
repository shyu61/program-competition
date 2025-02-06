#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// ジャンル
// 全ペア走査問題, 桁問題, 文字列問題

// 方針
// 最大N桁の数なので明らかに桁ごとに配列もしくは文字列で扱う必要がある
// 故に桁ごとに値を計算し、最後に繰り上げ処理を行うことで求解することを考える
// 桁ごとの計算はO(logN)以内である必要があるので、元の文字列のある桁を走査する時、同時に計算できる答えの桁は1つ程度である
// この実行制約を考慮しつつ考えると、累積和を使えばO(1)かつ各桁を1回ずつしか走査せずに求解できることがわかる

// ポイント
// 全ペア走査問題で、累積和を使った高速化を行うパターン
// 最終求めるものが総和なので、累積和を使うのでは？と考えるのも良い

int main() {
    int n; string s; cin >> n >> s;

    vector<ll> a(n);
    ll cur = 0;
    rep(i, n) {
        int d = s[i] - '0';
        cur += d * (i + 1);
        a[i] = cur;
    }

    ll carry = 0;
    for (int i = n - 1; i >= 0; i--) {
        a[i] += carry;
        carry = a[i] / 10;
        a[i] %= 10;
    }

    if (carry > 0) cout << carry;
    for (auto ai : a) cout << ai;
    cout << endl;
}
