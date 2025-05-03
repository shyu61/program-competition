#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using P = pair<int, int>;

// 🔷初見でどうやったら解けるか
// 操作が複雑なので、どの部分が問題なのか、ボトルネックなのかを特定し整理する。
// oの個数制限が問題であり、下処理した文字列sに対して?部分をoに変える必要があるかどうかが問題の本質だと分かる
// ポイントは上界と下界を考えること。つまり残り必要なoが i)下界と一致する,ii)上界と一致する,iii)その間 の3パターンを考えれば良い

// 🔷抑えるべき抽象論は？
// ある条件を満たす状態を考える時、上界と下界(極端な状態)を考えることは有用

string solve() {
    int n, k; cin >> n >> k;
    string s; cin >> s;

    rep(i, n) {
        if (s[i] == 'o') {
            if (i > 0) s[i - 1] = '.';
            if (i < n - 1) s[i + 1] = '.';
        }
    }

    int cnt = 0;
    rep(i, n) if (s[i] == 'o') cnt++;

    // i)下界と一致する
    if (cnt == k) {
        rep(i, n) if (s[i] == '?') s[i] = '.';
        return s;
    }

    rep(i, n) if (s[i] == '?') cnt++, i++;

    // iii)その間
    if (cnt > k) return s;

    // ii)上界と一致する
    // 奇数長連続領域を書き換える
    int len = 0;
    rep(i, n) {
        if (s[i] == '?') len++;
        else {
            if (len % 2 == 1) {
                rep(j, len) s[i - len + j] = (j % 2 == 0) ? 'o' : '.';
            }
            len = 0;
        }
    }
    if (len % 2 == 1) {
        rep(j, len) s[n - len + j] = (j % 2 == 0) ? 'o' : '.';
    }
    return s;
}

int main() {
    cout << solve() << endl;
}
