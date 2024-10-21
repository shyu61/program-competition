// 反転(Fliptile): p141
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 全問の2次元バージョン
// 1行目だけ全探索すれば2行目以降は一意に決まるので全問と同様に解ける

// 反転問題は、順序に影響を受けないことから、基本は端から順番に処理していく戦略を取りつつ、
// 同じ要素の2回反転は無駄であることから操作を一意に決められないかを検討すると良い。
// 本問題のように一部だけ全探索すればあとは一意に決まるパターンもあるので、実験してみることも重要

const int dx[5] = {-1,0,0,0,1};
const int dy[5] = {0,-1,0,1,0};

int M, N;
vector<vector<int>> tile, opt, flip;

// flipを更新するたびに盤面を変更するのではなく、チェックするときに反転回数を数えて状態を取得する
int get(int x, int y) {
    int c = tile[x][y];
    for (int d = 0; d < 5; d++) {
        int x2 = x + dx[d], y2 = y + dy[d];
        if (0 <= x2 && x2 < M && 0 <= y2 && y2 < N) {
            c += flip[x2][y2];
        }
    }
    return c % 2;
}

int calc() {
    // 2行目以降
    for (int i = 1; i < M; i++) {
        for (int j = 0; j < N; j++) {
            // 1つ上の行の、同列が黒なら反転する
            if (get(i - 1, j) != 0) {
                flip[i][j] = 1;
            }
        }
    }

    // 最終行が全部白かチェック
    for (int j = 0; j < N; j++) {
        if (get(M - 1, j) != 0) return -1;
    }

    // 反転回数をカウント
    int res = 0;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            res += flip[i][j];
        }
    }
    return res;
}

int main() {
    cin >> M >> N;
    tile = opt = flip = vector<vector<int>>(M, vector<int>(N));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cin >> tile[i][j];
        }
    }

    int res = -1;
    // 1行目を全通り試す
    for (int i = 0; i < 1 << N; i++) {
        for (int i = 0; i < flip.size(); i++) fill(flip[i].begin(), flip[i].end(), 0);

        for (int j = 0; j < N; j++) {
            // 集合iに合わせて1行目の各列を反転する
            flip[0][N - j - 1] = i >> j & 1;
        }
        int num = calc();
        if (num >= 0 && (res < 0 || res > num)) {
            res = num;
            opt = flip;
        }
    }

    if (res < 0) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                cout << opt[i][j] << " ";
            }
            cout << endl;
        }
    }
}
