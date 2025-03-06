#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;

// 想定解
// まとめて全探索

// 罠
// 全探索はmではなくf(m)についてする必要がある
// → mに比べてf(m)の通り数が少ないことに気付く必要がある
// 桁問題なので、桁dpや約数なども選択肢に上がってしまう点
// → 桁を累積的に見てもf(m)=m-Bかは途中で評価できないので、dpは意味がない
// → 素因数分解をしても引き算が絡むのでうまく絞れない

// ポイント
// 桁操作は文字列を使うと楽

int main() {
    ll n, b; cin >> n >> b;
    int d = int(log10(n)) + 1;

    unordered_map<ll, vector<string>> a;
    auto rec = [&](auto rec, int s, string c) -> void {
        if (c.size() <= d) {
            ll p = 1;
            for (auto& ci : c) p *= int(ci - '0');
            if (p + b <= n) a[p].push_back(c);
            if (c.size() == d) return;
        }
        for (int i = s; i < 10; i++) {
            c.push_back(i + '0');
            rec(rec, i, c);
            c.pop_back();
        }
    };

    rec(rec, 0, "");

    ll ans = 0;
    for (auto& [fm, ss] : a) {
        string ms = to_string(fm + b);
        sort(ms.begin(), ms.end());
        for (auto& s : ss) {
            if (s == ms) {
                ans++;
                break;
            }
        }
    }
    cout << ans << endl;
}
