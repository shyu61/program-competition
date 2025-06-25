#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using mint = atcoder::modint998244353;

// https://atcoder.jp/contests/arc116/tasks/arc116_b

// 🔷初見でどうやったら解けるか
// 数え上げ問題で、対象の生成が間に合わないケース。
// 生成せず数え上げるアプローチとして、数式変形,対称性利用,主客転倒,データ構造利用 などが定番
// 本問題は注目した値が、min,maxになりうるかが重要なので主客転倒が使えそう。
// sortして考えると、i<jを満たすi,jを考えるとき、min(B)=a[i],max(B)=a[j]となる通り数は、
// その間の要素を使うかどうかの通り数と等しいので2^(j-i-1)。sortした配列を小さい方から舐めれば求解できる

// 🔷抑えるべき抽象論は？
// 数え上げで対象の生成が間に合わないケースは頻出
// - 数式変形,対称性利用,主客転倒,データ構造利用 を順に検討する
// - 数列をsortできる場合も多い(全ペアや全集合が対象の場合が多いため)

int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i];
    sort(a.begin(), a.end());

    mint ans = 0;
    rep(i, n) ans += mint(a[i]) * a[i];

    mint now = 0;
    for (int i = n - 2; i >= 0; i--) {
        now += a[i + 1];
        ans += a[i] * now;
        now *= 2;
    }

    cout << ans.val() << endl;
}
