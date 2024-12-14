#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// suffix-arrayは辞書順で開始位置を値に持つ
// ダブリングの一種だが、自身を再帰的に更新する典型的なダブリングとは異なり、saとrankで互いに更新し合うという構造を取っている
// ソート済みのsaはほぼrankと同じ順序構造を持つが、イコールの場合を正確に表現できない。イコールかどうかは前後半に分割して比較する上で非常に重要なのでrankを別途計算する必要がある
// ポイント
// - 文字列のソートは前後半で分割して考えることができる

int n, k;
vector<int> rnk, tmp;

// (rank[i], rank[i+k])と(rank[j], rank[j+k])を比較
bool compare_sa(int i, int j) {
    // イコール判定がこの分割比較の核なので、saだけでの再帰更新ができずrankが必要になる
    if (rnk[i] != rnk[j]) return rnk[i] < rnk[j];
    else {  // 前半k文字のrankが一致した場合は、後半k文字のrankをみる
        int ri = i + k <= n ? rnk[i + k] : -1;
        int rj = j + k <= n ? rnk[j + k] : -1;
        return ri < rj;
    }
}

// 文字列Sの接頭辞配列を構築
void construct_sa(string S, vector<int>& sa) {
    n = S.length();
    rnk = tmp = vector<int>(n + 1);

    // 最初は1文字、ランクは文字コードにすれば良い
    for (int i = 0; i <= n; i++) {
        sa[i] = i;
        rnk[i] = i < n ? S[i] : -1;
    }

    // k文字についてソートされているところから、2k文字でソートする
    for (k = 1; k <= n; k *= 2) {
        // kでのrankを使って2kのsaを作る
        sort(sa.begin(), sa.end(), compare_sa);

        // 次のsortで使うランクの計算: 2kのsaを作るのには、kのrankが必要。つまりrankの方が更新が後になる
        // 故に2kのrankを計算するのに2kでソート済みのsaを使うことができる
        tmp[sa[0]] = 0;
        for (int i = 1; i <= n; i++) {
            // saは2kでソート済みなのでsa[i]がsa[i-1]よりもrankが小さくなることはない
            // ただしソート順が後でもrankが等しくなることはあり得るので比較する
            tmp[sa[i]] = tmp[sa[i - 1]] + (compare_sa(sa[i - 1], sa[i]) ? 1 : 0);
        }
        for (int i = 0; i <= n; i++) rnk[i] = tmp[i];
    }
}

// SにTが含まれるかを判定
// rolling-hashのO(|S|+|T|)に対しO(|T|log|S|)で計算でき、|S|が大きいとき有利になる
bool contain(string S, vector<int>& sa, string T) {
    // 二分探索でlbは常に満たさない, ubは常に満たす
    int lb = 0, ub = S.length();
    // O(log|S|)
    while (ub - lb > 1) {
        int m = (lb + ub) / 2;
        // Sのsa[m]文字目から|T|文字とTを比較
        // 比較コストはO(|T|)
        if (S.compare(sa[m], T.length(), T) < 0) lb = m;  // Tの方が辞書順で後ならsaをmより後ろ側を探索する必要があるのでlb=mと更新する
        else ub = m;
    }
    return S.compare(sa[ub], T.length(), T);
}
