// 行列累乗(グラフの長さkとパスの総数): p183
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Mat = vector<vector<int>>;

// 行列累乗は、累積構造を持っている場合に適用可能で、その性質上DPと相性が良い。
// グラフにおいても、頂点から頂点への移動は遷移であり、経路はこの遷移の繰り返しと考えることができる。
// 隣接行列とは 頂点から頂点への遷移を記述した行列であり、経路をたどるということは、この隣接行列の累乗とイコールである

// ただし行列累乗は、各累乗ごとに条件分岐がないことが必要である。つまりDFSのように再訪を許可しない場合では、繰り返し構造の中で条件分岐が生じるため、行列累乗上とは相性が悪い。

// Tips
// グラフで始点と終点がある問題において、始点と中間点と終点の3つで証明を考えるとうまくいくケースがある。
// グラフアルゴリズムもこの3点を使って証明しているケースが結構あるので、頭の片隅に置いておくと良い。

const int M = 10007;
int N;
vector<vector<int>> G;

Mat mul(Mat A, Mat B) {
    Mat res = vector<vector<int>>(A.size(), vector<int>(A.size()));
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A.size(); j++) {
            for (int k = 0; k < A.size(); k++) {
                res[i][j] = (res[i][j] + A[i][k] * B[k][j]) % M;
            }
        }
    }
    return res;
}

Mat pow(Mat A, int n) {
    Mat res = vector<vector<int>>(A.size(), vector<int>(A.size()));
    for (int i = 0; i < res.size(); i++) res[i][i] = 1;
    while (n > 0) {
        if (n & 1) res = mul(res, A);
        A = mul(A, A);
        n >>= 1;
    }
    return res;
}

int main() {
    int m, k; cin >> N >> m >> k;
    G = vector<vector<int>>(N, vector<int>(N));
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        G[--x][--y] = 1;
    }

    Mat nG = pow(G, k);
    int ans = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            ans += nG[i][j];
        }
    }
    cout << ans << endl;
}

// void dfs(int v, int d) {
//     if (d == k) {
//         cnt++;
//         return;
//     }
//     for (auto u : G[v]) dfs(u, d + 1);
// }

// int main() {
//     cin >> n >> m >> k;
//     G = vector<vector<int>>(n);
//     for (int i = 0; i < m; i++) {
//         int x, y; cin >> x >> y;
//         x--; y--;
//         G[x].push_back(y);
//     }

//     for (int i = 0; i < n; i++) dfs(i, 0);
//     cout << cnt << endl;
// }
