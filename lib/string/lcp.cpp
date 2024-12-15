#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 高さ配列, Longest Common Prefix
// lcp[i] := saでi番目とi+1番目のsuffixの共通prefix数

// ポイント
// 開始位置を一つずらす前後で共通部分している部分は次のlcpにも含まれるという性質を利用して尺取り法によりO(n)で求めることができる
// まさに尺取り法と同じ構造をしている

vector<int> rnk;

// lcp[i]:=S[sa[i]:]とS[sa[i+1]:]の共通prefix数
void construct_lcp(string S, vector<int>& sa, vector<int>& lcp) {
    int n = S.length();
    // rnk[i]:=位置iでのsuffixの順位 (saの逆表現配列)
    rnk = vector<int>(n + 1);
    for (int i = 0; i <= n; i++) rnk[sa[i]] = i;

    // k=sa[rnk[i]-1](位置iでのsuffixのsaで一つ前のsuffixの位置)とし、S[i:]とS[k:]のlcpをhとすると、
    // S[i+1:]とS[k+1:]のlcpはh-1以上が保証されることを利用する
    // S[i+1:]の比較対象はS[k':](k'=sa[rnk[i+1]-1])であり、k'=k+1とは限らないが、
    // S[k':]はS[i+1]とsaで隣接しているので、S[i+1]とのlcpが最も長い。ゆえにS[k+1:]よりもlcpが短くなることはない
    int h = 0;
    lcp[0] = 0;
    for (int i = 0; i < n; i++) {
        // 位置iのsuffixと、saでその1つ前のsuffix(位置j)のlcpを求める
        int j = sa[rnk[i] - 1];  // lcpはsaで隣接する2つのsuffixについての値

        // hの先頭の分1減らし、後ろが一致しているだけ増やす
        if (h > 0) h--;  // h-1以上が保証されるので初期値に設定
        // h分はすでに共通prefixであることがわかっているので、それ以降を調べる
        for (; j + h < n && i + h < n; h++) {
            if (S[j + h] != S[i + h]) break;  // 一致しなかったら終了
        }
        lcp[rnk[i] - 1] = h;  // 位置iとその一つ前のrankのsuffixとの比較をしたので、位置iのrankの-1のlcpを計算したことになる
    }
}
