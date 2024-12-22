// 応用問題(Evacuation Plan): p215
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 負の閉路を応用した解法: 判定問題という性質を利用する
// 最小費用流で解けることは分かったが、判定問題という性質を使っていない -> すでにEijが与えられている、つまり増加パスのように途中から始められるのでは？
// -> まずEij流しておいて最適性を判定 -> 最適でなかった場合は続きから水を流せば良い
// 最適性の判定 -> 負の閉路の有無をチェック -> ワーシャルフロイド/ベルマンフォードを使う -> これらが適用できる形でEijを流したグラフを用意する必要がある
// -> d[i][i]<0で判定できる -> 全ての点i,jについて、残余グラフでのd[i][j]を求めておけば良い -> 残余グラフはcap>0の場合のみエッジがあるとする

// ポイント
// ネットワークフローは途中から始めるという考えを採用しやすい。残余グラフに対しての増加パスは、既存のパスを修正する能力を持っているために
// 最大フローやマッチングは途中から始めることができる。最小費用流などパスの選択に規則を設けている（s-t最短路）場合はその限りではないが、最小費用流に関しては
// 負の閉路がないことが判定条件として使える。

const int MAX_D = 4 * 1000 * 100 + 1;
const int MAX_F = 1e5 + 1;

int main() {
    int N, M; cin >> N >> M;
    vector<int> X(N), Y(N), B(N), P(M), Q(M), C(M);
    for (int i = 0; i < N; i++) cin >> X[i] >> Y[i] >> B[i];
    for (int i = 0; i < M; i++) cin >> P[i] >> Q[i] >> C[i];
    vector<vector<int>> E(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> E[i][j];
        }
    }

    int V = N + M + 1;
    // sからの流出量は常にBiで固定なので順辺も逆辺も考慮する必要がないので省略
    int t = N + M;
    // ワーシャルフロイドで負の閉路判定を行うために、Eijを流した後の残余グラフにおけるd[i][j]を求める
    vector<vector<int>> d(V, vector<int>(V, MAX_D));  // 距離行列, MAX_Dはエッジが存在しない場合
    for (int j = 0; j < M; j++) {
        int sum = 0;
        for (int i = 0; i < N; i++) {
            int c = abs(X[i] - P[j]) + abs(Y[i] - Q[j]) + 1;
            d[i][N + j] = c;
            if (E[i][j] > 0) d[N + j][i] = -c;  // 順方向に流れがないものは逆辺のcapは0のままなのでエッジがないことと同じになる
            sum += E[i][j];
        }
        // シェルターN+jに流入がある場合は、シェルターとtの間にエッジをはる
        // ただし、流入がcapいっぱいの時(C[j])は逆辺のみはる
        if (sum > 0) d[t][N + j] = 0;
        if (sum < C[j]) d[N + j][t] = 0;
    }

    // ワーシャルフロイドにより閉路の存在確認
    vector<vector<int>> prev(V, vector<int>(V));
    vector<bool> used(V);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            prev[i][j] = i;
        }
    }
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                // `d[i][j] = min(d[i][j], d[i][k] + d[k][j])`で更新が走る時
                if (d[i][j] > d[i][k] + d[k][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                    // ダイクストラ同様、経路の更新が走る度にprevを保存していく
                    // i->jへの経路がkを経由するルートで短縮されるので、jの直前はk->jの直前と同じになる
                    prev[i][j] = prev[k][j];
                    // 負の閉路があることが確定する
                    // (全てのkを調べ終わらずとも既にd[i][j] < 0なら、minを取るのでd[i][j] < 0が確定する)
                    if (i == j && d[i][j] < 0) {
                        fill(used.begin(), used.end(), 0);
                        // 経路復元。閉路復元はusedな頂点を再訪するまで戻る
                        for (int v = i; !used[v]; v = prev[i][v]) {
                            used[v] = true;
                            if (v != t && prev[i][v] != t) {
                                // v>=Nつまりvがシェルター側の頂点なら、ビル->シェルターに向けて負の閉路が存在するということなので
                                // ビル->シェルターに向けて流量を増やす
                                if (v >= N) E[prev[i][v]][v - N]++;
                                // v<Nつまりvがビル側の頂点なら、シェルター->ビルに向けて負の閉路が存在するということなので
                                // シェルター->ビルに向けて流量を増やす、つまりEを減らす
                                else E[v][prev[i][v] - N]--;
                            }
                        }
                        cout << "SUBOPTIMAL" << endl;
                        for (int x = 0; x < N; x++) {
                            for (int y = 0; y < M; y++) {
                                cout << E[x][y] << (y == M - 1 ? "\n" : " ");
                            }
                        }
                        return 0;
                    }

                }
            }
        }
    }
    cout << "OPTIMAL" << endl;
}
