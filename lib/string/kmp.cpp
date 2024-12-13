#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> create_table(string T) {
    int i = 2, j = 0, m = T.length();
    vector<int> pi(m + 1);
    pi[0] = 0;
    while (i <= m) {
        // 先頭からj文字一致している場合
        if (T[i - 1] == T[j]) pi[i++] = ++j;
        // 部分一致が途切れる場合
        else if (j > 0) j = pi[j];
        else pi[i++] = 0;
    }
    return pi;
}

vector<int> kmp(string S, string T) {
    vector<int> res;
    vector<int> pi = create_table(T);  // 失敗関数を事前計算
    int i = 0, j = 0, n = S.length(), m = T.length();
    while (i + j < n) {
        if (T[j] == S[i + j]) {
            j++;
            if (j == m) {
                res.push_back(i);
                i += j - T[j];
                j = T[j];
            }
        } else {
            i += j - T[j];
            if (j > 0) j = T[j];
        }
    }
    return res;
}
