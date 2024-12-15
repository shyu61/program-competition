// 接頭辞配列(共通部分文字列): p340
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// LCS(Longest Common Subsequence)とは異なり"部分文字列"なので連続している必要があることに注意
// => LCSはdpで解けるがLCPはsaとlcpを使って解く

// ポイント
// - ある部分文字列のlcpはsaで隣接(辞書順で隣接)するものとの間で必ず最大になる(辞書順で離れるほど共通prefix数は小さくなる)

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

void construct_sa(string S, vector<int>& sa) {
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

void construct_lcp(string S, vector<int>& sa, vector<int>& lcp) {
    rnk = vector<int>(n + 1);
    for (int i = 0; i <= n; i++) rnk[sa[i]] = i;

    int h = 0;
    lcp[0] = 0;
    for (int i = 0; i < n; i++) {
        int j = sa[rnk[i] - 1];

        if (h > 0) h--;
        for (; j + h < n && i + h < n; h++) {
            if (S[j + h] != S[i + h]) break;
        }
        lcp[rnk[i] - 1] = h;
    }
}

int main() {
    string S, T; cin >> S >> T;

    // S,Tを混ぜた上でsaとlcpを計算し
    string ST = S + '\0' + T;
    n = ST.length();
    vector<int> sa(n), lcp(n);

    construct_sa(ST, sa);
    construct_lcp(ST, sa, lcp);

    int ans = 0, sl = S.length();
    for (int i = 0; i < n; i++) {
        // lcp[i]がS,T間での値の場合のみ採用
        if ((sa[i] < sl) != (sa[i + 1] < sl)) {
            ans = max(ans, lcp[i]);
        }
    }
    cout << ans << endl;
}
