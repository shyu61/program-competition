#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 🔷初見でどうやったら解けるか
// 逐次問題だがループが間に合わないケース。剰余が絡むので余りを考慮し周期性を利用する問題の可能性が高い。
// 周期性を見つける方法は大きく2つ。(1)地道に実験して法則性を見つける。(2)functionalグラフ的に考えて、再訪から周期を計算する。
// 法則性を見つけるのが難しそうなのと、(2)の場合の最悪のケースでもO(n)で周期を計算できるので(2)でいく。
// 一旦最悪周期1e5進めておけばエッジケースを考慮しなくて良い。あとはfunctionalグラフと同様に考えればok

// 🔷抑えるべき抽象論は？
// 周期性を見つける方法
// - 地道に実験して法則性を見つける
// - functionalグラフ的に考えて、再訪から周期を計算する
// functionalグラフは一旦頂点数分進めておけば良い

const int m = 1e5;

// エッジケースを考慮する王道解法
int main() {
    int n; ll k; cin >> n >> k;

    auto f = [&](int x) {
        int sum = 0;
        for (auto c : to_string(x)) sum += c - '0';
        return (x + sum) % m;
    };

    int s = n, d = 0;
    vector<int> id(m, -1);
    while (id[s] == -1) {
        id[s] = d++;
        s = f(s);
    }
    d -= id[s];
    if (k >= id[s]) {
        k -= id[s];
        k %= d;
        n = s;
    }
    rep(i, k) n = f(n);

    cout << n << endl;
}

// 定数倍遅いがエッジケースの考慮がいらない解法
int main() {
    int n; ll k; cin >> n >> k;

    auto f = [&](int x) {
        int sum = 0;
        int y = x;
        while (y > 0) {
            sum += y % 10;
            y /= 10;
        }
        return (x + sum) % m;
    };

    if (k <= m) {
        rep(i, k) n = f(n);
        cout << n << endl;
        return 0;
    }

    rep(i, m) n = f(n);
    k -= m;

    vector<bool> seen(m);
    int d = 0;
    while (!seen[n]) {
        d++;
        seen[n] = true;
        n = f(n);
    }
    k %= d;
    rep(i, k) n = f(n);
    cout << n << endl;
}
