#include <bits/stdc++.h>
using namespace std;

// ジャンル
// 数列, 区間クエリ

// 方針
// 厳密な区間クエリではないが、常に頭から上限を満たす位置までスキャンする必要があるので、区間クエリ問題だとみなせる
// 単調性を導出できるなら尺取り法あるいは二分探索が可能なので、そこに帰着させる方法で検討する
// Bはsortしても問題ないので尺取り法で解ける
// A側も実際に食べる位置の値は単調減少になるので二分探索でもいける(これはちょっと考察か必要)

int main() {
    int N, M; cin >> N >> M;
    vector<int> A(N);
    vector<pair<int, int>> B(M);
    for (int i = 0; i < N; i++) cin >> A[i];
    for (int i = 0; i < M; i++) {
        int b; cin >> b;
        B[i] = {b, i};
    }
    sort(B.begin(), B.end(), greater<>());

    vector<int> C(M, -1);

    int cur = 0;
    for (auto [b, i] : B) {
        while (cur < N && b < A[cur]) cur++;
        if (cur == N) break;
        C[i] = cur + 1;
    }

    for (auto x : C) cout << x << endl;
}

// int main() {
//     int N, M; cin >> N >> M;
//     vector<int> A(N);
//     for (int i = 0; i < N; i++) cin >> A[i];
//     for (int i = 0; i < N - 1; i++) A[i + 1] = min(A[i], A[i + 1]);

//     for (int i = 0; i < M; i++) {
//         int b; cin >> b;
//         int d = lower_bound(A.begin(), A.end(), b, greater<int>()) - A.begin();
//         cout << (d < N ? d + 1 : -1) << '\n';
//     }
// }
