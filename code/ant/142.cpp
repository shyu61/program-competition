// 列の分割統治法: p319
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 分割統治法は、非常に低レベルな概念であり、最も有名な高級概念としては木だと言える
// つまり非常に汎用性が高く、シーン特化な構造体やアルゴリズムが数多く派生して存在する
// 汎用性が高いが故に、分割統治法をナイーブに使って解ける問題も非常に多い

// 分割統治法の利用シーン
// - 問題が独立な部分問題に分割可能(最も典型は配列)
// - 統治が効率的に行える
// 基本的に累積構造を持つものが対象になる。
// 統治を効率的に行うのは難しく、分割統治法が適用できるかを左右する重要な要素。**数え上げはmergeソートと絡められるので最も典型的な利用例**

// 思考フロー
// 反転数を数えたい(数え上げ) -> j固定ではなく(i,j)のペアと考えると、独立な部分問題に分割してカウントできる
// -> 統治はmergeソートを使えばO(n)なのでO(nlogn)

ll merge_count(vector<int>& a) {
    int n = a.size();
    if (n <= 1) return 0;

    vector<int> b(a.begin(), a.begin() + n / 2);
    vector<int> c(a.begin() + n / 2, a.end());

    ll cnt = 0;
    cnt += merge_count(b);
    cnt += merge_count(c);

    // mergesort
    int ai = 0, bi = 0, ci = 0;
    while (ai < n) {
        if (bi < b.size() && (ci == c.size() || b[bi] <= c[ci])) {
            a[ai++] = b[bi++];
        } else {
            a[ai++] = c[ci++];
            cnt += n / 2 - bi;
        }
    }

    return cnt;
}

int main() {
    int n; cin >> n;
    vector<int> A(n);
    for (int i = 0; i < n; i++) cin >> A[i];

    cout << merge_count(A) << endl;
}
