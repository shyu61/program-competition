#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

// ジャンル
// 文字列, 周期性, 反転操作, 2進数, 再帰構造

// 方針
// 周期性が絡む問題は以下の2つを考えるのがまず基本
// 1. 周期内での位置
// 2. 何周期目か
// 周期の大きさが既知なら剰余と商になる。本問題は商が何回反転したのかが分かれば求解できる
// 明らかに再帰構造なので、木で考えてみると右移動回数の偶奇を調べることで反転状態が分かる
// あとは、根から葉まで掘りつつ右移動の回数を数えれば良い

// ポイント
// ダブリング構造は、再帰や木、ビット演算と関係しやすい
// ビット演算はindexと関連性があることが多い

// 反省点
// 思いついた法則性を強引に実装しようとしている。法則性が絡むならもっと綺麗な形に持っていけると考えるべき。
// 強引に実装するとエッジケースが多すぎて大変。2の累乗が絡むなら、bit演算や再帰構造、木構造を考える。
// 分解して何を考える必要があるのかを常に明確にする。今回なら、周期が絡む -> 周期内での位置と何個目の周期かは分かるので、
// その周期が何回反転したものかさえ分かればいい ということになる。とすれば周期ブロックの反転法則を見抜くことに集中でき、
// 2の累乗が絡むことや、再帰構造になっていることを冷静に考えると、bitで考えてみようとか木構造を書いてみようという発想になる。

int main() {
    string s; cin >> s;
    int n = s.size();
    int q; cin >> q;

    auto flip = [&](char c) -> char {
        if (islower(c)) return toupper(c);
        return tolower(c);
    };

    while (q--) {
        ll k; cin >> k; k--;
        int si = k % n;
        ll cnt = popcount(ull(k / n));
        cout << (cnt % 2 == 0 ? s[si] : flip(s[si])) << ' ';
    }
    cout << endl;
}

// 解法2
int main() {
    string s; cin >> s;
    int n = s.size();
    int q; cin >> q;

    auto flip = [&](char c) -> char {
        if (islower(c)) return toupper(c);
        return tolower(c);
    };

    const ll INF = 1ll << 60;
    auto dfs = [&](ll x) {
        int num = 0;
        ll l = 0, r = INF;
        while (r - l > 1) {
            ll mid = (l + r) / 2;
            if (x < mid) r = mid;
            else l = mid, num++;
        }
        return num;
    };

    while (q--) {
        ll k; cin >> k; k--;
        int si = k % n;
        ll x = k / n;
        int cnt = dfs(x);
        cout << (cnt % 2 == 0 ? s[si] : flip(s[si])) << ' ';
    }
    cout << endl;
}

// 解法3
int main() {
    string s; cin >> s;
    int n = s.size();
    int q; cin >> q;

    auto flip = [&](char c) -> char {
        if (islower(c)) return toupper(c);
        return tolower(c);
    };

    const ll INF = 1ll << 60;
    auto dfs = [&](auto dfs, ll x, ll l, ll r, int num) -> int {
        if (r - l <= 1) return num;
        ll mid = (l + r) / 2;
        if (x < mid) return dfs(dfs, x, l, mid, num);
        else return dfs(dfs, x, mid, r, num + 1);
    };

    while (q--) {
        ll k; cin >> k; k--;
        int si = k % n;
        ll x = k / n;
        int cnt = dfs(dfs, x, 0, INF, 0);
        cout << (cnt % 2 == 0 ? s[si] : flip(s[si])) << ' ';
    }
    cout << endl;
}
