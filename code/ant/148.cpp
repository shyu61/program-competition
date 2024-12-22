// 接頭辞配列(Sequence): p338
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// suffix-arrayの利用シーン
// - 文字列検索: O(|T|log|S|)
// - 辞書順prefix問題
//   - 元の文字列の反転文字列の最小suffixは、元の文字列の最大prefixになる

// suffix-array vs prefix-array
// prefix-arrayはほとんど使われない。saとpaは互いに簡単に変換可能でありどちらか一方のみで十分
// paなら終了位置を保持することなり操作として直感性にかけるためsaが一般に広く使われている
// <= 元の文字列を反転してsuffix-arrayを考え戻せばprefixの最大,最小を考えたことになる

// 2倍拡張を使うシーン
// - 循環を扱いたい場合(時刻など)
// - 区間個別の反転操作をまとめて扱いたい場合

int n, k;
vector<int> rnk, tmp;

bool compare_sa(int i, int j) {
    if (rnk[i] != rnk[j]) return rnk[i] < rnk[j];
    else {
        int ri = i + k <= n ? rnk[i + k] : -1;
        int rj = j + k <= n ? rnk[j + k] : -1;
        return ri < rj;
    }
}

void construct_sa(vector<int> S, vector<int>& sa) {
    n = S.size();
    rnk = tmp = vector<int>(n + 1);

    for (int i = 0; i <= n; i++) {
        sa[i] = i;
        rnk[i] = i < n ? S[i] : -1;
    }

    for (k = 1; k <= n; k *= 2) {
        sort(sa.begin(), sa.end(), compare_sa);

        tmp[sa[0]] = 0;
        for (int i = 1; i <= n; i++) {
            tmp[sa[i]] = tmp[sa[i - 1]] + (compare_sa(sa[i - 1], sa[i]) ? 1 : 0);
        }
        for (int i = 0; i <= n; i++) rnk[i] = tmp[i];
    }
}

int main() {
    int N; cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    // Aを逆転したものを作り、そのsuffix-arrayを構築
    vector<int> rev(N), sa(N);
    reverse_copy(A.begin(), A.end(), rev.begin());
    construct_sa(rev, sa);

    // 1つ目の区間を決める
    // 基本的には最小のsuffixを取れば良いのでsa[0]になるが「2文字以上残す必要がある && 最低1文字」という制約を守る必要がある
    int p1;
    for (int i = 0; i < N; i++) {
        p1 = N - sa[i];  // sa[i]は末尾からの位置なのでNから引く
        if (p1 >= 1 && N - p1 >= 2) break;
    }

    // p1以降の文字列を逆転して2回繰り返したものを作り、そのsuffix-arrayを構築
    int m = N - p1;
    rev.clear(); sa.clear();
    rev.resize(m * 2); sa.resize(m * 2);
    reverse_copy(A.begin() + p1, A.end(), rev.begin());
    reverse_copy(A.begin() + p1, A.end(), rev.begin() + m);
    construct_sa(rev, sa);

    // 2つ目の区間を決める
    int p2;
    for (int i = 0; i <= m * 2; i++) {
        // sa[i]は逆順の2倍拡張配列のindexより、
        // sa[i]が前半の場合: 前半区間の末尾からの距離が元配列の先頭からの距離になるので m-sa[i]
        // sa[i]が後半の場合: 考慮しない(m-sa[i]<0よりif条件で必ず弾かれる)
        p2 = p1 + (m - sa[i]);
        if (p2 - p1 >= 1 && N - p2 >= 1) break;
    }

    reverse(A.begin(), A.begin() + p1);
    reverse(A.begin() + p1, A.begin() + p2);
    reverse(A.begin() + p2, A.end());
    for (int i = 0; i < N; i++) cout << A[i] << (i == N - 1 ? "\n" : " ");
}
