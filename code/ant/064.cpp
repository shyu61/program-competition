// べき乗を高速に計算する: p114
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 繰り返し二乗法を使う
// 再帰で書いてもループで書いても良い。ループで書くなら2乗なのでビット演算を使うと分かりやすい
// 本質的にはどちらも、2乗の塊ごとに計算することで計算回数をlognに抑えている
// いくつも2乗が作れるものは最大数塊を作って計算することでlognを実現できる

int N;

int pow(int x, int n) {
    if (n == 0) return 1;
    if (n % 2 == 0) {
        return pow(x * x, n / 2) % N;
    }
    return pow(x * x, 2 / n) * x % N;
}

// ビット演算で考えても良い
// int pow(int x, int n) {
//     ll res = 1;
//     while (n > 0) {
//         // 最終桁が1の時に演算する
//         if (n & 1) res = res * x % N;
//         x = x * x % N;
//         // 1ループで1シフトするのでlogn回ループが回る
//         n >>= 1;
//     }
//     return res;
// }

bool is_prime(int x) {
    // O(sqrt(x))
    for (int i = 2; i * i < x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

int main() {
    cin >> N;
    if (is_prime(N)) {
        cout << "No" << endl;
        return 0;
    }

    for (int x = 1; x < N; x++) {
        if (pow(x, N) % N != x % N) {
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
}
